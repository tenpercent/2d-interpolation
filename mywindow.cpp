#include <QtGui>
#include <QtCore/qmath.h>
#include <mywindow.hh>

double MyWindow::f(double p){
  return qExp(p);
  //return (p*p*p+3*p);
  //return 1;
}

MyWindow::MyWindow(){
  resize(800, 600);
  setWindowFlags(Qt::Window);
  setWindowTitle(QString::fromUtf8("Приближение функции одной переменной"));

  go = new QPushButton(QString::fromUtf8("Построить"), this);
  exit = new QPushButton(QString::fromUtf8("Выход"), this);
  connect(go, SIGNAL(clicked()), SLOT(push_go()));
  connect(exit,SIGNAL(clicked()),SLOT(goodbye())); 
  
  draw = new PlotField();

  lbl = new QLabel(QString::fromUtf8("Невязка: -"));
  count_points=16;

  my_layout = new QGridLayout;
  my_layout->setMargin(5);
  my_layout->setSpacing(5);
  my_layout->addWidget(draw,0,0,9,10);
  my_layout->addWidget(chooseMethod(),10,0,1,1);
  my_layout->addWidget(choosePlot(),10,2,1,1);
  my_layout->addWidget(points(),10,4,1,1);
  my_layout->addWidget(begin(),10,5,1,1);
  my_layout->addWidget(end(),10,6,1,1);
  my_layout->addWidget(lbl,10,7,1,1);
  my_layout->addWidget(go, 10,8,1,1);
  my_layout->addWidget(exit, 10,9,1,1);
  setLayout(my_layout);

  count_points=16;
  start=0;
  finish=1;
  x=NULL; f_x=NULL; c=NULL; coef = NULL;
  draw->method = 1;
  draw->type=1;

}

MyWindow::~MyWindow(){
  delete[] coef;
  delete[] x;
  delete[] f_x;
  delete[] c;
  delete draw;
  delete go;
  delete exit;
  delete my_layout;
}

QGroupBox *MyWindow::choice_method(){
  QGroupBox *group_box = new QGroupBox(QString::fromUtf8("Построение приближения:"));
  group_box->setMaximumHeight(90);
  group_box->setMaximumWidth(230);

  QRadioButton *method_1 = new QRadioButton(QString::fromUtf8("Формула Ньютона"));
  QRadioButton *method_2 = new QRadioButton(QString::fromUtf8("Кусочная интерполяция"));
  QRadioButton *method_3 = new QRadioButton(QString::fromUtf8("Оба метода"));

  method_1->setChecked(true);

  connect(method_1, SIGNAL(clicked()), SLOT(push_method_1()));
  connect(method_2, SIGNAL(clicked()), SLOT(push_method_2()));
  connect(method_3, SIGNAL(clicked()), SLOT(push_method_3()));

  QVBoxLayout *method_layout = new QVBoxLayout;
  method_layout->addWidget(method_1);
  method_layout->addWidget(method_2);
  method_layout->addWidget(method_3);
  group_box->setLayout(method_layout);
  return group_box;
}

QGroupBox *MyWindow::chooseMethod(){
  QGroupBox *button_group = new QGroupBox();

  QCheckBox *newton_polynom = new QCheckBox(QString::fromUtf8("Формула Ньютона"));
  QCheckBox *splines = new QCheckBox(QString::fromUtf8("Кубические сплайны"));

  connect(newton_polynom, SIGNAL(clicked()), SLOT(push_method_1()));
  connect(splines, SIGNAL(clicked()), SLOT(push_method_2()));

  QHBoxLayout *method_layout = new QHBoxLayout;
  method_layout->addWidget(newton_polynom);
  method_layout->addWidget(splines);
  button_group->setLayout(method_layout);
  return button_group;
}

QGroupBox *MyWindow::choice_type_draw(){
  QGroupBox *group_box = new QGroupBox(QString::fromUtf8("Тип рисунка:"));
  group_box->setMaximumHeight(90);
  group_box->setMaximumWidth(230);

  QRadioButton *graphic= new QRadioButton(QString::fromUtf8("График"));
  QRadioButton *residual= new QRadioButton(QString::fromUtf8("Невязка"));

  graphic->setChecked(true);

  connect(graphic, SIGNAL(clicked()), SLOT(push_graphic()));
  connect(residual, SIGNAL(clicked()), SLOT(push_residual()));

  QVBoxLayout *type_layout = new QVBoxLayout;
  type_layout->addWidget(graphic);
  type_layout->addWidget(residual);
  group_box->setLayout(type_layout);
  return group_box;
}

QGroupBox *MyWindow::choosePlot(){
  QGroupBox *button_group = new QGroupBox();

  QCheckBox *graph = new QCheckBox(QString::fromUtf8("График"));
  QCheckBox *residual = new QCheckBox(QString::fromUtf8("Невязка"));

  connect(graph, SIGNAL(clicked()), SLOT(push_graphic()));
  connect(residual, SIGNAL(clicked()), SLOT(push_residual()));

  QHBoxLayout *plot_layout = new QHBoxLayout;
  plot_layout->addWidget(graph);
  plot_layout->addWidget(residual);
  button_group->setLayout(plot_layout);
  return button_group;
}

