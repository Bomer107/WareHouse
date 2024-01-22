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
   wareHouse.addAction(this);
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
   if (customer.canMakeOrder()) {
      int distance {customer.getCustomerDistance()};
      int numOrder {wareHouse.getNumOrder()};
      int id {customerId};
      Order* order {new Order(numOrder,id,distance)};
      wareHouse.addOrder(order);
      BaseAction::complete();
   }
   else{
      BaseAction::error("Cannot place this order");
   }
}

AddOrder * AddOrder::clone() const
{
}

string AddOrder::toString() const
{
}

AddCustomer::AddCustomer(string customerName, string customerType, int distance, int maxOrders):
BaseAction(), customerName{customerName}, customerType{}, distance{distance},maxOrders{maxOrders}
{ 
   if (customerType == "soldier") {
      const CustomerType customerType = CustomerType::Soldier;
   } 
   else if (customerType == "civilian"){
      const CustomerType customerType = CustomerType::Civilian; 
   }
   else{

   }
};

void AddCustomer::act(WareHouse &wareHouse){
   wareHouse.addAction(this);
   if(customerType == CustomerType::Soldier){
      Customer *customer{new SoldierCustomer(wareHouse.getNumCustomer(), customerName ,distance, maxOrders)};
      wareHouse.AddCustomer(customer);
   }
   else{
      Customer *customer{new CivilianCustomer(wareHouse.getNumCustomer(), customerName ,distance, maxOrders)};
      wareHouse.AddCustomer(customer);
   }
}

AddCustomer *clone()
{

}

string toString() 
{

}
