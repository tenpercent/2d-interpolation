#include <iostream>
#include "plotfield.hh"

PlotField::PlotField(){
  setBackgroundRole(QPalette::Light);
  setAutoFillBackground(true);
  point_list_1 = new QPointF[DRAW_SIZE];
  point_list_2 = new QPointF[DRAW_SIZE];
  point_list_f = new QPointF[DRAW_SIZE];

  //x_max_module = 1.;
  //y_max_module = 1.;
}

PlotField::~PlotField(){
  delete[] point_list_1;
  delete[] point_list_2;
  delete[] point_list_f;

  delete color_splines;
  delete color_newton;
  delete color_splines_res;
  delete color_newton_res;
}

void PlotField::paintEvent(QPaintEvent *){
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 1));

  double inverse;
  double scale_x,scale_y;

  //int size = (width()>height()) ? height() : width();

  QPointF center, position, point;
  position = pos();
  center.setX((position.x() + width()) / 2.0);
  center.setY((position.y() + height()) / 2.0);

  painter.drawLine(QPointF(center.x(), 0.0), QPointF(center.x(), height()));
  painter.drawLine(QPointF(0.0, center.y()), QPointF(width(), center.y()));

  if(method == 2)
  {
    max_module1 = max_module2;
    x_max_module1 = x_max_module2;
    y_max_module1 = y_max_module2;
  }
  if(method == 3)
  {
    if(max_module1 < max_module2) max_module1 = max_module2;
    if(x_max_module1 < x_max_module2) x_max_module1 = x_max_module2;
    if(y_max_module1 < y_max_module2) y_max_module1 = y_max_module2;
  }
  scale_x = width() / (2.0 * x_max_module1);
  if (fabs(y_max_module1)<EPS) scale_y=0.0;
  else scale_y = height() / (2.0 * y_max_module1);

  point.setX(0.0); point.setY(0.0);
  if (method==1 && type==1){
    painter.setPen(QPen(Qt::darkGreen, 1));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_f[i].x() + center.x());
      point.setY(scale_y * point_list_f[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);	
      painter.drawPoint(point);
    }
    painter.setPen(QPen(Qt::darkBlue, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_1[i].x() + center.x());
      point.setY(scale_y * point_list_1[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);
      painter.drawPoint(point);
    }
    return;
  }
  if (method==1 && type==2){
    painter.setPen(QPen(Qt::darkMagenta, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_1[i].x() + center.x());
      point.setY(scale_y * point_list_1[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);
      painter.drawPoint(point);
    }
    return;
  }
  if (method==2 && type==1){
    painter.setPen(QPen(Qt::darkGreen, 1));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_f[i].x() + center.x());
      point.setY(scale_y * point_list_f[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);	
      painter.drawPoint(point);
    }
    painter.setPen(QPen(Qt::darkYellow, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_2[i].x() + center.x());
      point.setY(scale_y * point_list_2[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);
      painter.drawPoint(point);
    }
    return;
  }
  if (method==2 && type==2){
    painter.setPen(QPen(Qt::yellow, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_2[i].x() + center.x());
      point.setY(scale_y * point_list_2[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);
      painter.drawPoint(point);
    }
    return;
  }
  if (method==3){
    painter.setPen(QPen(Qt::darkBlue, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_1[i].x() + center.x());
      point.setY(scale_y * point_list_1[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);	
      painter.drawPoint(point);
    }
    painter.setPen(QPen(Qt::darkYellow, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_2[i].x() + center.x());
      point.setY(scale_y * point_list_2[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);
      painter.drawPoint(point);
    }
    return;
  }
}
