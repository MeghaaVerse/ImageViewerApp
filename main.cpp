#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window w;
    w.setWindowTitle("Brightness Slider App");
    w.resize(900,600);
    w.show();

    return app.exec();
}
