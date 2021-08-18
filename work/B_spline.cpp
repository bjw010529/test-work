#include<iostream>
#include<cmath>
#include<cstring>
//#include<armadillo>
#include<vector>
using namespace std;

struct point_2d{
	double x,y;
};
const double eps = 1e-10;
int  dcmp(double x)
{
    if( fabs(x) < eps )
        return  0;
    else
        return x < 0?-1:1;
}

int isinpoly(point_2d p,vector<point_2d> poly)
{
    int wn=0;
    int n=poly.size();
    for(int i=0;i<n;i++)
    {
        if(onseg(p,poly[i],poly[(i+1)%n])) return -1;   //在边界上
        int k=dcmp(cross(poly[(i+1)%n]-poly[i],p-poly[i]));
        int d1=dcmp(poly[i].y-p.y);
        int d2=dcmp(poly[(i+1)%n].y-p.y);
        if(k>0 && d1<=0 && d2>0) wn++;
        if(k<0 && d2<=0 && d1>0) wn--;
    }
    if(wn!=0) return 1;     //内部
    return 0;               //外部
}

void draw_B_spline()
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
	//done


	vector<point_2d> fit_curve;
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
			point_2d tmpp;
			tmpp.x = px;tmpp.y = py;
			//cout << tmpt << endl;
			//cout << px << " " << py << endl;
			fit_curve.push_back(tmpp);
		}
	}

	//return 0;
}
int main(int argc, char const *argv[])
{
	freopen("Data000.txt","r",stdin);
	//freopen("output000.txt","w",stdout);
	draw_B_spline();
	return 0;
}