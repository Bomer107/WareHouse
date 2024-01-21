#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer
(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders{maxOrders}, ordersLeft{maxOrders}
{}

LimitedDriverVolunteer * LimitedDriverVolunteer::clone() const
{

}

int LimitedDriverVolunteer::getMaxOrders() const
{

}

int LimitedDriverVolunteer::getNumOrdersLeft() const
{

}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{

}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{

}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{

}

string LimitedDriverVolunteer::toString() const
{

}
