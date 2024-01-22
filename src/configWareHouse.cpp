#include "../include/WareHouse.h"
#include "../include/Action.h"

int configWareHouse(WareHouse &warehouse, vector<string> command){
    if (command[0] == "customer"){
        if (command.size() != 5){
            cerr << "usage: customer <customer_name> <customer_type> <customer_distance> <max_orders>" << endl;
        }
        else if (command[2] == "solider"){
            //warehouse.AddCustomer(new Customer())
        }
        else if (command[2] == "civilian"){
            
        }
        else{
            cerr << "usage: customer <customer_name> <solider / civilian> <customer_distance> <max_orders>" << endl;
        }
    }

    else if(command[0] == "volunteer"){

    }
}