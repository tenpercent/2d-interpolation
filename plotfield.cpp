#include <iostream>
#include "plotfield.hh"

PlotField::PlotField(){
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  point_list_1 = new QPointF[DRAW_SIZE];
  point_list_2 = new QPointF[DRAW_SIZE];
  point_list_f = new QPointF[DRAW_SIZE];
}

PlotField::~PlotField(){
  delete[] point_list_1;
  delete[] point_list_2;
  delete[] point_list_f;
}

void PlotField::paintEvent(QPaintEvent *){
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 1));

  double inverse;
  double scale_x,scale_y;

  QPointF center, position, point;
  position = pos();
  center.setX((position.x() + width()) / 2.0);
  center.setY((position.y() + height()) / 2.0);

  // Координатные линии
  painter.drawLine(QPointF(center.x(), 0.0), QPointF(center.x(), height()));
  painter.drawLine(QPointF(0.0, center.y()), QPointF(width(), center.y()));

  scale_x = width() / (2.0 * x_max_module);
  if (fabs(y_max_module)<EPS) scale_y=0.0;
  else scale_y = height() / (2.0 * y_max_module);

  point.setX(0.0); point.setY(0.0);
  if (method==1 && type==1){
    painter.setPen(QPen(Qt::red, 1));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_f[i].x() + center.x());
      point.setY(scale_y * point_list_f[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);	
      painter.drawPoint(point);
    }
    painter.setPen(QPen(Qt::blue, 2));
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
    painter.setPen(QPen(Qt::blue, 2));
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
    painter.setPen(QPen(Qt::red, 1));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_f[i].x() + center.x());
      point.setY(scale_y * point_list_f[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);	
      painter.drawPoint(point);
    }
    painter.setPen(QPen(Qt::green, 2));
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
    painter.setPen(QPen(Qt::green, 2));
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
    painter.setPen(QPen(Qt::blue, 2));
    for(int i=0; i<DRAW_SIZE; ++i){
      point.setX(scale_x * point_list_1[i].x() + center.x());
      point.setY(scale_y * point_list_1[i].y() + center.y());
      inverse = 2 * (point.y() - center.y());
      inverse = point.y() - inverse;
      point.setY(inverse);	
      painter.drawPoint(point);
    }
    painter.setPen(QPen(Qt::green, 2));
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
