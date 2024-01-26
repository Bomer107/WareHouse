#include "../include/Volunteer.h"

DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep):
Volunteer(id, name), maxDistance{maxDistance}, distancePerStep{distancePerStep}, distanceLeft{NO_ORDER}
{}

DriverVolunteer * DriverVolunteer::clone() const
{
    return (new DriverVolunteer(getId(), getName(), getMaxDistance(), getDistancePerStep()));
}

int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft()
{
    if(distanceLeft > distancePerStep){
        distanceLeft -= distancePerStep;
        return false;
    }
    else{
        distanceLeft = NO_ORDER;
        return true;
    }
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return (distanceLeft == NO_ORDER) && (order.getDriverId() == NO_VOLUNTEER) 
            && (maxDistance >= order.getDistance()) && (order.getStatus() == OrderStatus::COLLECTING);
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    completedOrderId = activeOrderId;
    activeOrderId = order.getId();
    distanceLeft = order.getDistance();
}

void DriverVolunteer::step()
{

}

string DriverVolunteer::toString() const
{
    stringstream ss;
    ss << "VolunteerID: " << getId() << "\n" <<
        "isBusy: " << isBusy() << "\n";
    ss << "Distance left: ";
    if(getDistanceLeft() > 0)
        ss << getDistanceLeft() << "\n";
    else
        ss << "None" << "\n";
    ss << "OrdersLeft: No Limit";
    return ss.str();
}