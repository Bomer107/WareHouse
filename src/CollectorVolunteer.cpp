#include "../include/Volunteer.h"

CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown): 
Volunteer(id, name), coolDown{coolDown}, timeLeft{NO_ORDER}
{}

CollectorVolunteer *CollectorVolunteer::clone() const
{
    return (new CollectorVolunteer(getId(), getName(), getCoolDown()));
}

void CollectorVolunteer::step()
{

}

int CollectorVolunteer::getCoolDown() const
{

}

int CollectorVolunteer::getTimeLeft() const
{

}

bool CollectorVolunteer::decreaseCoolDown()
{

}

bool CollectorVolunteer::hasOrdersLeft() const
{

}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{

}

void CollectorVolunteer::acceptOrder(const Order &order)
{

}

string CollectorVolunteer::toString() const
{

}