#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

class EditorWindow : public QWidget {
    Q_OBJECT

public:
    explicit EditorWindow(const QPixmap &image, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap screenshot;
    QPoint startPoint, endPoint;
    bool isDrawing;

public slots:
    void saveScreenshot();
};

#endif // EDITORWINDOW_H
