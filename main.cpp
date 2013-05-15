#include <QtGui>
#include <mymainwindow.hh>

int main(int argc, char *argv[]){

  QApplication app(argc, argv);
  MyMainWindow window;
  window.resize(640, 480);
  window.move(300, 300);  
  window.show();
  return app.exec();
}
