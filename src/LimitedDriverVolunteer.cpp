#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer
(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedDriverVolunteer * LimitedDriverVolunteer::clone() const
{
    LimitedDriverVolunteer * clone {new LimitedDriverVolunteer(getId(), getName(), getMaxDistance(), getDistancePerStep(), getMaxOrders())};
    clone->ordersLeft = getNumOrdersLeft();
    clone->setDistanceLeft(getDistanceLeft());
    clone->completedOrderId = getCompletedOrderId();
    clone->activeOrderId = getActiveOrderId();
    clone->finishedNow = getFinishedNow();
    return clone;
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
        "isBusy: ";
    if(isBusy()){
        ss << "True" << "\n";
        ss << "OrderId: " << getActiveOrderId();
    }
    else
        ss << "False" << "\n" << "OrderId: None";
    ss<< "\n";
    ss << "Distance left: ";
    if(getDistanceLeft() > 0)
        ss << getDistanceLeft() << "\n";
    else
        ss << "None" << "\n";
    ss << "OrdersLeft: " << getNumOrdersLeft();
    return ss.str();
}

