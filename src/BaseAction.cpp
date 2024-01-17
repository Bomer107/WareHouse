#include "../include/BaseAction.h"
       
       
       
       
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
    
 