#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class icalSubject
{
private:
	string name;
	int hours;
	int minutes;
	int events;
public:
	icalSubject(string name0){name=name0;hours=0;minutes=0;events=0;}
	bool isthis(string name0)	{
		return name0.compare(name)==0;
	}
	void addtime(int hs,int ms)
	{
		hours+=hs;
		minutes+=ms;
		events++;
	}
//	void print(){cout<<name<<" : "<<hours<<" hours and "<<minutes<<" minutes in"<<events<<" events"<<endl;}
	void print()
	{
		//printf("%.25s : %d hours and %d minutes in %d events\n",name,hours,minutes,events);
		printf("%3d hours and %3d minutes in %3d events",hours,minutes,events);
		cout<<" for "<<name<<endl;
	}
};

class icalHours
{
private:
	vector<icalSubject> ical;
public:
	icalHours(){ical=vector<icalSubject>();}
	icalSubject *search(string name0)
	{
		for (int i=0;i<ical.size();i++)
			if (ical[i].isthis(name0))
				return &ical[i];
		icalSubject newics(name0);
		ical.push_back(newics);
		return &newics;
	}
	void printResult()
	{
		for (int i=0;i<ical.size();i++)
			ical[i].print();
	}
};

int main(int argc, char *argv[])
{
	string infile		= argv[1];
	ifstream inpt(infile);
	if (!inpt.is_open())
	{
		cout<<"Error: unable to open file '"<<infile<<"'"<<endl;
		return 1;
	}
	string line;
	icalHours ich;

	int hours=0,minutes=0,hl,ml;
	int events=0;
	do
	{
		getline(inpt,line);
		//Check if this is a start time
		if (line.substr(0,7).compare("DTSTART")==0)
		{
			//Read hours and minutes of the start time
			
			hl=stoi(line.substr(17,2));
			ml=stoi(line.substr(19,2));
			//Read next line for the end time
			getline(inpt,line);
			
			hl-=stoi(line.substr(15,2));
			ml-=stoi(line.substr(17,2));
			//Get the name of the event
			getline(inpt,line);
			line=line.substr(8,line.length()-1);
			ich.search(line)->addtime(-hl,-ml);
			//Add up the hours and minutes
			hours  -=hl;
			minutes-=ml;
			events++;
		}
	}while(!inpt.eof());
	cout<<"Total: "<<hours<<" hours and "<<minutes<<" minutes, in "<<events<<" events"<<endl;
	ich.printResult();
	getchar();
}