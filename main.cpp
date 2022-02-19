#include <QTimer>
#include <QSurfaceFormat>
#include <QWidget>
#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    // Use OpenGL 3.3 Core Profile
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    // Initialization
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    // Set up a QT timer to pulse the update() function of the node graph widget.
    auto gw = m.findChild<QWidget *>("GraphWidget");
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), gw, SLOT(update()));
    timer.start(16);

    // Run the application
    return a.exec();
}
