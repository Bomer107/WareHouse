#include "../include/BaseAction.h"
class customer ;    
       
       
       
 BaseAction::BaseAction():status(ActionStatus::INPROCESS){}
 
 ActionStatus BaseAction:: getStatus() const
 {
     return status;
 }
 
 void BaseAction::complete()
 {
    ActionStatus tmp (ActionStatus :: COMPLETED);
    BaseAction :: status=tmp;
 }
 void BaseAction:: error(string errorMsg)
 {
    BaseAction: errorMsg = errorMsg;
    ActionStatus tmp (ActionStatus ::ERROR);
    BaseAction :: status=tmp;

 }
 string BaseAction:: getErrorMsg() const
 {
     return errorMsg;
 }
 Order::Order(int id):customerId(id){

 }
 void Order:: act(WareHouse &wareHouse) override 
 {
    customer& customer=wareHouse.getCustomer(customerId);
    int distance=customer.getCustomerDistance();
    int numOrder=wareHouse.getNumOrder();
    int id =customerId;
    Order* order=new Order(numOrder,id,distance);
    WareHouse.addOrder(order);


 }
 
 order::Order *clone() const override
 {

 }
 string order:: toString() const override
 {

 }  
 