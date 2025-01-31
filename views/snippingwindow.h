// SnippingTool.h
#ifndef SNIPPINGWINDOW_H
#define SNIPPINGWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QPainterPath>

class SnippingTool : public QWidget {
    Q_OBJECT

public:
    explicit SnippingTool(QWidget *parent = nullptr);
    ~SnippingTool();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint startPoint, endPoint;
    QRect selectedRect;
    QPixmap grabbedScreen;
    bool isSelecting;
};

#endif // SNIPPINGWINDOW_H
