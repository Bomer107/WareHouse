#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void parseString(string &line, vector <string> &command);

void executeCommand(vector <string> &command, bool initial);