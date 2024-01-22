#include "../include/WareHouse.h"
#include "../include/executeLine.h"

WareHouse::WareHouse(const string &configFilePath) :
isOpen{false}, actionsLog{}, volunteers{}, pendingOrders{}, inProcessOrders{}, 
completedOrders{}, customerCounter{}, volunteerCounter{}, allOrders{}, availableVolunteers{}
{
    ifstream configFile {configFilePath};
    string line{};
    vector<string> command{};
    while (getline(configFile, line))
    {
        parseString(line, command);
        if(command.size() > 0)
            configWareHouse(*this, command);
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

void WareHouse::AddCustomer(Customer *customer)
{
    if(customer->getId() == customerCounter){
        customerCounter++;
        customers.push_back(customer);
    }
    else{
        cerr << "";
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

void WareHouse::close()
{

}

void WareHouse::open()
{
    isOpen = true;
    cout << "The WareHouse is open" << endl;
}

int WareHouse::getNumOrder() const
{
    return allOrders.size();
}

int WareHouse::getNumCustomer() const
{
    return customerCounter;
}
