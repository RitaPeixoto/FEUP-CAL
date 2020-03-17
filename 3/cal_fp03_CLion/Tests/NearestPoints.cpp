/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2)-> it is O(n^2) because we have a for inside a for both iterating over a vector of size n
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;
	for(int i=0; i<vp.size();i++){
	    for(int j=i+1;j<vp.size();j++){
	        double distance = vp[i].distance(vp[j]);//distance between the two points
	        if(distance<res.dmin){//verifies if the new distance is smaller
	            res.p1 = vp[i];
	            res.p2 = vp[j];
                res.dmin = distance;//updates with the new minimum distance
	        }
	    }
	}
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	sortByX(vp, 0, vp.size()-1);
	return nearestPoints_BF(vp);
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
	for(int i = left; i<= right; i++){
	    for(int j= left+1; j<=right; j++){
	        double distance = vp[i].distance(vp[j]);
	        if(distance>=res.dmin){
	            break;
	        }
	        else if(distance<res.dmin){
	            res.p1= vp[i];
	            res.p2 = vp[j];
	            res.dmin = vp[i].distance(vp[j]);
	        }
	    }
	}
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	Result res;
    // Base case of two points
	if(abs(left-right)==1){
	    res.p1 = vp[left];
	    res.p2 = vp[right];
	    res.dmin = vp[left].distance(vp[right]);
        return res;
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if(abs(left-right)==0){
        res.p1 = vp[left];
        res.p2 = vp[right];
	    res.dmin = MAX_DOUBLE;
	    return res;
	}
	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	//first we calcullate the middle index
	int middle = left + abs(left-right)/2.0;

	//we're going to have two results  auxiliar results
	Result auxLeft, auxRight;
	if(numThreads<=1){// if we can only use 1 thread
	    auxLeft = np_DC(vp,left,middle,numThreads);
	    auxRight = np_DC(vp,middle+1, right, numThreads);//we have to add one because the middle point is includade in the left half
	}
	else{
	    std:: thread t([&vp,&auxLeft,left,middle, numThreads]{
	        vector <Point> v(vp);
            auxLeft = np_DC(v,left,middle,numThreads/2.0);
	    });
        auxRight = np_DC(vp,middle+1, right, numThreads/2.0);//we have to add one because the middle point is includade in the left half
	    t.join();
	}

	// Select the best solution from left and right, the smaller is the better one
	if(auxLeft.dmin<auxRight.dmin){
	    res = auxLeft;
	}
	else
	    res = auxRight;

	// Determine the strip area around middle point
	vector<Point> strip;//vector where we will add all the points that can belong to the strip
	for(int i=left; i<= right; i++){
	    if(abs(vp[middle].x-vp[i].x)<=res.dmin){//if this happens it means it can belong to the strip area
            strip.push_back(vp[i]);
	    }
	}

	// Order points in strip area by Y coordinate
	sortByY(strip,0,strip.size()-1);

	// Calculate nearest points in strip area (using npByY function)
	npByY(strip,0,strip.size()-1,res);

	// Reorder points in strip area back by X coordinate
	sortByX(strip,0,strip.size()-1);

	return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
