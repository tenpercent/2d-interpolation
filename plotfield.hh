#ifndef PLOTFIELD
#define PLOTFIELD

#define EPS 1e-14
#define DRAW_SIZE 3000

#include <QtGui>

class PlotField: public QWidget{ 
  Q_OBJECT
  public:
    PlotField();
    ~PlotField();
    QPointF *point_list_newton;
    QPointF *point_list_splines;
    QPointF *point_list_function;

    QPen *color_newton;
    QPen *color_splines;
    QPen *color_newton_res;
    QPen *color_splines_res;

    int method;
    int type;

    double max_module1;
    double max_module2;
    double x_max_module1;
    double y_max_module1;
    double x_max_module2;
    double y_max_module2;

  protected:
    void paintEvent(QPaintEvent *);
};

#endif
