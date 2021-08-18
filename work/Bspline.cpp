#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
//#include<armadillo>
#include<vector>
using namespace std;

struct point{
	double x,y;
	point(double x = 0,double y = 0):x(x),y(y){};
};
point operator - (point a,point b)
{
    return point(a.x - b.x,a.y -b.y );
}


const double eps = 1e-10;
int  dcmp(double x)
{
    if( fabs(x) < eps )
        return  0;
    else
        return x < 0?-1:1;
}

double cross(point a, point b, point c){	// norm of the cross product of vector ab and vector ac
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dot(point a, point b, point c){		// the dot product of vector ab and vector ac
	return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

bool onsegment(point p, point a, point b){
	//	cross product = 0  	->  p,a,b are collinear
	//	dot product < 0 	->  p lies between a,b
	return dcmp(cross(p,a,b)) == 0 && dcmp(dot(p,a,b)) < 0;
}


//===================== check whether the point p is inside the jordan curve =======================================================================

int isincurve(point p, vector<point> curve)
{
    int wn = 0;
    point tmp = curve[curve.size()-1];
    curve.push_back(tmp);
    for(int i = 0; i < curve.size(); i++)
    {
        if(onsegment(p,curve[i],curve[i+1]) ){
        	curve.pop_back();
        	return -1;		//on the boundary
        }
        int k = dcmp(cross(curve[i],curve[i+1],p));
        int d1 = dcmp(curve[i].y - p.y);
        int d2 = dcmp(curve[i+1].y - p.y);
        
        if(k > 0 && d1 <= 0 && d2 > 0)	wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)	wn--;
 
    }
    curve.pop_back();
    if(wn != 0)return 1;	//inside
    return 0;				//outside
}


//========================== generate the B spline of a jordan curve ===============================================================================
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
		for(int j = 0; j <=1000; j++){
			double tmpt = j * (t[i]-t[i-1]) / 1000 + t[i-1];
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
			//cout << px << " " << py << endl;
			fit_curve.push_back(tmpp);
		}
	}
	return fit_curve;

}
int main(int argc, char const *argv[])
{
	freopen("Data000.txt","r",stdin);
	point tmp(0,0);
	cout << isincurve(tmp,draw_B_spline()) << endl;
	return 0;
}