#include "OffReader.h"
#include "struct.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

OffReader::OffReader()
{
}

Mesh OffReader::import(std::string file) {
	std::vector<point3> points;
	std::vector<int> triangles;
	std::vector<point3> normales;

	ifstream f;
	f.open(file);
	if(f.is_open()) {
		string str;
		getline(f, str);
		std::cout << "Extension : " << str << std::endl;
		int vertices, faces, edges;
		getline(f,str);
		istringstream iss(str);
		std::vector<string> subs;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(subs));
		vertices = atoi(subs.at(0).c_str());
		faces = atoi(subs.at(1).c_str());
		edges = atoi(subs.at(2).c_str());
		std::cout << vertices << " / " << faces << " / " << edges << std::endl;

		for(int i = 0; i < vertices ; ++i) {
			subs.clear();
			getline(f,str);
			istringstream is(str);
			copy(istream_iterator<string>(is), istream_iterator<string>(), back_inserter(subs));
			double x = atof(subs.at(0).c_str());
			double y = atof(subs.at(1).c_str());
			double z = atof(subs.at(2).c_str());
			point3 ins(x, y, z);
			points.push_back(ins);
		}

		for(int i = 0; i < faces ; ++i) {
			subs.clear();
			getline(f,str);
			istringstream is(str);
			copy(istream_iterator<string>(is), istream_iterator<string>(), back_inserter(subs));
			int un = atoi(subs.at(1).c_str());
			int deux = atoi(subs.at(2).c_str());
			int trois = atoi(subs.at(3).c_str());
			triangles.push_back(un);
			triangles.push_back(deux);
			triangles.push_back(trois);
		}
	}
	f.close();

	Mesh m(points, triangles, normales);
	return m;
}

OffReader::~OffReader()
{
}
