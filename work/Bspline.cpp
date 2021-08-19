#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
//#include<armadillo>
#include<vector>
using namespace std;



//==================================== structure ===================================================================================================

#ifndef __POINT__
#define __POINT__
struct point{
	double x,y;
	point(double x = 0,double y = 0):x(x),y(y){};
};
point operator - (point a,point b)
{
    return point(a.x - b.x,a.y -b.y );
}
#endif

//================================= algorithm ======================================================================================================

vector<point> draw_B_spline();
int  dcmp(double x);
double cross(point a, point b, point c);
double dot(point a, point b, point c);
bool onsegment(point p, point a, point b);
int isincurve(point p, vector<point> curve);
vector<point> draw_B_spline();

//================================ algorithm realization ===========================================================================================

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

//========================= the inclusion of jordan curves =========================================================================================
//	Since the given Jordan curves are disjoint, then I use the "isincurve" function to judge whether a point on curve i is inside curve j, and then 
//	get the iclusion relation of the curves


int **inclu_map(vector <vector<point> > jordan_curves){
	int n = jordan_curves.size();
	//cout << n << endl;
	int **inclusion;	// the inclusion of these jordan curves, initialized as 0, inclusion[i][j] = 1 represents that curve i is inside curve j
	inclusion = new int*[n];
	for(int i = 0; i < n; i++){
		inclusion[i] = new int[n];
		for(int j = 0; j < n; j++){
			if(isincurve(jordan_curves[i][0],jordan_curves[j]) == 1)
				inclusion[i][j] = 1;
			else
				inclusion[i][j] = 0;
			if(i == j)
				inclusion[i][j] = -1;
		}
	}
	return inclusion; 
}

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
		for(int j = 0; j <1000; j++){
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
			cout << px << " " << py << endl;
			fit_curve.push_back(tmpp);
		}
	}
	return fit_curve;

}

int main(int argc, char const *argv[])
{
	vector <vector<point> > jordan_curves;
	int n = 15;		// number of jordan curves
	for(auto i = 0; i < n; i++){

		//input of jordan curves, tmp_inpath determined by the path of input files
		string tmp_inpath = "Data000.txt";
		tmp_inpath[5] += i / 10;
		tmp_inpath[6] += i % 10;
		const char* inpath = nullptr;
		inpath = tmp_inpath.c_str();
		outpath = tmp_outpath.c_str();
		freopen(inpath,"r",stdin);
		jordan_curves.push_back(draw_B_spline());
		cin.clear();
		//cout << jordan_curves[i].size() << endl;
	}
	fclose(stdin);
	int **inclusion = inclu_map(jordan_curves);
	/*freopen("inclusion.csv","w",stdout);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i != j)
				cout << inclusion[i][j] << ", ";
			else cout << " , ";
		}
		cout << endl;
	}
	cout.clear();*/
	//cout << isincurve(jordan_curves[13][0],jordan_curves[2]) << endl << isincurve(jordan_curves[2][0],jordan_curves[13]) << endl;
	//cout << jordan_curves.size() << endl <<  "done" << endl;
	return 0;
}
