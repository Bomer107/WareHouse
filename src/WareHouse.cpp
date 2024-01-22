#include "../include/WareHouse.h"
#include "../include/ExecuteLine.h"

WareHouse::WareHouse(const string &configFilePath) :
isOpen{false}, actionsLog{}, volunteers{}, pendingOrders{}, inProcessOrders{}, 
completedOrders{}, customerCounter{}, volunteerCounter{}, allOrders{}, availableVolunteers{}
{
    ifstream configFile {configFilePath};
    string line{};
    vector<string> command{};
    int lineNum = 1;
    while (getline(configFile, line))
    {
        parseString(line, command);
        if(command.size() > 0)
            configWareHouse(*this, command, lineNum);
        ++lineNum;
    }
    configFile.close();   
}

void WareHouse::start(){
    open();
    while (isOpen)
    {
        /* code */
    }
    
}

const vector<BaseAction*> & WareHouse::getActions() const
{
    return actionsLog;
}

void WareHouse::addOrder(Order* order)
{
    if(order->getStatus() == OrderStatus::PENDING){
        pendingOrders.push_back(order);
        allOrders.push_back(order);
    }
    else
        cerr << "you can only add new orders";
}

void WareHouse::addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}

void WareHouse::addCustomer(Customer *customer)
{
    if(customer->getId() == customerCounter){
        customerCounter++;
        customers.push_back(customer);
    }
    else{
        cerr << "this customer wasn't created by this WareHouse";
    }
}

void WareHouse::addVolunteer(Volunteer *volunteer)
{
    if(volunteer->getId() == volunteerCounter){
        volunteerCounter++;
        volunteers.push_back(volunteer);
    }
    else{
        cerr << "this volunteer wasn't created by this WareHouse";
    }
}

Customer & WareHouse::getCustomer(int customerId) const
{
    return (*(customers.at(customerId)));
}

Volunteer & WareHouse::getVolunteer(int volunteerId) const
{
    return (*(volunteers.at(volunteerId)));
}

Order & WareHouse::getOrder(int orderId) const
{
    return (*(allOrders.at(orderId)));
}

int WareHouse::getNumVolunteers() const
{
    return volunteerCounter;
}

void WareHouse::close()
{

}

void WareHouse::open()
{
    isOpen = true;
    cout << "The WareHouse is open" << endl;
}

int WareHouse::getNumOrders() const
{
    return allOrders.size();
}

int WareHouse::getNumCustomers() const
{
    return customerCounter;
}
