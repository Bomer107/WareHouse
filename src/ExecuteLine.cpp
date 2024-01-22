#include "../include/ExecuteLine.h"
#include "../include/Action.h"

bool executeCommand(vector <string> &command, WareHouse warehouse){
    string &the_command = command[0];

    if(the_command == "step"){
        if (command.size() != 2){
            cerr << "usage: step <number_of_steps>" << endl;
            return -1;
        }
    }

    else if(the_command == "order"){
        if (command.size() != 2){
            cerr << "usage: order <customer_id>" << endl;
            return -1;
        }
        int customer_id = csti(command[1], "customer_id");
        if(customer_id < 0){
            cerr << "customer_id has to be a non-negative number" << endl;
        }
        AddOrder * addOrder = new AddOrder(customer_id);
        addOrder->act(warehouse);
    }

    else if(the_command == "orderStatus"){
        if (command.size() != 2){
            cerr << "usage: orderStatus <order_id>" << endl;
            return -1;
        }
        int order_id = csti(command[1], "order_id");
        if(order_id < 0){
            cerr << "order_id has to be a non-negative number" << endl;
        }
        PrintOrderStatus * printOrderStatus = new PrintOrderStatus(order_id);
        printOrderStatus->act(warehouse);
    }

    else if(the_command == "customerStatus"){
        if (command.size() != 2){
            cerr << "usage: customerStatus <customer_id>" <<endl;
            return -1;
        }
        int customer_id = csti(command[1], "customer_id");
        if(customer_id < 0){
            cerr << "customer_id has to be a non-negative number" << endl;
        }
        PrintCustomerStatus * printCustomerStatus = new PrintCustomerStatus(customer_id);
        printCustomerStatus->act(warehouse);
    }

    else if(the_command == "volunteerStatus"){
        if (command.size() != 2){
            cerr << "usage: volunteerStatus <volunteer_id>" << endl;
            return -1;
        }
        int volunteer_id = csti(command[1], "volunteer_id");
        if(volunteer_id < 0){
            cerr << "volunteer_id has to be a non-negative number" << endl;
        }
        PrintVolunteerStatus * printVolunteerStatus = new PrintVolunteerStatus(volunteer_id);
        printVolunteerStatus->act(warehouse);
    }

    else if(the_command == "log"){
        if (command.size() != 1){
            cerr << "usage: log" << endl;
            return -1;
        }
        PrintActionsLog * printActionsLog = new PrintActionsLog();
        printActionsLog->act(warehouse);
    }

    else if(the_command == "close"){
        if (command.size() != 1){
            cerr << "usage: close" << endl;
            return -1;
        }
        Close * close = new Close();
        close->act(warehouse);
    }

    else if(the_command == "backup"){
        if (command.size() != 1){
            cerr << "usage: backup" << endl;
            return -1;
        }
        BackupWareHouse * backupWareHouse = new BackupWareHouse();
        backupWareHouse->act(warehouse);
    }

    else if(the_command == "restore"){
        if (command.size() != 1){
            cerr << "usage: restore" << endl;
            return -1;
        }
        RestoreWareHouse * restoreWareHouse = new RestoreWareHouse();
        restoreWareHouse->act(warehouse);
    }

    else{
        cerr << "This command isn't a valid command" << endl;
        return false;
    }

}
