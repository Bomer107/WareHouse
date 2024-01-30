#pragma once
#include "main.h"

using namespace std;

class Customer;
class WareHouse;

void parseString(string &line, vector <string> &command);

bool configWareHouse(WareHouse &warehouse, vector <string> &command, int lineNum);

bool executeCommand(vector <string> &command, WareHouse &warehouse);

int csti(string &s, string parameter);

size_t digits(int num);

bool addCustomerGeneral(WareHouse &warehouse, vector<string> &command, int lineNum, bool config);

void printErrorAtLine(int lineNum);

bool isValid(vector<string> &command, size_t size, int &lineNum, string &usage, bool config);