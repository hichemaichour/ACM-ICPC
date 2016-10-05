#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

const double PI = 3.14159;

void findBest (const vector<double>& angles,double fieldOfView,int& maxVisible,double& bestAngle){
	vector<double> a = angles;
	copy (angles.begin(), angles.end(), back_inserter(a));
	copy (angles.begin(), angles.end(), back_inserter(a));

	for (int i = 0; i < angles.size(); ++i)
		a[i] -= 360.0;
	for (int i = 2*angles.size(); i < 3*angles.size(); ++i)
		a[i] += 360.0;

	maxVisible = 0;
	bestAngle = 0.0;
	int start = 0;

	for (int ia = 0; ia < 3600; ++ia)
	{
		double telescope = ((double)ia)/10.0;
		double lowAngle = telescope - fieldOfView / 2.0;
		double highAngle = telescope + fieldOfView / 2.0;

		while (start < 3*angles.size() && a[start] <= lowAngle)
			++start;

		int stop = start;
		while (stop < 3*angles.size() && a[stop] < highAngle)
			++stop;

		int cnt = stop - start;
		if (cnt > maxVisible) {
			maxVisible = cnt;
			bestAngle = telescope;

			/*cerr << telescope << " " << maxVisible << "  "
				<< "Low delta: " <<  a[start] - lowAngle
				<< "  High delta: " << highAngle - a[stop-1] << endl;*/
		}
	}
}



int main (int argc, char** argv){
	ifstream cin("Moths.h");
	int numTrees;
	while ((cin >> numTrees) && (numTrees > 0)){
		vector<double> angles;
		double tx, ty, field;
		cin >> tx >> ty >> field;
		for (int i = 0; i < numTrees; ++i){
			double x, y;
			cin >> x >> y;
			x -= tx;
			y -= ty;
			double angle = atan2 (x,y);
			angle = angle * 180.0 / PI;
			if (angle < 0.0)
				angle += 360.0;
			angles.push_back(angle);
		}

		sort (angles.begin(), angles.end());

		/* Debugging output
		copy (angles.begin(), angles.end(), 
		ostream_iterator<double>(cerr, " "));
		cerr << endl;
		*/

		int maxVisible;
		double camera;
		findBest (angles, field, maxVisible, camera);
		cout << "Point the camera at angle "
			<< setprecision(1) << fixed << camera 
			<< " to view " << maxVisible << " infested trees."
			<< endl;
	}
	return 0;
}