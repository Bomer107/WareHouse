#include "../include/Action.h"
#include <iostream>   


/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------BaseAction---------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

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

string BaseAction::getStatusString() const
{
   switch (getStatus()) 
   {
      case ActionStatus::COMPLETED: return "COMPLETED";
      case ActionStatus::ERROR: return "COLLECTING";
      default: return "Unknown";
   }
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------SimulateStep-------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
    
SimulateStep::SimulateStep(int numOfSteps) :
BaseAction(), numOfSteps{numOfSteps}
{}

void SimulateStep::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   vector<Order*> &pending = wareHouse.getPendingOrders();
   vector<Order*> &inProccess = wareHouse.getInproccessOrders();
   vector<Order*> &comleted = wareHouse.getCompleted();
   vector<Volunteer*>volunteers = wareHouse.getVolunteers();
   for(int i{}; i < numOfSteps; ++i) {

      //assigning volunteers to orders
      for(Order *order : pending){
         for(int j{}; j < volunteers.size(); ++j){
            Volunteer *volunteer = volunteers[j];
            if(volunteer->canTakeOrder(*order)){
               volunteer->acceptOrder(*order);
            }
         }
      }
   }
   for(Volunteer *volunteer:volunteers){
      volunteer->step();
      if(!volunteer->isBusy()){

      }
      


   }
}

SimulateStep * SimulateStep::clone() const
{

}


std::string SimulateStep::toString() const
{
   stringstream ss;
   ss << "step " << numOfSteps << " " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------AddOrder-----------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

AddOrder::AddOrder(int id) : BaseAction::BaseAction(), customerId{id}
{}

void AddOrder::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   if(customerId <= wareHouse.getNumCustomers()){
      Customer& customer {wareHouse.getCustomer(customerId)};
      if (customer.canMakeOrder()) {
         int distance {customer.getCustomerDistance()};
         int numOrder {wareHouse.getNumOrders()};
         int id {customerId};
         Order* order {new Order(numOrder,id,distance)};
         wareHouse.addOrder(order);
         complete();
      }
      else{
         error("Cannot place this order, the customer can't make any more orders");
         cout << getErrorMsg() << endl;
      }
   }
   else{
      error("Cannot place this order, the customer doesn't exist");
      cout << getErrorMsg() << endl;
   }
}

AddOrder * AddOrder::clone() const
{
   return (new AddOrder(customerId));
}

string AddOrder::toString() const
{
   stringstream ss;
   ss << "order " << customerId << " " <<  getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------AddCustomer--------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

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
      error("The customer type you entered doesn't exist");
      cout << getErrorMsg() << endl;
   }
};

void AddCustomer::act(WareHouse &wareHouse){
   if(getErrorMsg() == ""){
      wareHouse.addAction(this);
      if(customerType == CustomerType::Soldier){
         Customer *customer{new SoldierCustomer(wareHouse.getNumCustomers(), customerName ,distance, maxOrders)};
         wareHouse.addCustomer(customer);
         complete();
      }
      else {
         Customer *customer{new CivilianCustomer(wareHouse.getNumCustomers(), customerName ,distance, maxOrders)};
         wareHouse.addCustomer(customer);
         complete();
      }
   }
}


AddCustomer *AddCustomer:: clone() const{
   string customerType = this->getcustomrType();
   return new AddCustomer (customerName,customerType ,distance,maxOrders);

}

string AddCustomer:: toString() const 
{
   stringstream ss;
   ss << "customer " << customerName << " " << getcustomrType() << " " << distance << " " << maxOrders;
   return ss.str();
}

string AddCustomer::getcustomrType() const
{
   switch (customerType) 
   {
      case CustomerType::Soldier: return "Soldier";
      case CustomerType::Civilian: return "Civilian";
      default: return "Unknown";
   }
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------PrintOrderStatus---------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

PrintOrderStatus:: PrintOrderStatus(int id):orderId{id}
{}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   if(orderId < wareHouse.getNumOrders() && orderId > -1){
      Order &order = wareHouse.getOrder(orderId);
      cout << order.toString();
      complete();
   }
   else
   {
      error("Order doesn't exist");
      cout << getErrorMsg() << endl;
   }
}
         
PrintOrderStatus * PrintOrderStatus::clone() const
{
   return new PrintOrderStatus (orderId);
}

