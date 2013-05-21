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
    QWidget *left();
    QWidget *right();

    int count_points;
    double start;
    double finish;
    
    double *table;
    double *coef;
    double *x,*f_x;
    //double *c1,*c2,*c3,*c4;
    double *c;

    double fdiff(int i, int j);

    PlotField *draw;

    double f(double p);

    void setup_draw_function();
    void build_newton_coef();
    double find_newton_value(double p);
    void setup_draw_newton();
    void setup_draw_residual_newton();
    double residual_newton();

    void solve_system(double *a1, double *a2, double *a3, double *b, double *x);
    void build_spline();
    double find_spline_value(double p);
    void setup_draw_spline();
    double residual_spline();
    void setup_draw_residual_spline();
  public slots:
    void set_points_plus();
    void set_points_minus();
    void set_left(double x);
    void set_right(double x);
    void push_go();
    void push_method_1();
    void push_method_2();
    void push_graphic();
    void push_residual();
  signals:
    void close_window();
    void counterChanged(int);
};
#endif