#include "../include/executeLine.h"

int configWareHouse(vector <string> &command){
    if (command[0] == "customer"){
        if (command.size() != 5){
            cerr << "usage: customer <customer_name> <customer_type> <customer_distance> <max_orders>" << endl;
        }
        else if (command[2] == "solider"){
            
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

int executeCommand(vector <string> &command){
    if(command[0] == "step"){
        if (command.size() != 2){
            cerr << "usage: step <number_of_steps>" << endl;
            return -1;
        }
    }

    else if(command[0] == "order"){
        if (command.size() != 2){
            cerr << "usage: order <customer_id>" << endl;
            return -1;
        }
    }

    else if(command[0] == "orderStatus"){
        if (command.size() != 2){
            cerr << "usage: orderStatus <order_id>" << endl;
            return -1;
        }
    }

    else if(command[0] == "customerStatus"){
        if (command.size() != 2){
            cerr << "usage: customerStatus <customer_id>" <<endl;
            return -1;
        }
    }

    else if(command[0] == "volunteerStatus"){
        if (command.size() != 2){
            cerr << "usage: volunteerStatus <volunteer_id>" << endl;
            return -1;
        }
    }

    else if(command[0] == "log"){
        if (command.size() != 1){
            cerr << "usage: log" << endl;
            return -1;
        }
    }

    else if(command[0] == "close"){
        if (command.size() != 1){
            cerr << "usage: close" << endl;
            return -1;
        }
    }

    else if(command[0] == "backup"){
        if (command.size() != 1){
            cerr << "usage: backup" << endl;
            return -1;
        }
    }

    else if(command[0] == "restore"){
        if (command.size() != 1){
            cerr << "usage: restore" << endl;
            return -1;
        }
    }

}
