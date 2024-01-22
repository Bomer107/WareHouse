#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer
(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedDriverVolunteer * LimitedDriverVolunteer::clone() const
{
    return (new LimitedDriverVolunteer(getId(), getName(), getMaxDistance(), getDistancePerStep(), getMaxOrders()));
}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return DriverVolunteer::canTakeOrder(order) && hasOrdersLeft();
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    --ordersLeft;
}

string LimitedDriverVolunteer::toString() const
{
    return ("Limited Driver Volunteer " + getName() + ", id: " + std::to_string(getId()));
}

