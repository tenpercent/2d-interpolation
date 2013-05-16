#ifndef MYMAINWINDOW
#define MYMAINWINDOW

#include <QtGui>
#include <QMenuBar>
#include "plotfield.hh"

class MyMainWindow : public QMainWindow
{
  Q_OBJECT  

  public:
    MyMainWindow();
    ~MyMainWindow();
  private:
    QRect* geometry;
    QMenuBar *mainmenu;
    QAction *quit;
    QAction *run;
    QAction *newton_method;
    QAction *splines_method;
    QAction *graphic_plot;
    QAction *residual_plot;
    QWidget *my_widget;
    QActionGroup *plot_action_group;
    QLabel *lbl;

    QMenu *file;
    QMenu *method;
    QMenu *plot;

    QGridLayout *my_layout;
    QGroupBox *points();
    QWidget *begin();		//поле для ввода начала отрезка
    QWidget *end();		//поле для ввода конца отрезка

    int count_points;		//количество точек разбиения
    double start;		//начало отрезка
    double finish;		//конец отрезка
    
    double *table;		//таблица разделенных разностей
    double *coef;
    double *x,*f_x;		//узлы и значения в узлах функции
    double *c;

    double fdiff(int i, int j);

    PlotField *draw;		//поле для рисования

    double f(double p);		//фунция, которую будем приближать

    void setup_draw_function();
    void build_newton_coef();
    double find_newton_value(double p);
    void setup_draw_newton();	//настройка данных и подготовка для рисования первого метода
    void setup_draw_residual_newton();//настройка данных и подготовка для рисования невязки первого метода
    double residual_newton();	//вычисление невязки первого метода 

    void solve_system(double *a1, double *a2, double *a3, double *b, double *x);
    void build_spline();
    double find_spline_value(double p);
    void setup_draw_spline();
    double residual_spline();
    void setup_draw_residual_spline();
  public slots:
    void set_points_plus();
    void set_points_minus();
    void set_begin(double x);
    void set_end(double x);
    void push_go();
    void goodbye();
    void push_method_1();
    void push_method_2();
    void push_graphic();
    void push_residual();
  signals:
    void close_window();
    void counterChanged(int);
    //void valueChanged(double);
};
#endif