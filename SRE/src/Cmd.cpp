#include "pch.h"
#include <sredefs.h>
#include <Auxiliary.h>
#include <Cmd.h>


map<string,vector<string>> GetArgs(char **argv,int argc,vector<string> &list){
	vector<string> args = CCharToString(argv, argc);
	return GetArgs(args, list);
}


map<string, vector<string>> GetArgs(vector<string> args, vector<string>& list) {
	map<string, vector<string>> argMap;
	GUARD_GENTLE(args.size() != 0, argMap);
	string old;
	bool flag = false;
	for (string mid : args) {
		vector<string>::iterator v = find(list.begin(), list.end(), mid.c_str());
		if (v != list.end()) {
			old = *v;
			vector<string> value;
			argMap.insert(pair<string, vector<string>>(old, value));
			flag = true;
		}
		else {
			if (flag == true) {
				argMap[old].push_back(mid);
			}

		}
	}
	return argMap;

}