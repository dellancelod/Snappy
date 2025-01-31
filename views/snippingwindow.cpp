// SnippingTool.cpp
#include "snippingwindow.h"
#include "editorwindow.h"

SnippingTool::SnippingTool(QWidget *parent) : QWidget(parent), isSelecting(false) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowState(Qt::WindowFullScreen);

    grabbedScreen = QGuiApplication::primaryScreen()->grabWindow(0);
    qDebug() << "SnippingTool geometry:" << this->geometry();
}

SnippingTool::~SnippingTool() {}

void SnippingTool::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Fill the entire screen with black

    selectedRect = QRect(startPoint, endPoint).normalized();
    painter.drawPixmap(0, 0, grabbedScreen);
    painter.fillRect(rect(), QColor(0, 0, 0, 127)); // Semi-transparent black overlay

    if(selectedRect.width() > 1 && selectedRect.height() > 1){
        // Clear the selected area to make it fully transparent
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.fillRect(selectedRect, Qt::transparent);

        // Draw a red outline around the selection area
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawRect(selectedRect);
    }


}

void SnippingTool::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mouse press at:" << event->pos();
        startPoint = event->pos();
        endPoint = startPoint;
        isSelecting = true;

    }
}

void SnippingTool::mouseMoveEvent(QMouseEvent *event) {
    if (isSelecting) {
        endPoint = event->pos();
        update();
    }
}

void SnippingTool::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {

        qDebug() << "Width:" << selectedRect.width();
        qDebug() << "Height:" << selectedRect.height();
        if(selectedRect.width() <= 1 || selectedRect.height() <= 1){
            return;
        }
        isSelecting = false;

        // Hide the overlay before capturing
        this->hide();
        QGuiApplication::processEvents();

        // Capture the screenshot
        QPixmap screenshot = QGuiApplication::primaryScreen()->grabWindow(0, selectedRect.x(), selectedRect.y(), selectedRect.width(), selectedRect.height());

        // Open the screenshot editor window
        EditorWindow *editor = new EditorWindow(screenshot);
        editor->show();

        // Close the snipping tool
        close();
    }
}
