#include "../include/Volunteer.h"

Volunteer::Volunteer(int id, const string &name): 
completedOrderId{NO_ORDER}, activeOrderId{NO_ORDER}, finishedNow{false}, id{id}, name{name}
{}

int Volunteer::getId() const
{
    return id;
}

const string & Volunteer::getName() const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    return (activeOrderId != NO_ORDER);
}

const bool Volunteer::getFinishedNow() const{
    return finishedNow;
}