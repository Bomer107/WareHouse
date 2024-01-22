#include "../include/WareHouse.h"
#include "../include/ExecuteLine.h"

bool configWareHouse(WareHouse &warehouse, vector<string> &command, int lineNum){
    string & the_command = command[0];

    if (the_command == "customer"){
        string usage = "usage: customer <customer_name> <customer_type: solider/civilian> <customer_distance> <max_orders>";
        if (!isValid(command, 5, lineNum, usage)){
            return false;
        }
        string & customer_name = command[1];
        string & customer_type = command[2];
        int customer_distance = csti(command[3], "customer distance");
        int max_orders = csti(command[4], "max_orders");

        if(customer_distance < 1 || max_orders < 1){
            return false;
        }
        
        if (customer_type == "solider"){
            warehouse.addCustomer
            (new SoldierCustomer(warehouse.getNumCustomers(), customer_name, customer_distance, max_orders));
            return true;
        }
        else if (customer_type == "civilian"){
            warehouse.addCustomer
            (new CivilianCustomer(warehouse.getNumCustomers(), customer_name, customer_distance, max_orders));
            return true;
        }
        else{
            printError(lineNum);
            cerr << usage << endl;
            return false;
        }
    }

    else if(the_command == "volunteer"){
        string & name = command[1];
        string & volunteer_role = command[2];

        if(volunteer_role == "collector"){
            string usage = "usage: volunteer <volunteer_name> collector <volunteer_cooldown>";

            if (!isValid(command, 4, lineNum, usage)){
                return false;
            }

            int cooldown = csti(command[3], "volunteer_cooldown");
            if(cooldown < 1){
                return false;
            }
            warehouse.addVolunteer(new CollectorVolunteer(warehouse.getNumVolunteers(), name, cooldown));
            return true;
        }

        else if(volunteer_role == "limited_collector"){
            string usage = "usage: volunteer <volunteer_name> limited_collector <volunteer_cooldown> <volunteer_maxOrders>";

            if (!isValid(command, 5, lineNum, usage)){
                return false;
            }
            int cooldown = csti(command[3], "volunteer_cooldown");
            int maxOrders = csti(command[4], "volunteer_maxOrders");
            if(cooldown < 1 || maxOrders < 1){
                return false;
            }
            warehouse.addVolunteer
            (new LimitedCollectorVolunteer(warehouse.getNumVolunteers(), name, cooldown, maxOrders));
            return true;
        }

        else if(volunteer_role == "driver"){
            string usage = "usage: volunteer <volunteer_name> driver <volunteer_maxDistance> <distance_per_step>";

            if (!isValid(command, 5, lineNum, usage)){
                return false;
            }

            int maxDistance = csti(command[3], "volunteer_maxDistance");
            int distance_per_step = csti(command[4], "distance_per_step");
            if(maxDistance < 1 || distance_per_step < 1){
                return false;
            }
            warehouse.addVolunteer(new DriverVolunteer(warehouse.getNumVolunteers(), name, maxDistance, distance_per_step));
            return true;
        }

        else if(volunteer_role == "limited_driver"){
            string usage = "usage: volunteer <volunteer_name> limited_driver <volunteer_maxDistance> <distance_per_step> <volunteer_maxOrders>";

            if (!isValid(command, 6, lineNum, usage)){
                return false;
            }

            int maxDistance = csti(command[3], "volunteer_maxDistance");
            int distance_per_step = csti(command[4], "distance_per_step");
            int maxOrders = csti(command[5], "volunteer_maxOrders");
            if(maxDistance < 1 || distance_per_step < 1 || maxOrders < 1){
                return false;
            }
            warehouse.addVolunteer
            (new LimitedDriverVolunteer(warehouse.getNumVolunteers(), name, maxDistance, distance_per_step, maxOrders));
            return true;
        }
        
        else{
            printError(lineNum);
            cerr << "The volunteer role can only be: collector/ limited_collector/ driver/ limited_driver" << endl;
        }
        

    }

    else{
        printError(lineNum);
        cerr << "You can only add volunteer and customer in your configuration file" << endl;
        return false;
    }
}

// Convert String To Int
int csti(string &s, string parameter){
    try{
        int x = stoi(s);
        if(digits(x) != s.size()){
            cout << parameter << " has to be a positive integer" << endl;
            return -1;
        }
        return x;
    }
    catch(invalid_argument){
        cout << parameter << " has to be an integer" << endl;
        return -1;
    }
}

// created because of stoi behaviors
int digits(int num){
    int digits = 0;
    while (num != 0){
        num /= 10;
        digits++;
    }
    return digits;
}

void printError(int lineNum){
    cerr << "The command at line: " << lineNum << ", isn't a valid command" << endl;
}

bool isValid(vector<string> &command, int size, int &lineNum, string &usage){
    if (command.size() != size){
        printError(lineNum);
        cerr << usage << endl;
        return false;
    }
    return true;
}