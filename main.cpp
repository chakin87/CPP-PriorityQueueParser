/* to use this, 
     - write a form that calls this program with 'action=' in the <form> tag
     - call getPostData() 
     - use getField(string) to access form information 

*/
#include <iostream>
#include <cstdlib>
#include <queue>
#include <functional>
#include <vector>
#include <string>
#include "htmlform.h"
#include "prioritystring.hpp"

void printProgram(std::string program);   /// print the program in HTML
void parseProgram(std::vector<std::string> str);


using namespace std;

int main()
{
  /// complete the http header
  cout << "Content-type: text/html\n\n";

  /// build a form object
  HTMLform steps;
  steps.getPostData();

  /// Show the debugging
  cout << "Priority Queue Parser Lab startup" << endl;
  steps.debug();

  

  /// the entire programs
  string program = steps.getField("program");
  
  printProgram(program);
  
  //The next line is for you to complete
  //parseProgram(program);

  std::string pause;

  std::cin >> pause;

  return 0;
}

void printProgram(std::string program)
{

	/// a single line
	string line;
	/// for counting the lines
	int count = 0;
	/// where the newline is (for peeling off a line)
	int pos;

	program += " \n";

	std::vector<std::string> str, method;

	while (string::npos != (pos = program.find("\n"))) {
		line = program.substr(0, pos);    /// before the newline

		program = program.substr(pos + 1);  /// after the newline
		/// there might newline characters at the end of line
		if (line[pos] < '0') line.erase(pos - 1);


		/// here's where you need to process 'line'
		/// this routine just prints it.
		str.push_back(line.substr(0, line.find("\n")));

	}

	parseProgram(str);

};


void parseProgram(std::vector<std::string> str){

	typedef std::priority_queue<PriorityString, std::vector<PriorityString>, PriorityStringComparison>  pq;

	pq p;

	std::string strCheck;
	std::string strNum = "";
	std::string strParser;
	std::string strData;
	std::string strMethod;
	int iNum;
	int numOfPushes = 0;


	strMethod = str[str.size() - 1];

	for (unsigned int i = 0; i < str.size(); ++i) {
		strNum = "";
		strCheck = str[i].substr(0, str[i].find(" "));
		strParser = str[i].substr(0, str[i].find(","));
		if (strParser.length() == 7) {
			strNum += strParser.at(5);
			strNum += strParser.at(6);
			strData = str[i].substr(9, str[i].find("\n"));
		}
		else if (strParser.length() == 6) {
			strNum += strParser.at(5);
			strData = str[i].substr(8, str[i].find("\n"));
		}
		iNum = atoi(strNum.c_str());
		if (strCheck == "PUSH") {
			++numOfPushes;
			//std::cout << iNum << "  inum   :   strData   " << strData << "<br />";
			p.push(PriorityString{ iNum, strData });
		}
		else if (strCheck == "TOP") { std::cout << p.top().priority << ", " << p.top().data << "<br />"; }
		else if (strCheck == "DUMP") {
			for (unsigned int i = 0; i < numOfPushes; ++i) {
				std::cout << p.top().priority << ", " << p.top().data << "<br />";
				p.pop();
			}
		}
		else if (strCheck == "NAME") { std::cout << "Ken Urban<br />"; }
		else {
			std::cout << "YOU MUST USE 'PUSH', 'DUMP, or 'NAME'!!! :( " << "<br />";
		}
	}

};

