#include "../include/Volunteer.h"

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown ,int maxOrders):
CollectorVolunteer(id, name, coolDown), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedCollectorVolunteer * LimitedCollectorVolunteer::clone() const
{
    return (new LimitedCollectorVolunteer(getId(), getName(), getCoolDown(), getMaxOrders()));
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
    return ("Limited Collector Volunteer " + getName() + ", id: " + std::to_string(getId()));
}