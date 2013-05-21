#include "mymainwindow.hh"
//#define SHORT_WAY
#include <time.h>
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
  delete[] c;
  delete[] x;
  delete[] f_x;

  int i; double temp1,temp2;
  double omega= (finish-start)/(count_points-1);
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
    c[i] = 3 * temp1 + 3 * temp2;
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
/*
void MyMainWindow::solve_system(double *a, double *c, double *b, double *f, double *x)
{
        double m;
        for (int i = 1; i < count_points; i++)
        {
                m = a[i]/c[i-1];  
                c[i] = c[i] - m*b[i-1];
                f[i] = f[i] - m*f[i-1];
        }
 
        x[count_points-1] = f[count_points-1]/c[count_points-1]; 
 
        for (int i = count_points - 2; i >= 0; i--) 
                x[i]=(f[i]-b[i]*x[i+1])/c[i];
 
}

void MyMainWindow::build_spline(){
  delete[] c1;
  delete[] c2;
  delete[] c3;
  delete[] c4;
  delete[] x;

  int i; double temp1,temp2;
  double omega = (finish-start)/(count_points-1);
  
  x = new double[count_points];
  c1 = new double[count_points];
  c2 = new double[count_points];
  c3 = new double[count_points];
  c4 = new double[count_points];

  double *mid_diag = new double[count_points];
  double *right = new double[count_points];
  double *top_diag = c4;
  double *bot_diag = c3;
  double *solution = c2;
  
 for(i=0;i<count_points;++i){
    x[i]=start+i*omega;
    c1[i]=f(x[i]);  
  };
#ifndef SHORT_WAY
  for (i = 1; i <count_points- 1; ++i){
    temp1 = (c1[i] - c1[i - 1]) / (x[i] - x[i - 1]);
    temp2 = (c1[i + 1] - c1[i]) / (x[i + 1] - x[i]);
    right[i] = 3 * temp1 * (x[i + 1] - x[i]) + 3 * temp2 * (x[i] - x[i - 1]);
    mid_diag[i] = 2.0 * (x[i + 1] - x[i - 1]);
    top_diag[i] = x[i] - x[i - 1];
    bot_diag[i] = x[i + 1] - x[i];
  }
  mid_diag[0] = x[2]-x[1]; 
  top_diag[0] = x[2]-x[0];
  mid_diag[count_points - 1] = x[count_points-2]-x[count_points-3]; 
  bot_diag[count_points - 1] = x[count_points-1]-x[count_points-3];
  right[count_points- 1] = ((c1[count_points-2]-c1[count_points-3])/(x[count_points-2]-x[count_points-3])*(x[count_points-1]-x[count_points-2])*(x[count_points-1]-x[count_points-2]) + (c1[count_points-1]-c1[count_points-2])/(x[count_points-1]-x[count_points-2])*(x[count_points-2]-x[count_points-3])*(3*x[count_points-1]-2*x[count_points-3]-x[count_points-2]))/(x[count_points-1]-x[count_points-3]);
  right[0] = ((c1[2]-c1[1])/(x[2]-x[1])*(x[1]-x[0])*(x[1]-x[0]) + (c1[1]-c1[0])/(x[1]-x[0])*(x[2]-x[1])*(2*x[2]+x[1]-3*x[0]))/(x[2]-x[0]);
#else
  for (i = 1; i <count_points- 1; ++i){
    temp1 = (c1[i] - c1[i - 1]);
    temp2 = (c1[i + 1] - c1[i]);
    right[i] = 3 * temp1  + 3 * temp2;
    mid_diag[i] = omega * 4;
    top_diag[i] = omega;
    bot_diag[i] = omega;
  }
  mid_diag[0] = omega; 
  top_diag[0] = omega * 2;
  mid_diag[count_points - 1] = omega; 
  bot_diag[count_points - 1] = omega * 2;
  right[count_points- 1] = ((c1[count_points-2]-c1[count_points-3]) + (c1[count_points-1]-c1[count_points-2])*5)/2.;
  right[0] = ((c1[2]-c1[1]) + (c1[1]-c1[0])*5)/2.;
#endif
  //solve_system(mid_diag, top_diag, bot_diag, c1, d);
  solve_system(bot_diag, mid_diag, top_diag, right, c2);
  //c1 = f_x;
  //c2 = solution;
  c3 = top_diag;
  c4 = bot_diag;
  for (i = 0; i < count_points-1; i++){
    //c1[i] = f_x[i];
    //c2[i] = solution[i];
    temp2 = x[i + 1] - x[i];
    temp1 = (f_x[i + 1] - f_x[i]) / temp2;
    c3[i] = (3*temp1 - 2*c2[i] - c2[i + 1]) / temp2;
    temp2 *= temp2;
    c4[i] = (c2[i] + c2[i + 1] - 2*temp1) / temp2;
  } 
  delete[] right;
  delete[] mid_diag;
}
*/
double MyMainWindow::find_spline_value(double p){
  double ans, dist;
  unsigned int b, e, m;
  b = 0; e = count_points-1; m = 0;
  while(e>b){
    m = (b+e)>>1;
    if(p>x[m])
      b=m+1;
    else
      e=m;
  }
  dist = p - x[m];
  //ans = ((c4[m]*dist+c3[m])*dist+c2[m])*dist+c1[m];//better faster makes us stronger
  ans = ((c[4*m+3]*dist+c[4*m+2])*dist+c[4*m+1])*dist+c[4*m];
  return ans;
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
    
    draw->point_list_splines[i].setX(current_x);
    temp = find_spline_value(current_x);
    draw->point_list_splines[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module2 = max_module_x;
  draw->y_max_module2 = max_module_y;
  draw->max_module2 = (max_module_x < max_module_y? max_module_y: max_module_x);
}

double MyMainWindow::residual_spline(){
  int i;
  double max_module=0.0;
  double module;

  for(i= 0; i<DRAW_SIZE; ++i){
    module = fabs(draw->point_list_splines[i].y());

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
    
    draw->point_list_splines[i].setX(current_x);
    temp = find_spline_value(current_x);
    temp=f(current_x)-temp;
    if (fabs(temp)<(EPS)) temp=0.0;
    draw->point_list_splines[i].setY(temp);
    if(fabs(temp) >max_module_y)
      max_module_y = fabs(temp);
  }
  draw->x_max_module2 = max_module_x;
  draw->y_max_module2 = max_module_y;
  draw->max_module2 = (max_module_x < max_module_y? max_module_y: max_module_x);
}
