#include "../include/Volunteer.h"

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown ,int maxOrders):
CollectorVolunteer(id, name, coolDown), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedCollectorVolunteer * LimitedCollectorVolunteer::clone() const
{

}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{

}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{

}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{

}

int LimitedCollectorVolunteer::getMaxOrders() const
{

}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{

}

string LimitedCollectorVolunteer::toString() const
{

}