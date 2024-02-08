#include "../include/WareHouse.h"
#include "../include/ExecuteLine.h"

bool configWareHouse(WareHouse &warehouse, vector<string> &command, int lineNum){
    string & the_command = command[0];

    if (the_command == "customer"){
        addCustomerGeneral(warehouse, command, lineNum, true);
    }

    else if(the_command == "volunteer"){
        string & name = command[1];
        string & volunteer_role = command[2];

        if(volunteer_role == "collector"){
            string usage = "usage: volunteer <volunteer_name> collector <volunteer_cooldown>";

            if (!isValid(command, 4, lineNum, usage, true)){
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

            if (!isValid(command, 5, lineNum, usage, true)){
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

            if (!isValid(command, 5, lineNum, usage, true)){
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

            if (!isValid(command, 6, lineNum, usage, true)){
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
            printErrorAtLine(lineNum);
            cerr << "The volunteer role can only be: collector/ limited_collector/ driver/ limited_driver" << endl;
        }
        

    }
    else{
        printErrorAtLine(lineNum);
        cerr << "You can only add volunteer and customer in your configuration file" << endl;
        return false;
    }
    return true;
}

// Convert String To Int
int csti(string &s, string parameter){
    try{
        int x = stoi(s);
        if(digits(x) != s.size()){
            cout << "error in the " << parameter << " you sent" << endl;
            return -1;
        }
        return x;
    }
    catch(invalid_argument const&){
        cout << parameter << " has to be an integer" << endl;
        return -1;
    }
}

// created because of stoi behaviors
size_t digits(int num){
    if (num == 0)
        return 1;
    size_t digits = 0;
    while (num != 0){
        num /= 10;
        digits++;
    }
    return digits;
}

void printErrorAtLine(int lineNum){
    cerr << "The command at line: " << lineNum << ", isn't a valid command" << endl;
}

bool isValid(vector<string> &command, size_t size, int &lineNum, string &usage, bool config){
    if (command.size() != size){
        if(config)
            printErrorAtLine(lineNum);
        cerr << usage << endl;
        return false;
    }
    return true;
}