QGroupBox *MyWindow::points(){
  QGroupBox *group_box = new QGroupBox(QString::fromUtf8("Количество точек:"));

  QLabel *lable2 = new QLabel;

  lable2->setText(QString::number(count_points));
  QPushButton *plus=new QPushButton(QString::fromUtf8("+"), this);
  QPushButton *minus=new QPushButton(QString::fromUtf8("-"), this);
  connect(plus, SIGNAL(clicked()), SLOT(set_points_plus()));
  connect(minus, SIGNAL(clicked()), SLOT(set_points_minus()));
  connect(this, SIGNAL(counterChanged(int)),lable2, SLOT(setNum(int)));

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(minus);
  layout->addWidget(lable2);
  layout->addWidget(plus);
  group_box->setLayout(layout);

  return group_box;
}

QWidget *MyWindow::begin(){
  QWidget *widget = new QWidget();
  widget->setMaximumHeight(50);
  widget->setMaximumWidth(230);

  QLabel *lable = new QLabel;
  lable->setText(QString::fromUtf8("Начало отрезка:"));

  QDoubleSpinBox *spin_box = new QDoubleSpinBox;
  spin_box->setRange(-5000.0, 5000.0);
  spin_box->setSingleStep(0.1);
  spin_box->setValue(0.0);

  connect(spin_box, SIGNAL(valueChanged(double)), SLOT(set_begin(double)));

  QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
  layout->addWidget(lable);
  layout->addWidget(spin_box);
  widget->setLayout(layout);

  return widget;
}

QWidget *MyWindow::end(){
  QWidget *widget = new QWidget();
  widget->setMaximumHeight(50);
  widget->setMaximumWidth(230);

  QLabel *lable = new QLabel;
  lable->setText(QString::fromUtf8("Конец отрезка:"));

  QDoubleSpinBox *spin_box = new QDoubleSpinBox;
  spin_box->setRange(-5000.0, 5000.0);
  spin_box->setSingleStep(0.1);
  spin_box->setValue(1.0);

  connect(spin_box, SIGNAL(valueChanged(double)), SLOT(set_end(double)));

  QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
  layout->addWidget(lable);
  layout->addWidget(spin_box);
  widget->setLayout(layout);

  return widget;
}

void MyWindow::set_points_plus(){
  MyWindow::count_points =2*count_points;
  if (count_points>=64) 
    if (draw->method==1 || draw->method==3) count_points=64;
  if (count_points>=1000000) count_points=1048576; 
  emit counterChanged(count_points);
}

void MyWindow::set_points_minus(){
  MyWindow::count_points =count_points/2;
  if (count_points<=2) 
     count_points=2; 
  emit counterChanged(count_points);
}

void MyWindow::set_begin(double x){
  MyWindow::start =x;
}
void MyWindow::set_end(double x){
  MyWindow::finish =x;
}
void MyWindow::goodbye(){
  emit close_window();
}
void MyWindow::push_go(){

  double r=0.0;
  if(start >finish){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromUtf8("Ошибка"));
        msgBox.setText(QString::fromUtf8("Ошибка ввода! Повторите попытку."));
        msgBox.exec();
    return;
  }
  if (draw->method==1){
    build_newton_coef();
    setup_draw_residual_newton();
    r=residual_newton();
    if (fabs(r)<EPS) r=0.0;
    if (draw->type==1){
      setup_draw_function();
      setup_draw_newton();	
      draw->update();
    }
    else{
      draw->update();
    }
    lbl->setText(QString::fromUtf8("Невязка интерполяционной\n  формулы Ньютона: ") +
                       QString::number(r));
    return;
  }
  if (draw->method==2){
    build_spline();
    setup_draw_residual_spline();
    r=residual_spline();
    if (fabs(r)<EPS) r=0.0;
    if (draw->type==1){
      setup_draw_function();
      setup_draw_spline();
      draw->update();
    }
    else
      draw->update();
    lbl->setText(QString::fromUtf8("Невязка кусочной интерполяции\n  кубическими сплайнами: ") +
                       QString::number(r));	
    //draw->update();
  }
  if (draw->method==3){
    lbl->setText(QString::fromUtf8("Для просмотра невязки выберите\n  конкретный способ приближения"));
    if (draw->type==1){
      build_newton_coef();
      setup_draw_newton();
      draw->update();
      build_spline();
      setup_draw_spline();
      draw->update();
    }
    if (draw->type==2){
      build_spline();
      setup_draw_residual_spline();
      build_newton_coef();
      setup_draw_residual_newton();
      draw->update();
    }
  }
  return;
}
void MyWindow::push_method_1(){ 
  draw->method = 1; if (count_points>=64) count_points=64;
  emit counterChanged(count_points);
}

void MyWindow::push_method_2(){
  draw->method = 2;
}

void MyWindow::push_method_3(){
  draw->method = 3; if (count_points>=64) count_points=64;
  emit counterChanged(count_points);
}

void MyWindow::push_graphic(){ 
  draw->type = 1;
}

void MyWindow::push_residual(){
  draw->type = 2;
}
