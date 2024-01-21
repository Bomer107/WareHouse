#include "../include/WareHouse.h"

WareHouse::WareHouse(const string &configFilePath) :
isOpen{false}, actionsLog{}, volunteers{}, pendingOrders{}, inProcessOrders{}, 
completedOrders{}, customerCounter{}, volunteerCounter{}
{
    ifstream configFile {configFilePath};
    string line{};
    while (getline(configFile, line))
    {
    }
    configFile.close();   
}

void WareHouse::start(){
    open();
}
const vector<BaseAction*> & WareHouse::getActions() const
{

}

void WareHouse::addOrder(Order* order)
{

}

void WareHouse::addAction(BaseAction* action)
{

}

Customer & WareHouse::getCustomer(int customerId) const
{

}

Volunteer & WareHouse::getVolunteer(int volunteerId) const
{

}

Order & WareHouse::getOrder(int orderId) const
{

}

void WareHouse::close()
{

}

void WareHouse::open()
{
    isOpen = true;
}