std::string PrintOrderStatus::toString() const 
{ 
   stringstream ss;
   ss << "orderStatus " << orderId << " " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------PrintCustomerStatus------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

PrintCustomerStatus::PrintCustomerStatus(int customerId): customerId{customerId}
{}

void PrintCustomerStatus::act(WareHouse &wareHouse) 
{
   wareHouse.addAction(this);
   if(customerId < wareHouse.getNumCustomers() && customerId > -1){
      Customer &customer = wareHouse.getCustomer(customerId);
      cout << "CustomerID: " << customer.getId() << endl;
      vector<int> customerOrders {customer.getOrdersId()};
      for(int orderID : customerOrders){
         cout << "OrderID: " << orderID << endl;
         cout << "OrderStatus: " << (wareHouse.getOrder(orderID)).getStatusString() << endl;
      }
      cout << "numOrdersLeft: " << customer.getMaxOrders() - customerOrders.size() << endl;
      complete();
   }
   else
   {
      error("Customer doesn't exist");
      cout << getErrorMsg() << endl;
   }
}

PrintCustomerStatus * PrintCustomerStatus::clone() const
{

}

string PrintCustomerStatus::toString() const
{
   stringstream ss;
   ss << "customerStatus " << customerId << " " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------PrintVolunteerStatus-----------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

PrintVolunteerStatus::PrintVolunteerStatus(int id): VolunteerId{id}
{}

void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   if(VolunteerId < wareHouse.getNumVolunteers() && VolunteerId > -1){
      Volunteer &volunteer = wareHouse.getVolunteer(VolunteerId);
      cout << "VolunteerID: " << volunteer.getId() << endl;
      cout << boolalpha;
      cout << "isBusy: " << volunteer.isBusy() << endl;
      if (CollectorVolunteer* collector = dynamic_cast<CollectorVolunteer*>(&volunteer)){
         cout << "TimeLeft: ";
         if(collector->getTimeLeft() > 0)
            cout << collector->getTimeLeft() << endl;
         else
            cout << "None" << endl;
         cout << "OrdersLeft: ";
         if (LimitedCollectorVolunteer* limitedCollector = dynamic_cast<LimitedCollectorVolunteer*>(collector)){
            cout << limitedCollector->getNumOrdersLeft() << endl;
         }
         else
            cout << "No Limit" << endl;
         
      }
      else if (DriverVolunteer* driver = dynamic_cast<DriverVolunteer*>(&volunteer)){
         cout << "DistanceLeft: ";
         if(driver->getDistanceLeft() > 0)
            cout << driver->getDistanceLeft() << endl;
         else
            cout << "None" << endl;

         cout << "OrdersLeft: ";
         if (LimitedDriverVolunteer* limitedDriver = dynamic_cast<LimitedDriverVolunteer*>(driver))
            cout << limitedDriver->getNumOrdersLeft() << endl;
         
         else
            cout << "No Limit" << endl;
      }
      complete();
   }
   
   else
   {
      error("Volunteer doesn't exist");
      cout << getErrorMsg() << endl;
   }
}

PrintVolunteerStatus * PrintVolunteerStatus::clone() const
{

}

string PrintVolunteerStatus::toString() const
{
   stringstream ss;
   ss << "volunteerStatus " << VolunteerId << " " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------PrintActionsLog----------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog::act(WareHouse &wareHouse)
{
   vector<BaseAction *> actions = wareHouse.getActions();
   for(BaseAction * action: actions)
      cout << action->toString();

   wareHouse.addAction(this);
   complete();
}

PrintActionsLog * PrintActionsLog::clone() const
{

}

string PrintActionsLog::toString() const
{
   stringstream ss;
   ss << "log " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------Close--------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

        
Close::Close(){}
        
void Close::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   for(int i{}; i < wareHouse.getNumOrders(); ++i)
      cout << (wareHouse.getOrder(i)).toString();
   complete();
   wareHouse.close();
}
        
Close * Close::clone() const
{

}
        
string Close::toString() const
{
   stringstream ss;
   ss << "close " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------BackupWareHouse----------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

        
BackupWareHouse::BackupWareHouse(){}
        
void BackupWareHouse::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   if (backup == nullptr)
      backup = new WareHouse{wareHouse};
   else
      (*backup) = wareHouse;
   complete();
}
        
BackupWareHouse * BackupWareHouse::clone() const
{
   
}
        
string BackupWareHouse::toString() const
{
   stringstream ss;
   ss << "backup " << getStatusString();
   return ss.str();
}

/*
-----------------------------------------------------------------------------------------------------------------------
----------------------------------RestoreWareHouse---------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/

        
RestoreWareHouse::RestoreWareHouse(){}
        
void RestoreWareHouse::act(WareHouse &wareHouse)
{
   wareHouse.addAction(this);
   if(backup != nullptr){
      wareHouse = move(backup);
      complete();
   }
   else{
      error("No backup available");
      cout << getErrorMsg() << endl;
   }
}
        
RestoreWareHouse * RestoreWareHouse::clone() const
{

}
        
string RestoreWareHouse::toString() const
{
   stringstream ss;
   ss << "restore " << getStatusString();
   return ss.str();
}
