#include "../include/WareHouse.h"
#include "../include/ExecuteLine.h"

WareHouse::WareHouse(const string &configFilePath) :
isOpen{false}, actionsLog{}, volunteers{}, allOrders{}, pendingOrders{}, inProcessOrders{},
completedOrders{}, customers{}, customerCounter{}, volunteerCounter{}
{
    ifstream configFile {configFilePath};
    string line{};
    vector<string> command{};
    int lineNum = 1;
    while (getline(configFile, line))
    {
        command.clear();
        parseString(line, command);
        if(command.size() > 0)
            configWareHouse(*this, command, lineNum);
        ++lineNum;
    }
    configFile.close();   
}

WareHouse::~WareHouse() //Deconstructor
{
    clearWareHouse();
}

void WareHouse::clearWareHouse()
{
    for(BaseAction* action : actionsLog)
        delete action;
    for(Volunteer* volunteer : volunteers)
        delete volunteer;
    for(Order* order : allOrders)
        delete order;
    for(Customer* customer : customers)
        delete customer;

    //cleans the vectors
    customers.clear();
    actionsLog.clear();
    volunteers.clear();
    pendingOrders.clear();
    inProcessOrders.clear();
    completedOrders.clear();
    allOrders.clear();
}

//Copy constructor
WareHouse::WareHouse(const WareHouse& other) : 
isOpen{}, actionsLog{}, volunteers{},
allOrders{}, pendingOrders{}, 
inProcessOrders{}, completedOrders{}, 
customers(), customerCounter{}, 
volunteerCounter{}
{
    updateWareHouse(other);
}

WareHouse& WareHouse::operator=(const WareHouse& other) //Copy Assignment Operator
{
    if(this != &other)
    {
        clearWareHouse(); // deletes memory from the heap

        isOpen = other.isOpen;
        customerCounter = other.customerCounter; 
        volunteerCounter = other.volunteerCounter; 
        updateWareHouse(other);

        
    }
    return (*this);
} 

WareHouse::WareHouse(WareHouse&& other) noexcept :  //Move Constructor
isOpen{other.isOpen}, actionsLog{move(other.actionsLog)}, volunteers{move(other.volunteers)},
allOrders{move(other.allOrders)}, pendingOrders{move(other.pendingOrders)}, 
inProcessOrders{move(other.inProcessOrders)}, completedOrders{move(other.completedOrders)}, 
customers(move(other.customers)), customerCounter{move(other.customerCounter)}, 
volunteerCounter{move(other.volunteerCounter)}
{} 

WareHouse& WareHouse::operator=(WareHouse&& other) noexcept //Move Assignment Operator
{
    if (this != &other)
    {
        clearWareHouse();
        isOpen = other.isOpen;
        actionsLog = move(other.actionsLog);
        volunteers = move(other.volunteers);
        pendingOrders = move(other.pendingOrders);
        inProcessOrders = move(other.inProcessOrders);
        completedOrders = move(other.completedOrders); 
        customerCounter = move(other.customerCounter); 
        volunteerCounter = move(other.volunteerCounter); 
        allOrders = move(other.allOrders);
    }
    return (*this);
}

void WareHouse::start(){
    open();
    string line{};
    vector<string> command{};
    while (isOpen)
    {
        command.clear();
        getline(cin, line);
        parseString(line, command);
        if(command.size() > 0)
            executeCommand(command, *this);
    }
    
}

const vector<BaseAction*> & WareHouse::getActions() const
{
    return actionsLog;
}

void WareHouse::addOrder(Order* order)
{
    if(order->getStatus() == OrderStatus::PENDING){
        pendingOrders.push_back(order);
        allOrders.push_back(order);
    }
    else
        cerr << "you can only add new orders";
}

void WareHouse::addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}

void WareHouse::addCustomer(Customer *customer)
{
    if(customer->getId() == customerCounter){
        customerCounter++;
        customers.push_back(customer);
    }
    else{
        cerr << "this customer wasn't created by this WareHouse";
    }
}

void WareHouse::addVolunteer(Volunteer *volunteer)
{
    if(volunteer->getId() == volunteerCounter){
        volunteerCounter++;
        volunteers.push_back(volunteer);
    }
    else{
        cerr << "this volunteer wasn't created by this WareHouse";
    }
}

Customer & WareHouse::getCustomer(int customerId) const
{
    return (*(customers.at(customerId)));
}

Volunteer & WareHouse::getVolunteer(int volunteerId) const
{
    return (*(volunteers.at(volunteerId)));
}

Order & WareHouse::getOrder(int orderId) const
{
    return (*(allOrders.at(orderId)));
}

BaseAction & WareHouse::getAction(int id) const
{
    return *(actionsLog[id]);
}

int WareHouse::getNumVolunteers() const
{
    return volunteerCounter;
}

void WareHouse::close()
{
    isOpen = false;
}

void WareHouse::open()
{
    isOpen = true;
    cout << "Warehouse is open!" << endl;
}

int WareHouse::getNumOrders() const
{
    return allOrders.size();
}

int WareHouse::getNumCustomers() const
{
    return customerCounter;
}

vector<Order*> & WareHouse::getInproccessOrders()
{
    return inProcessOrders;
}
vector<Order*> & WareHouse::getPendingOrders()
{
    return pendingOrders;
}
vector<Order*> & WareHouse::getCompleted()
{
    return completedOrders;
}
vector<Volunteer*> & WareHouse::getVolunteers()
{
    return volunteers;
}

void WareHouse::updateWareHouse(const WareHouse &other){
    for(size_t i{}; i < (other.actionsLog).size(); ++i){
        actionsLog.push_back((other.getAction(i)).clone());
    }

    for(int i{}; i < other.getNumVolunteers(); ++i){
        volunteers.push_back((other.getVolunteer(i)).clone());
    }

    for(int i{}; i < other.getNumOrders(); ++i){
        Order * clone = (other.getOrder(i)).clone();
        allOrders.push_back(clone);
    }

    for(size_t i{}; i < (other.pendingOrders).size(); ++i){
        Order *order = (other.pendingOrders)[i];
        Order * clone = (*order).clone();
        pendingOrders.push_back(clone);
    }

    for(size_t i{}; i < (other.inProcessOrders).size(); ++i){
        Order *order = (other.inProcessOrders)[i];
        Order * clone = (*order).clone();
        inProcessOrders.push_back(clone);
    }
    
    for(size_t i{}; i < (other.completedOrders).size(); ++i){
        Order *order = (other.completedOrders)[i];
        Order * clone = (*order).clone();
        completedOrders.push_back(clone);
    }
}
