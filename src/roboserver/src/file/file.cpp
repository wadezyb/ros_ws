#include "file.h"
#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include "../link/robolink.h"
using namespace std;

void fileRun(void)
{
	ifstream in;
	in.open("/home/path.txt");
	int a,b,c,d;
	char str[100];
	if(in.is_open())
	{
		while(!in.eof())
		{
			in.getline(str,100);
			sscanf(str,"%d %d %d %d",&a,&b,&c,&d);
			sendIPM(a,b,c,d);
		}
	}
}
