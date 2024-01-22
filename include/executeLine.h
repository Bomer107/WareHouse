#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Customer;
class WareHouse;

void parseString(string &line, vector <string> &command);

int configWareHouse(WareHouse &warehouse, vector <string> &command);
