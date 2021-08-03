#include<iostream>
#include<cmath>
#include<cstring>
//#include<armadillo>
#include<vector>


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
	tmp = x[0];x.push_back(tmp);tmp = x[1];x.push_back(tmp);tmp = x[2];x.push_back(tmp);
	tmp = y[0];y.push_back(tmp);tmp = y[1];y.push_back(tmp);tmp = y[2];y.push_back(tmp);
	t.push_back(0);
	for(int i = 1; i <= 337; i++)
		t.push_back(t[i-1] + sqrt(pow(x[i]-x[i-1],2) + pow(y[i]-y[i-1],2)));
	
	

	return 0;
}