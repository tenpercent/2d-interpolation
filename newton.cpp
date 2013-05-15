#include "mymainwindow.hh"

double MyMainWindow::fdiff(int i, int j){ 
  return (f_x[i]-f_x[j])/(x[i]-x[j]);
}

void MyMainWindow::build_newton_coef(){
  delete[] coef;
  delete[] x;
  delete[] f_x;

  int i,j;
  double omega = (finish-start)/(count_points-1);
  double delta = omega;
  coef = new double[count_points];
  x = new double[count_points];
  f_x = new double[count_points];

  for(i=0;i<count_points;++i){
    x[i]=start+i*omega;
    f_x[i]=f(x[i]);
    coef[i]=f_x[i]; 
  }
#ifndef SHORT_WAY  
  for(i=1; i<count_points; ++i){
    for(j=count_points-1; j>=i; --j){
      coef[j]=(coef[j]-coef[j-1])/(x[j]-x[j-i]);
    }
  }
#else
  for(i=1; i<count_points; ++i){
    for(j=count_points-1; j>=i; --j){
      coef[j]=(coef[j]-coef[j-1])/delta;
    }
    delta+=omega;
  }
#endif
}

double MyMainWindow::find_newton_value(double point){
  int i;
  double value=0.;
  value = coef[count_points-1];
  
  for (i =count_points-2; i>=0; --i){
    value *= (point - x[i]);
    value+=coef[i];
  }
  
  return value;
}

void MyMainWindow::setup_draw_function(){
  int i;
  double omega= (finish-start)/(DRAW_SIZE -1);
  double current_x;
  double temp;
  double max_module_x=0.0;
  double max_module_y=0.0;
  
  for(i=0; i<DRAW_SIZE; ++i){
    current_x=start+i*omega;
    if(fabs(current_x) >max_module_x)
      max_module_x = fabs(current_x);
    
    draw->point_list_f[i].setX(current_x);
    temp=f(current_x);
    draw->point_list_f[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module=max_module_x;
  draw->y_max_module=max_module_y;
  draw->max_module= (max_module_x<max_module_y? max_module_y: max_module_x);
}

void MyMainWindow::setup_draw_newton(){
  int i;
  double omega= (finish-start)/(DRAW_SIZE -1);
  double current_x;
  double temp;
  double max_module_x=0.0;
  double max_module_y=0.0;
  
  for(i=0; i<DRAW_SIZE; ++i){
    current_x=start+i*omega;
    if(fabs(current_x) >max_module_x)
      max_module_x = fabs(current_x);
    
    draw->point_list_1[i].setX(current_x);
    temp = find_newton_value(current_x);
    draw->point_list_1[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module=max_module_x;
  draw->y_max_module=max_module_y;
  draw->max_module= (max_module_x<max_module_y? max_module_y: max_module_x);
}

double MyMainWindow::residual_newton(){
  int i;
  double max_module=0.0;
  double module;

  for(i= 0; i<DRAW_SIZE; ++i){
    module = fabs(draw->point_list_1[i].y());

    if(module > max_module)
      max_module =module;
  }
  return max_module;
}

void MyMainWindow::setup_draw_residual_newton(){
  int i;
  double omega= (finish-start)/(DRAW_SIZE -1);
  double current_x;
  double temp;
  double max_module_x=0.0;
  double max_module_y=0.0;
  
  for(i=0; i<DRAW_SIZE; ++i){
    current_x=start+i*omega;
    if(fabs(current_x) >max_module_x)
      max_module_x = fabs(current_x);
    
    draw->point_list_1[i].setX(current_x);
    temp=find_newton_value(current_x);
    temp=f(current_x)-temp;
    if (fabs(temp)<(EPS)) temp=0.0;
    draw->point_list_1[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module=max_module_x;
  draw->y_max_module=max_module_y;
  draw->max_module= (max_module_x<max_module_y? max_module_y: max_module_x);
}
