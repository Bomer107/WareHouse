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
    if(decreaseCoolDown()){
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
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
    activeOrderId = order.getId();
    timeLeft = coolDown;
}

string CollectorVolunteer::toString() const
{
    stringstream ss;
    ss << "VolunteerID: " << getId() << "\n" <<
        "isBusy: " << isBusy() << "\n";
    ss << "TimeLeft: ";
    if(getTimeLeft() > 0)
        ss << getTimeLeft() << "\n";
    else
        ss << "None" << "\n";
    ss << "OrdersLeft: No Limit";
    return ss.str();
}

