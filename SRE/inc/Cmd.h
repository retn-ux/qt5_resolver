#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using std::map;
using std::vector;
using std::string;
using std::find;
using std::pair;

		
map<string, vector<string>> GetArgs(char** argv, int argc, vector<string> &list);
map<string, vector<string>> GetArgs(vector<string> args, vector<string>& list);



