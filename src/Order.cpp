#include "../include/Order.h"

Order::Order(int id, int customerId, int distance) : 
id{id}, customerId{customerId}, distance{distance}, 
status{OrderStatus::PENDING}, collectorId{NO_VOLUNTEER}, driverId{NO_VOLUNTEER}
{}

int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    return customerId;
}

int Order::getDistance() const
{
    return distance;
}

void Order::setStatus(OrderStatus status)
{
    Order::status = status;
}

void Order::setCollectorId(int collectorId)
{
    Order::collectorId = collectorId;
}

void Order::setDriverId(int driverId)
{
    Order::driverId = driverId;
}

int Order::getCollectorId() const
{
    return collectorId;
}

int Order::getDriverId() const
{
    return driverId;
}

OrderStatus Order::getStatus() const
{
    return status;
}


const string Order::toString() const
{
    stringstream ss;
    ss << "OrderId: " << id << "\n" << 
        "OrderStatus: " << getStatusString() << "\n" <<
        "CustomerId: " << customerId << "\n" <<
        "Collector: " << collectorId << "\n" <<
        "Driver: " << driverId << "\n";
    return ss.str();
}

string Order::getStatusString() const
{
    switch (getStatus()) 
    {
        case OrderStatus::PENDING: return "PENDING";
        case OrderStatus::COLLECTING: return "COLLECTING";
        case OrderStatus::DELIVERING: return "DELIVERING";
        case OrderStatus::COMPLETED: return "COMPLETED";
        default: return "Unknown";
    }
}