#include "../include/Order.h"

Order::Order(int id, int customerId, int distance) : 
id{id}, customerId{customerId}, distance{distance}, 
status{OrderStatus::PENDING}, collectorId{NO_VOLUNTEER}, driverId{NO_VOLUNTEER},finish(true)
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
    string toString = "OrderId: " + id + '\n';
    toString += "OrderStatus: " + OrderStatusHandler::toString(status) + '\n';
    toString += "CustomerId: " + customerId + '\n';
    toString += "Collector: " + collectorId + '\n';
    toString += "Driver: " + driverId + '\n';
    return toString;
}

string OrderStatusHandler::toString(OrderStatus OrderStatus)
{
    switch (OrderStatus) 
    {
        case OrderStatus::PENDING: return "PENDING";
        case OrderStatus::COLLECTING: return "COLLECTING";
        case OrderStatus::DELIVERING: return "DELIVERING";
        case OrderStatus::COMPLETED: return "COMPLETED";
        default: return "Unknown";
    }
}