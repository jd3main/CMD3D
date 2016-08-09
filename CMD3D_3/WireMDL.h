#ifndef WIREMDL_H
#define WIREMDL_H


#include<fstream>
#include<vector>
#include"CMD3D_Math.h"

using namespace std;

typedef Vec4 Point;


bool getTheChar(ifstream &file, char c)
{
	char x;
	while(1)
	{
		if(!file.get(x))
			return false;
		if(x==c)
			return true;
	}
}

struct WMDL
{
	vector<Vec4> point;
	
	void Load(const char *file_name)
	{
		ifstream file(file_name);
		if(!file)
		{
			cout << "File not Found\n";
			return;
		}
		Vec4 p;
		bool going = true;
		while(going)
		{
			if(!getTheChar(file,'('))
				break;
			file >> p.x;
			if(!getTheChar(file,','))
				break;
			file >> p.y;
			if(!getTheChar(file,','))
				break;
			file >> p.z;
			if(!getTheChar(file,')'))
				break;
			p.w = 1;
			point.push_back(p);
		}
	}
	
	
	WMDL(){};
	WMDL(const char* file_name){
		point.clear();
		Load(file_name);
	};
};
















#endif
