#include "../include/Volunteer.h"

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown ,int maxOrders):
CollectorVolunteer(id, name, coolDown), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedCollectorVolunteer * LimitedCollectorVolunteer::clone() const
{
    LimitedCollectorVolunteer * clone {new LimitedCollectorVolunteer(getId(), getName(), getCoolDown(), getMaxOrders())};
    clone->setTimeLeft(getTimeLeft());
    clone->ordersLeft = ordersLeft;
    clone->completedOrderId = getCompletedOrderId();
    clone->activeOrderId = getActiveOrderId();
    clone->finishedNow = getFinishedNow();
    return clone;
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return CollectorVolunteer::canTakeOrder(order) && hasOrdersLeft();
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    --ordersLeft;
}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const
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
    ss << "TimeLeft: ";
    if(getTimeLeft() > 0)
        ss << getTimeLeft() << "\n";
    else
        ss << "None" << "\n";
    ss << "OrdersLeft: " << getNumOrdersLeft();
    return ss.str();
}