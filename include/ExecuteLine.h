#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Customer;
class WareHouse;

void parseString(string &line, vector <string> &command);

bool configWareHouse(WareHouse &warehouse, vector <string> &command, int lineNum);

bool executeCommand(vector <string> &command, WareHouse warehouse);

int csti(string &s, string parameter);

int digits(int num);
