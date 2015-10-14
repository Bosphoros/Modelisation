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
	if(f.is_open) {
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
		/*while( getline(f,str) ) {

		}*/
	}
	f.close();
}

OffReader::~OffReader()
{
}
