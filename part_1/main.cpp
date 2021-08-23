#include<iostream>
#include<cstdio>
#include "./include/Bspline.h"
#include "./include/inclusion.h"


int main(int argc, char const *argv[])
{
	vector <vector<point> > jordan_curves;
	int n = 15;		// number of jordan curves
	for(auto i = 0; i < n; i++){

		//input of jordan curves, tmp_inpath determined by the path of input files
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
	fclose(stdin);


	freopen("inclusion.csv","w",stdout);
	// print "inclusion"
	int **inclusion = inclu_map(jordan_curves);		//	the map of inclusion of the curves
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i != j)
				cout << inclusion[i][j] << ", ";
			else cout << " , ";
		}
		cout << endl;
	}
	cout.clear();
	fclose(stdout);
	return 0;
}