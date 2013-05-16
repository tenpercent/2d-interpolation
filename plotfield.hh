#ifndef PLOTFIELD
#define PLOTFIELD

#define EPS 1e-14
#define DRAW_SIZE 1111

#include <QtGui>

class PlotField: public QWidget{ 
  Q_OBJECT
  public:
    PlotField();
    ~PlotField();
    QPointF *point_list_1;
    QPointF *point_list_2;
    QPointF *point_list_f;

    int method;
    int type;
    double max_module;
    double x_max_module;
    double y_max_module;

  protected:
    void paintEvent(QPaintEvent *);
};

#endif
