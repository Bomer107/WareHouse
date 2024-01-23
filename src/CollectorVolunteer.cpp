#include "../include/Volunteer.h"

CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown): 
Volunteer(id, name), coolDown{coolDown}, timeLeft{NO_ORDER}
{}

CollectorVolunteer * CollectorVolunteer::clone() const
{
    return (new CollectorVolunteer(getId(), getName(), getCoolDown()));
}

void CollectorVolunteer::step()
{

}

int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown()
{
    if (timeLeft > 1){
        --timeLeft;
        return false;
    }
    else{
        timeLeft = NO_ORDER;
        return true; 
    }
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (timeLeft == NO_ORDER) && (order.getCollectorId() == NO_VOLUNTEER) 
            && order.getStatus() == OrderStatus::PENDING;
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    completedOrderId = activeOrderId;
    activeOrderId = order.getId();
    timeLeft = coolDown;   
}

string CollectorVolunteer::toString() const
{
    return ("Collector Volunteer " + getName() + ", id: " + std::to_string(getId()));
}