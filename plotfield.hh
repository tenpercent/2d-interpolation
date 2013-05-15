#ifndef PLOTFIELD
#define PLOTFIELD

#include <QtGui>

class PlotField: public QWidget{ 
  Q_OBJECT
  public:
    PlotField();
    ~PlotField();
    QPointF *point_list_1;
    QPointF *point_list_2;
    QPointF *point_list_f;

    static const int DRAW_SIZE = 1111;
    static const double EPS = 1e-15;

    int method;
    int type;
    double max_module;
    double x_max_module;
    double y_max_module;

  protected:
    void paintEvent(QPaintEvent *);
};

#endif
