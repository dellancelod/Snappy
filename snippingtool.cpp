// SnippingTool.cpp
#include "snippingtool.h"

SnippingTool::SnippingTool(QWidget *parent) : QWidget(parent), isSelecting(false) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setWindowOpacity(0.6);
    setStyleSheet("QWidget{background: #000000}");
    setWindowState(Qt::WindowFullScreen);
    qDebug() << "SnippingTool geometry:" << this->geometry();
}

SnippingTool::~SnippingTool() {}

void SnippingTool::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    qDebug() << "paintEvent called";
    painter.setPen(Qt::red);
    painter.setBrush(QColor(255, 0, 0, 50));
    painter.drawRect(QRect(startPoint, endPoint));
}

void SnippingTool::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mouse press at:" << event->pos();
        startPoint = event->pos();
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
        isSelecting = false;
        QRect selectedRect(startPoint, endPoint);
        QPixmap screenshot = QGuiApplication::primaryScreen()->grabWindow(0, selectedRect.x(), selectedRect.y(), selectedRect.width(), selectedRect.height());
        screenshot.save("screenshot.png");
        close();
    }
}
