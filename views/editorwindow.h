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
    void wheelEvent(QWheelEvent *event) override;

private:
    QPixmap screenshot;
    float scaleFactor;

public slots:
    void saveScreenshot();
};

#endif // EDITORWINDOW_H
