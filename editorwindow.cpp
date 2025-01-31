#include "EditorWindow.h"
#include <QPainter>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

EditorWindow::EditorWindow(const QPixmap &image, QWidget *parent)
    : QWidget(parent), screenshot(image), isDrawing(false) {

    setWindowTitle("Screenshot Editor");
    resize(screenshot.size());

    // Add a save button
    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &EditorWindow::saveScreenshot);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(saveButton);
    layout->setAlignment(saveButton, Qt::AlignBottom | Qt::AlignRight);
    setLayout(layout);
}

void EditorWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, screenshot);

    if (isDrawing) {
        painter.setPen(Qt::red);
        painter.drawRect(QRect(startPoint, endPoint));
    }
}

void EditorWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        isDrawing = true;
    }
}

void EditorWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        endPoint = event->pos();
        update();
    }
}

void EditorWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
        update();
    }
}

void EditorWindow::saveScreenshot() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Screenshot", "", "PNG Files (*.png);;JPG Files (*.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        screenshot.save(fileName);
        close();
    }
}
