#include "mymainwindow.hh"

void MyMainWindow::solve_system(double *a, double *c, double *d, double *b, double *x){
  int i;
  c[0] /= a[0];
  for (i = 1; i <count_points- 1; ++i){
    a[i] -= d[i - 1] * c[i - 1];
    c[i] /= a[i];
  }
  a[count_points- 1] -= d[count_points- 2] * c[count_points- 2];
  x[0] = b[0] / a[0];
  for (i = 1; i <count_points;++i)
    x[i] = (b[i] - d[i - 1] * x[i - 1]) / a[i];
  for (i =count_points-2; i >= 0; --i)
    x[i] -= c[i] * x[i + 1];
}

void MyMainWindow::build_spline(){
  //удаялем старые данные
  delete[] c;
  delete[] x;
  delete[] f_x;

  //инициализация
  int i; double temp1,temp2;
  double omega= (finish-start)/(count_points-1);
  //table = new double[count_points*count_points];
  x= new double[count_points];
  f_x= new double[count_points];
  c=new double[count_points*4];

  double *mid_diag = 0;
  mid_diag=new double[count_points];
  double *top_diag = 0;
  top_diag=new double[count_points];
  double *bot_diag = 0;
  bot_diag=new double[count_points];
  double *d = 0;
  d=new double[count_points];
  
 for(i=0;i<count_points;++i){
    x[i]=start+i*omega;
    f_x[i]=f(x[i]);  
  };
#ifndef SHORT_WAY
  for (i = 1; i <count_points- 1; ++i){
    temp1 = (f_x[i] - f_x[i - 1]) / (x[i] - x[i - 1]);
    temp2 = (f_x[i + 1] - f_x[i]) / (x[i + 1] - x[i]);
    c[i] = 3 * temp1 * (x[i + 1] - x[i]) + 3 * temp2 * (x[i] - x[i - 1]);
    mid_diag[i] = 2.0 * (x[i + 1] - x[i - 1]);
    top_diag[i] = x[i] - x[i - 1];
    bot_diag[i - 1] = x[i + 1] - x[i];
  }
  mid_diag[0] = x[2]-x[1]; 
  top_diag[0] = x[2]-x[0];
  mid_diag[count_points - 1] = x[count_points-2]-x[count_points-3]; 
  bot_diag[count_points - 2] = x[count_points-1]-x[count_points-3];
  c[count_points- 1] = ((f_x[count_points-2]-f_x[count_points-3])/(x[count_points-2]-x[count_points-3])*(x[count_points-1]-x[count_points-2])*(x[count_points-1]-x[count_points-2]) + (f_x[count_points-1]-f_x[count_points-2])/(x[count_points-1]-x[count_points-2])*(x[count_points-2]-x[count_points-3])*(3*x[count_points-1]-2*x[count_points-3]-x[count_points-2]))/(x[count_points-1]-x[count_points-3]);
  c[0] = ((f_x[2]-f_x[1])/(x[2]-x[1])*(x[1]-x[0])*(x[1]-x[0]) + (f_x[1]-f_x[0])/(x[1]-x[0])*(x[2]-x[1])*(2*x[2]+x[1]-3*x[0]))/(x[2]-x[0]);
#endif
#ifdef SHORT_WAY
  for (i = 1; i <count_points- 1; ++i){
    temp1 = (f_x[i] - f_x[i - 1]);
    temp2 = (f_x[i + 1] - f_x[i]);
    c[i] = 3 * temp1  + 3 * temp2;
    mid_diag[i] = omega * 4;
    top_diag[i] = omega;
    bot_diag[i - 1] = omega;
  }
  mid_diag[0] = omega; 
  top_diag[0] = omega * 2;
  mid_diag[count_points - 1] = omega; 
  bot_diag[count_points - 2] = omega * 2;
  c[count_points- 1] = ((f_x[count_points-2]-f_x[count_points-3]) + (f_x[count_points-1]-f_x[count_points-2])*5)/2.;
  c[0] = ((f_x[2]-f_x[1]) + (f_x[1]-f_x[0])*5)/2.;
#endif
  solve_system(mid_diag, top_diag, bot_diag, c, d);
  
  for (i = 0; i < count_points-1; i++){
    c[4*i+ 0] = f_x[i];
    c[4*i+ 1] = d[i];
    temp2 = x[i + 1] - x[i];
    temp1 = (f_x[i + 1] - f_x[i]) / temp2;
    c[4*i+ 2] = (3*temp1 - 2*d[i] - d[i + 1]) / temp2;
    temp2 *= temp2;
    c[4*i+ 3] = (d[i] + d[i + 1] - 2*temp1) / temp2;
  }
  delete[] top_diag; 
  delete[] bot_diag; 
  delete[] mid_diag; 
  delete[] d; 
}

double MyMainWindow::find_spline_value(double p){
  int i;
  for(i=0;i<count_points-2;++i)
    if (p>=x[i] && p<=x[i+1]) break;
  double dist = p - x[i];
  return c[4*i] + c[4*i+1] * dist + c[4*i+2] * dist*dist + c[4*i+3] * dist*dist*dist;
}

void MyMainWindow::setup_draw_spline(){
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
    
    draw->point_list_2[i].setX(current_x);
    temp = find_spline_value(current_x);
    draw->point_list_2[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module=max_module_x;
  draw->y_max_module=max_module_y;
  draw->max_module= (max_module_x<max_module_y ? max_module_y : max_module_x);
}

double MyMainWindow::residual_spline(){
  int i;
  double max_module=0.0;
  double module;

  for(i= 0; i<DRAW_SIZE; ++i){
    module = fabs(draw->point_list_2[i].y());

    if(module > max_module)
      max_module =module;
  }
  return max_module;
}
void MyMainWindow::setup_draw_residual_spline(){
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
    
    draw->point_list_2[i].setX(current_x);
    temp = find_spline_value(current_x);
    temp=f(current_x)-temp;
    if (fabs(temp)<(EPS)) temp=0.0;
    draw->point_list_2[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module=max_module_x;
  draw->y_max_module=max_module_y;
  draw->max_module= (max_module_x<max_module_y? max_module_y: max_module_x);
}
