#ifndef __INCLUSION_H__
#define __INCLUSION_H__

#include "Bspline.h"

//================================ algorithm realization ===========================================================================================

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
/*
bool onsegment(point p, point a, point b){
	//	cross product = 0  	->  p,a,b are collinear
	//	dot product < 0 	->  p lies between a,b
	return dcmp(cross(p,a,b)) == 0 && dcmp(dot(p,a,b)) < 0;
}*/


//===================== check whether the point p is inside the jordan curve =======================================================================

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

//========================= the inclusion of jordan curves =========================================================================================
//	Since the given Jordan curves are disjoint, then I use the "isincurve" function to judge whether a point on curve i is inside curve j, and then 
//	get the iclusion relation of the curves


int **inclu_map(vector <vector<point> > jordan_curves){
	int n = jordan_curves.size();
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

#endif