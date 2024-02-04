#include "../include/Order.h"

Order::Order(int id, int customerId, int distance) : 
id{id}, customerId{customerId}, distance{distance}, 
status{OrderStatus::PENDING}, collectorId{NO_VOLUNTEER}, driverId{NO_VOLUNTEER}, 
finish(false)
{}

Order * Order::clone() const
{
    Order * clone {new Order(getId(), getCustomerId(), getDistance())};
    clone->status = getStatus();
    clone->collectorId = getCollectorId();
    clone->driverId = getDriverId();
    clone->finish = getfinish();
    return clone;
}

void Order::setfinish(bool wateFor)
{
    finish = wateFor;
}

bool Order::getfinish() const
{
    return finish;
}

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

void Order::accepted(int id)
{
    switch (getStatus())
    {
    case OrderStatus::PENDING:
        setStatus(OrderStatus::COLLECTING);
        setCollectorId(id);
        break;
    case OrderStatus::COLLECTING:
        setStatus(OrderStatus::DELIVERING);
        setDriverId(id);
        break;
    case OrderStatus::DELIVERING:
        setStatus(OrderStatus::COMPLETED);
        break;
    default:
        break;
    }        
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