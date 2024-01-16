#include "../include/Customer.h"
#include <string>


Customer::Customer(int id, const string &name, int locationDistance, int maxOrders):id(id),name(name) ,locationDistance(locationDistance)
,maxOrders(maxOrders), ordersId{}{ 
}
const string& Customer:: getName() const
{
    return name;
}
int Customer:: getId() const
{
    return id;
}
int Customer::  getCustomerDistance() const
{
    return locationDistance;
}
int Customer:: getMaxOrders() const
{
    return maxOrders;
} 
int Customer:: getNumOrders() const
{
    return ordersId.size;
} 
bool canMakeOrder() const
{
    return(getNumOrders()<maxOrders);
} 
vector<int> Customer:: &getOrders() const
{
    return maxOrders;
}
int Customer:: addOrder(int orderId){
    ordersId.push_back(orderId)
    return 0;
}
Customer::virtual Customer *clone() const = 0; // Return a copy of the custome

Customer::SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders);
Customer::SoldierCustomer::SoldierCustomer *clone() const override;
CivilianCustomer(int id, string name, int locationDistance, int maxOrders);

CivilianCustomer *clone() const override;
