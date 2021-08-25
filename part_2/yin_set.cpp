

#include<iostream>


#include<cmath>
#include<vector>
#ifndef __YINSET_H__
#define __YINSET_H__
using namespace std;

#ifndef __EPS__
#define __EPS__

const double eps = 1e-10;

#endif




struct point{
	double x,y;
	point(double x = 0,double y = 0):x(x),y(y){};
};
point operator - (point a,point b)
{
    return point(a.x - b.x, a.y - b.y);
}


int  dcmp(double x)
{
    if( fabs(x) < eps )
        return  0;
    else
        return x < 0?-1:1;
}

double cross(point a, point b){	// norm of the cross product of vector ab and vector ac
	return a.x*b.y - a.y*b.x;
}

double dot(point a, point b, point c){		// the dot product of vector ab and vector ac
	return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}
int isincurve(point p, vector<point> curve)
{
    int wn = 0;
    int n = curve.size();
    for(int i = 0; i < n; i++){
        //if(onsegment(p,curve[i],curve[(i+1)%n]) )		return -1;		//on the boundary
        int k = dcmp(cross(curve[(i+1)%n]-curve[i],p-curve[i]));
        int d1 = dcmp(curve[i].y - p.y);
        int d2 = dcmp(curve[(i+1)%n].y - p.y);
        
        if(k > 0 && d1 <= 0 && d2 > 0)	
        	wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)	
        	wn--;
 
    }
    if(wn != 0)return 1;	//inside
    return 0;				//outside
}
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

//------------------------------------------------------------------------------------------------------------------














//------------------------------------------------------------------------------------------------------------------
class yinset{

private:
	vector<vector<point> > curves;
	vector<int> orientation;
	int size;
	bool has_emptycurve;
	int** inclusion;
	void set_size(){
		size = curves.size();
	}
	void set_inclusion();
	void set_orientation();
public:
	void acquire(vector<vector<point> > cur);
	void show_orientation();
	void show_inclusion();
	void ori_inverse(int i);
	yinset intersect(yinset yin1, yinset yin2);
	yinset uunion(yinset yin1, yinset yin2);
	yinset exterior(yinset yin);
};

//------------------------------------------------------------------------------------------------------------------


void yinset::set_inclusion(){
	inclusion = new int*[size];
	for(int i = 0; i < size; i++){
		inclusion[i] = new int[size];
		for(int j = 0; j < size; j++){
			if(isincurve(curves[i][0],curves[j]) == 1)
				inclusion[i][j] = 1;
			else
				inclusion[i][j] = 0;
			if(i == j)
				inclusion[i][j] = 0;
		}
	}
}

void yinset::set_orientation(){
	for(int i = 0; i < size; i++){
		int sum = 0;
		for(int j = 0; j < size; j++)
			sum += inclusion[i][j];
		orientation.push_back(sum);
		//show_orientation();
	}
}

void yinset::acquire(vector<vector<point> > cur){
	curves = cur;
	set_size();
	for(int i = size-1; i > 0; i--)
		if(curves[i].size() == 0){
			cout << "Error: empty curve" << endl;
			has_emptycurve = true;
			return;
		}
	set_inclusion();
	set_orientation();
}

void yinset::show_orientation(){
	for(int i = 0; i < size; i++)
		cout << orientation[i] << " ";
	cout << endl;
}

void yinset::show_inclusion(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
			cout << inclusion[i][j] << ", ";
		cout << endl;
	}
}

void yinset::ori_inverse(int i){
	orientation[i] = 1 - orientation[i];
}

yinset yinset::uunion(yinset yin1, yinset yin2){
	yinset return_val;
	vector<vector<point> > return_curve;


	//return_curve.push_back(curve_union(yin1.curves[i],yin2.curves[j]));
	//return_curve.push_back()
	return_val.acquire(return_curve);
	return return_val;
}

yinset yinset::intersect(yinset yin1, yinset yin2){
	yinset return_val;
	vector<vector<point> > return_curve;
	return_val.acquire(return_curve);
	return return_val;
}

yinset yinset::exterior(yinset yin){
	yinset return_val = yin;
	for(int i = 0; i < yin.size; i++)
		return_val.ori_inverse(i);
	return return_val;
}

#endif


//------------------------------------------------------------------------------------------------------------------


int main(int argc, char const *argv[])
{
	vector <vector<point> > jordan_curves;
	int n = 15;		// number of jordan curves
	for(auto i = 0; i < n; i++){

		//input of jordan curves, tmp_inpath/tmp_outpath determined by the path of input/output files
		string tmp_inpath = "./data/Data000.txt";string tmp_outpath = "./plots/output000.txt";
		tmp_inpath[12] += i / 10;
		tmp_outpath[15] = tmp_inpath[12];
		tmp_inpath[13] += i % 10;
		tmp_outpath[16] = tmp_inpath[13];
		const char* inpath = nullptr;
		const char* outpath = nullptr;
		inpath = tmp_inpath.c_str();
		outpath = tmp_outpath.c_str();
		freopen(inpath,"r",stdin);
		freopen(outpath,"w",stdout);
		jordan_curves.push_back(draw_B_spline());
		cin.clear();
		cout.clear();
	}


	/*
	freopen("out.txt","w",stdout);
	yinset set;
	set.acquire(jordan_curves);
	set.show_orientation();*/
	return 0;
}
