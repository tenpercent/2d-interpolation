#ifndef MYWINDOW_H
#define MYWINDOW_H
#define SHORT_WAY

#include <QtGui>
#include <plotfield.hh>
#include <QCheckBox>
#include <QButtonGroup>

class MyWindow : public QWidget{ 
  Q_OBJECT
  private:
    QPushButton *go;		//кнопка "построить"
    QPushButton *exit;		//кнопка "выход"
    QLabel *lbl;		//место для вывода невязки
    QGridLayout *my_layout;	//мое оформление
    QGroupBox *choice_method(); //группа выбора метода
    QGroupBox *choice_type_draw();
    QGroupBox *points();	//поле для указание количества точек разбиения

    QGroupBox *chooseMethod();
    QGroupBox *choosePlot();
    //QButtonGroup *points();

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

  public:
    MyWindow();
    ~MyWindow();
    static const int DRAW_SIZE = 1111;
    static const double EPS = 1e-15;

  public slots:
    void set_points_plus();
    void set_points_minus();
    void set_begin(double x);
    void set_end(double x);
    void push_go();
    void goodbye();
    void push_method_1();
    void push_method_2();
    void push_method_3();
    void push_graphic();
    void push_residual();
  signals:
    void close_window();
    void counterChanged(int);
};

#endif // MYWINDOW_H
