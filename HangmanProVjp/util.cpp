#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

#include "util.h"

using namespace std;

string upperSTR(const string& s)
{
    string newS = s;
    for (int i = 0;i < newS.size();i++)
        if (newS[i] >= 'a' && newS[i] <= 'z')
            newS[i] += 32;
    return newS;
}

string chooseWord(const string& fileName, int difficult)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return "";
    while (!file.eof()) 
    {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(upperSTR(line));
    }

    vector<string> filter;
    for (const auto& word : vocabulary)
        if ((word.length() <= 4 && difficult==1) || (word.length() > 4 && difficult==2) || (difficult==3))
            filter.push_back(word);
    if (filter.empty())
        return "";
    else
    {
        string res = filter[rand() % filter.size()];
        return res;
    }
}

bool contains(string word,char guess)
{
    return(word.find(guess) != string::npos);
}

