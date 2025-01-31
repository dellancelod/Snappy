#include "EditorWindow.h"
#include <QPainter>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

EditorWindow::EditorWindow(const QPixmap &image, QWidget *parent)
    : QWidget(parent), screenshot(image), scaleFactor(1.0) {

    setWindowTitle("Screenshot Editor");
    setMinimumSize(200, 200); // Set minimum width and height

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

    QPixmap scaledScreenshot = screenshot.scaled(screenshot.size() * scaleFactor, Qt::KeepAspectRatio);

    int xOffset = (width() - scaledScreenshot.width()) / 2;
    int yOffset = (height() - scaledScreenshot.height()) / 2;

    painter.drawPixmap(xOffset, yOffset, scaledScreenshot);

}
void EditorWindow::wheelEvent(QWheelEvent *event) {
    // Check if the Alt key is held down while scrolling
    if (event->modifiers() & Qt::ControlModifier) {
        // Check the direction of the scroll

        if (event->angleDelta().y() > 0) {
            // Zoom in
            scaleFactor += 0.1f;
        } else {
            // Zoom out
            scaleFactor -= 0.1f;
        }

        // Ensure the image doesn't get too small
        if (scaleFactor < 0.1) scaleFactor = 0.1;
        if (scaleFactor > 3.0) scaleFactor = 3.0;

        // Repaint the window to show the resized image
        update();
    }

    // Call the base class method to handle default behavior
    QWidget::wheelEvent(event);
}

void EditorWindow::saveScreenshot() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Screenshot", "", "PNG Files (*.png);;JPG Files (*.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        screenshot.save(fileName);
        close();
    }
}
