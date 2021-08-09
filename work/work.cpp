#include<iostream>
#include<cmath>
#include<cstring>
//#include<armadillo>
#include<vector>
/*
struct point_2d{
	double x,y;
};*/

using namespace std;
int main()
{
	vector<double> x,y,t;
	double tmp;int n = 335;
	freopen("Data001.txt","r",stdin);
	freopen("output.txt","w",stdout);
	for(int i = 1; i <= 335; i++){
		cin >> tmp;
		x.push_back(tmp);
		cin >> tmp;
		y.push_back(tmp);
	}
	for(int i = 1; i <= 3; i++){
		tmp = x[334];
		x.insert(x.begin(),tmp);
		tmp = y[334];
		y.insert(y.begin(),tmp);
	}
	tmp = x[3];x.push_back(tmp);tmp = x[4];x.push_back(tmp);
	tmp = y[3];y.push_back(tmp);tmp = y[4];y.push_back(tmp);
	t.push_back(0);
	for(int i = 1; i <= 339; i++)
		t.push_back(t[i-1] + sqrt(pow(x[i]-x[i-1],2) + pow(y[i]-y[i-1],2)));
	//done


	//vector<point_2d> fit_curve;
	for(int i = 3; i < 338; i++){
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
			//point_2d tmpp;
			//tmpp.x = px;tmpp.y = py;
			//cout << tmpt << endl;
			cout << px << " " << py << endl;
			//fit_curve.push_back(tmpp);
		}
	}

	return 0;
}