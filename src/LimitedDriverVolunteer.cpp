#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer
(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedDriverVolunteer * LimitedDriverVolunteer::clone() const
{
    LimitedDriverVolunteer * clone {};
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
    stringstream ss;
    ss << "VolunteerID: " << getId() << "\n" <<
        "isBusy: " << isBusy() << "\n";
    ss << "Distance left: ";
    if(getDistanceLeft() > 0)
        ss << getDistanceLeft() << "\n";
    else
        ss << "None" << "\n";
    ss << "OrdersLeft: " << getNumOrdersLeft();
    return ss.str();
}

