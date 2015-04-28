#include "widget.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat glFormat;
       glFormat.setVersion( 4, 1 );
       glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
       glFormat.setSampleBuffers( true );

    Widget w(glFormat);
    w.resize(1000,1000);
    w.show();
    return a.exec();
}
