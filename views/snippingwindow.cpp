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

    painter.drawPixmap(0, 0, grabbedScreen);

    selectedRect = QRect(startPoint, endPoint).normalized();
    // Create a path covering the full window
    QPainterPath overlayPath;
    overlayPath.addRect(rect());

    // If selection is valid, subtract it from the overlay path
    if (selectedRect.width() > 1 && selectedRect.height() > 1) {
        QPainterPath selectionPath;
        selectionPath.addRect(selectedRect);
        overlayPath = overlayPath.subtracted(selectionPath);

        // Draw selection border
        painter.setPen(QPen(Qt::white, 2));
        painter.drawRect(selectedRect);
    }

    // Fill the rest of the screen with semi-transparent black
    painter.fillPath(overlayPath, QColor(0, 0, 0, 127));

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

        qDebug() << "Screen: " << grabbedScreen;
        qDebug() << "Screenshot: " << selectedRect;
        if(selectedRect.width() <= 1 || selectedRect.height() <= 1){
            return;
        }
        isSelecting = false;

        // Hide the overlay before capturing
        this->hide();
        QGuiApplication::processEvents();

        // Capture the screenshot

        qreal dpr = grabbedScreen.devicePixelRatio();
        QRect scaledRect = QRect(selectedRect.topLeft() * dpr, selectedRect.size() * dpr);
        QPixmap screenshot = grabbedScreen.copy(scaledRect);
        screenshot.setDevicePixelRatio(dpr);

        // Open the screenshot editor window
        EditorWindow *editor = new EditorWindow(screenshot);
        editor->show();

        // Close the snipping tool
        close();
    }
}
