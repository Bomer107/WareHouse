#include "../include/Action.h"
       
BaseAction::BaseAction(): 
errorMsg{}, status{}
{}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::complete()
{
   status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg)
{
   BaseAction::errorMsg = errorMsg;
   status = ActionStatus::ERROR;
}

string BaseAction:: getErrorMsg() const
{
    return errorMsg;
}
    
SimulateStep::SimulateStep(int numOfSteps) :
BaseAction(), numOfSteps{numOfSteps}
{}

void SimulateStep::act(WareHouse &wareHouse)
{

}

std::string SimulateStep::toString() const
{

}

SimulateStep * SimulateStep::clone() const
{

}


AddOrder::AddOrder(int id) : BaseAction::BaseAction(), customerId{id}
{}

void AddOrder::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   Customer& customer {wareHouse.getCustomer(customerId)};
   int distance {customer.getCustomerDistance()};
   int numOrder {wareHouse.getNumOrder()};
   int id {customerId};
   Order* order {new Order(numOrder,id,distance)};
   wareHouse.addOrder(order);
}

AddOrder * AddOrder::clone() const
{
}

string AddOrder::toString() const
{
}  

