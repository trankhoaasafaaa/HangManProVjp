#ifndef UTIL_H
#define UTIL_H

#include <string>

using namespace std;

string upperSTR(const string& s);
string chooseWord(const string& fileName,int difficult);

bool contains(string word, char guess);

#endif

