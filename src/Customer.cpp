#include "../include/Customer.h"


Customer::Customer(int id, const string &name, int locationDistance, int maxOrders):
id{id}, name{name}, locationDistance{locationDistance}, maxOrders{maxOrders}, ordersId{}
{}

const string & Customer::getName() const
{
    return name;
}

int Customer::getId() const
{
    return id;
}

int Customer::getCustomerDistance() const
{
    return locationDistance;
}

int Customer::getMaxOrders() const
{
    return maxOrders;
}

int Customer::getNumOrders() const
{
    return ordersId.size();
}

bool Customer::canMakeOrder() const
{
    return (getNumOrders() < maxOrders);
}

const vector<int> & Customer::getOrdersIds() const
{
    return ordersId;
}

int Customer::addOrder(int orderId)
{
    if(canMakeOrder() && orderId > -1)
    {
        ordersId.push_back(orderId);
        return orderId; 
    }
    return -1;
}


SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders): 
Customer(id, name, locationDistance, maxOrders)
{

}

SoldierCustomer *SoldierCustomer::clone() const
{
    SoldierCustomer * clone {new SoldierCustomer{getId(), getName(), getCustomerDistance(), getMaxOrders()}};
    const vector<int> & orders{getOrdersIds()};
    for (int order: orders)
        clone->addOrder(order);
    return clone;
}



CivilianCustomer::CivilianCustomer(int id, string name, int locationDistance, int maxOrders): 
Customer(id, name, locationDistance, maxOrders)
{}

CivilianCustomer *CivilianCustomer::clone() const
{
    CivilianCustomer * clone {new CivilianCustomer{getId(), getName(), getCustomerDistance(), getMaxOrders()}};
    const vector<int> & orders{getOrdersIds()};
    for (int order: orders)
        clone->addOrder(order);
    return clone;
}
