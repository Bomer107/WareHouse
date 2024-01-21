#include "../include/Volunteer.h"

DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep):
Volunteer(id, name), maxDistance{maxDistance}, distancePerStep{distancePerStep}, distanceLeft{NO_ORDER}
{}

DriverVolunteer * DriverVolunteer::clone() const
{

}

int DriverVolunteer::getDistanceLeft() const
{

}

int DriverVolunteer::getMaxDistance() const
{

}

int DriverVolunteer::getDistancePerStep() const
{

}

bool DriverVolunteer::decreaseDistanceLeft()
{

}

bool DriverVolunteer::hasOrdersLeft() const
{

}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{

}

void DriverVolunteer::acceptOrder(const Order &order)
{

}

void DriverVolunteer::step()
{

}

string DriverVolunteer::toString() const
{

}