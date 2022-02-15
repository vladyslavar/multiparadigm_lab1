#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;

int main()
{
	map<string, vector<int>> words;
	vector<int> mislints;
	string wholeText;
	string recText;
	int lineindexer = 0;
	int pagesCount = 1;
	int iter1 = 0;

	smatch match;
	regex reg("(\\w+)");
	string matchSTR;
	

	ifstream MyFile("longText.txt");

	if (!MyFile.is_open()) {
		cout << "File was not opened" << endl;
	}
ReadFromFile:
	if (!MyFile.eof()) goto StartReadFromFile;
	else goto EndReadFromFile;
StartReadFromFile:
	if (lineindexer < 45) // 45 is lines in page
	{
		getline(MyFile, recText);
		if (recText.empty()) {
			goto StartReadFromFile;
		}
	RegxGo:
		if (regex_search(recText, match, reg))
		{
			matchSTR = match.str();
			transform(matchSTR.begin(), matchSTR.end(), matchSTR.begin(), ::tolower);
			if (words.find(matchSTR) == words.end())
			{
				words[matchSTR] = vector<int>();
			}
			words[matchSTR].push_back(pagesCount);
			recText = match.suffix();
			goto RegxGo;
		}
		lineindexer++;
		pagesCount++;
	}
	lineindexer = 0;
	goto ReadFromFile;
EndReadFromFile:
	
	map <string, vector<int>>::iterator it = words.begin();
	map <string, vector<int>>::iterator itSaved;
CheckCount:
	if (it != words.end())
	{
		itSaved = it;
		it++;
		if (itSaved->second.size() > 100) words.erase(itSaved->first);
		goto CheckCount;
	}

	map <string, vector<int>>::iterator itt = words.begin();
	int jeter = 0;
	int keter = 0;
OuterDelete:
	if (jeter < words.size())
	{
	InnerDelete:
		if (keter < itt->second.size() - 1)
		{
			if (itt->second[keter] == itt->second[keter + 1])
				itt->second.erase(itt->second.begin() + keter);
			else
				keter++;
			goto InnerDelete;
		}
		keter = 0;
		itt++;
		jeter++;
		goto OuterDelete;
	}
	int anothiter = 0;
	map <string, vector<int>>::iterator ittt = words.begin();
OOut:
	if (ittt != words.end())
	{
		cout << ittt->first << " : ";
	IOut:
		if (anothiter < ittt->second.size())
		{
			cout << ittt->second[anothiter] << " ";
			anothiter++;
			goto IOut;
		}
		anothiter = 0;
		cout << endl;
		ittt++;
		goto OOut;
	}
		cout << endl;
}
