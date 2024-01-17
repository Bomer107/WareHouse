#include "../include/BaseAction.h"
       
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


Order::Order(int id):BaseAction(), customerId{id}
{}

void Order::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   Customer& customer {wareHouse.getCustomer(customerId)};
   int distance {customer.getCustomerDistance()};
   int numOrder {wareHouse.getNumOrder()};
   int id {customerId};
   Order* order {new Order(numOrder,id,distance)};
   wareHouse.addOrder(order);
}

Order * Order::clone() const
{
}

string Order::toString() const
{
}  

