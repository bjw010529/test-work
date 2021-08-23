#ifndef __BSPLINE_H__
#define __BSPLINE_H__


#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;

//==================================== structure ====================================================================================================

#ifndef __POINT__
#define __POINT__
struct point{
	double x,y;
	point(double x = 0,double y = 0):x(x),y(y){};
};
point operator - (point a,point b)
{
    return point(a.x - b.x, a.y - b.y);
}
#endif

//==================================== constant =====================================================================================================

#ifndef __EPS__
#define __EPS__

const double eps = 1e-10;

#endif

//==================================== algorithm ====================================================================================================

vector<point> draw_B_spline();
int  dcmp(double x);
double cross(point a, point b);
double dot(point a, point b, point c);
//bool onsegment(point p, point a, point b);
int isincurve(point p, vector<point> curve);
vector<point> draw_B_spline();

//========================== generate the B spline of a jordan curve ===============================================================================
//	I design this part to directly scan data from input file and generate its B_spline
vector<point> draw_B_spline()	
{
	vector<double> x,y,t;
	double tmp1,tmp2,tmp;int n = 0;
	while(scanf("%lf%lf",&tmp1,&tmp2)!=EOF){
		x.push_back(tmp1);
		y.push_back(tmp2);
		n++;
	}
	for(int i = 1; i <= 3; i++){
		tmp = x[n-1];
		x.insert(x.begin(),tmp);
		tmp = y[n-1];
		y.insert(y.begin(),tmp);
	}
	tmp = x[3];x.push_back(tmp);tmp = x[4];x.push_back(tmp);
	tmp = y[3];y.push_back(tmp);tmp = y[4];y.push_back(tmp);
	t.push_back(0);
	for(int i = 1; i <= n+4; i++)
		t.push_back(t[i-1] + sqrt(pow(x[i]-x[i-1],2) + pow(y[i]-y[i-1],2)));


	vector<point> fit_curve;
	for(int i = 3; i < n+3; i++){
		for(int j = 0; j <100; j++){
			double tmpt = j * (t[i]-t[i-1]) / 100 + t[i-1];
			double p1 = pow(tmpt-t[i-1],3) / ((t[i+2]-t[i-1])*(t[i+1]-t[i-1])*(t[i]-t[i-1]));

			double p2 = pow(tmpt-t[i-1],2)*(t[i+2]-tmpt) / ((t[i+2]-t[i-1])*(t[i]-t[i-1])*(t[i+1]-t[i-1])) 
						+ pow(tmpt-t[i-2],2)*(t[i]-tmpt) / ((t[i+1]-t[i-2])*(t[i]-t[i-2])*(t[i]-t[i-1])) 
						+ (t[i+1]-tmpt)*(tmpt-t[i-1])*(tmpt-t[i-2]) / ((t[i+1]-t[i-1])*(t[i]-t[i-1])*(t[i+1]-t[i-2]));

			double p3 = pow(tmpt-t[i],2)*(tmpt-t[i-3]) / ((t[i]-t[i-3])*(t[i]-t[i-2])*(t[i]-t[i-1]))
						+ (t[i+1]-tmpt)*(tmpt-t[i-2])*(t[i]-tmpt) / ((t[i]-t[i-2])*(t[i]-t[i-1])*(t[i+1]-t[i-2]))
						+ pow(t[i+1]-tmpt,2)*(tmpt-t[i-1]) / ((t[i+1]-t[i-2])*(t[i+1]-t[i-1])*(t[i]-t[i-1]));

			double p4 = pow(t[i]-tmpt,3) / ((t[i]-t[i-3])*(t[i]-t[i-2])*(t[i]-t[i-1]));


			double px = (x[i]*p1+x[i-1]*p2+x[i-2]*p3+x[i-3]*p4)/(p1+p2+p3+p4);
			double py = (y[i]*p1+y[i-1]*p2+y[i-2]*p3+y[i-3]*p4)/(p1+p2+p3+p4);
			point tmpp;
			tmpp.x = px;tmpp.y = py;
			//cout << tmpt << endl;
			cout << px << " " << py << endl;
			fit_curve.push_back(tmpp);
		}
	}
	return fit_curve;

}

#endif