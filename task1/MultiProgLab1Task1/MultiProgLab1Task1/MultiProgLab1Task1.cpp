#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;

int main()
{
	vector<string> words;
	string wholeText;
	string recText;

	//read from file
	ifstream MyFile("someText.txt");

	if (!MyFile.is_open()) {
		cout << "File was not opened" << endl;
	}
	
ReadFromFile:
	if (!MyFile.eof())
	{
		getline(MyFile, recText);
		if (!recText.empty()) {
			wholeText += recText;
			wholeText += " ";
		}
		goto ReadFromFile;
	}
	MyFile.close();

	//regex parse
	smatch match;
	regex reg("(\\w+)");
	string matchSTR;
RegxGo:
	if (regex_search(wholeText, match, reg))
	{
		matchSTR = match.str();
		transform(matchSTR.begin(), matchSTR.end(), matchSTR.begin(), ::tolower);
		words.push_back(matchSTR);
		wholeText = match.suffix();
		goto RegxGo;
	}

	// count words
	vector<string> notWords = { "the", "a", "an", "to", "in", "with", "for", "at", "on", "and"};
	map<string, int> wordsCount;
	string currword;
	int numOfwords = words.size();
	int numOfNotWords = notWords.size();
	int niter = 0;
	int iter = 0;
	bool isWord = true;
CountWords:
	if (iter < numOfwords)
	{
		currword = words[iter];
	NotWordsFlag:
		if (niter < numOfNotWords)
		{
			if (currword == notWords[niter]) isWord = false;
			niter++;
			goto NotWordsFlag;
		}
		niter = 0;

		if (isWord)
		{
			if (wordsCount.find(currword) != wordsCount.end())
				wordsCount[currword] ++;
			else
				wordsCount[currword] += 1;
		}
		isWord = true;
		iter++;
		goto CountWords;
	}

	// sort map
	pair<string, int> max;
	int i = 0;
	int orig_size = wordsCount.size();
	std::map<string, int>::iterator iterat;
SortGo:
	if (i < orig_size)
	{
		max = { "", -1 };
		iterat = wordsCount.begin();
	SearchMax:
		if (iterat != wordsCount.end())
		{
			if (iterat->second > max.second) {
				max = *iterat;
			}
			iterat++;
			goto SearchMax;
		}
		cout << max.first << " : " << max.second << endl;
		wordsCount.erase(max.first);
		i++;
		goto SortGo;
	}
	cout << endl;
		
}

