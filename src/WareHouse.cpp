#include "../include/WareHouse.h"
#include "../include/ExecuteLine.h"

WareHouse::WareHouse(const string &configFilePath) :
isOpen{false}, actionsLog{}, volunteers{}, allOrders{}, pendingOrders{}, inProcessOrders{},
completedOrders{}, customers{}, doesntExist{new CollectorVolunteer(-1, "doesn't exist", -1)},
customerCounter{}, volunteerCounter{}
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
    deleteWareHouse(*this);
}

void WareHouse::deleteWareHouse(WareHouse &wareHouse)
{
    for(BaseAction* action : wareHouse.actionsLog)
        delete action;
    for(Volunteer* volunteer : wareHouse.volunteers)
        if(volunteer)
            delete volunteer;
    for(Order* order : wareHouse.allOrders)
        delete order;
    for(Customer* customer : wareHouse.customers)
        delete customer;

    delete wareHouse.doesntExist;
    clearWareHouse(wareHouse);
    
}

void WareHouse::clearWareHouse(WareHouse &wareHouse)
{
    (wareHouse.customers).clear();
    (wareHouse.actionsLog).clear();
    (wareHouse.volunteers).clear();
    (wareHouse.pendingOrders).clear();
    (wareHouse.inProcessOrders).clear();
    (wareHouse.completedOrders).clear();
    (wareHouse.allOrders).clear();
}

//Copy constructor
WareHouse::WareHouse(const WareHouse& other) : 
isOpen{other.isOpen}, actionsLog{}, volunteers{},
allOrders{}, pendingOrders{}, 
inProcessOrders{}, completedOrders{}, 
customers{}, doesntExist{},
customerCounter{other.customerCounter}, volunteerCounter{other.volunteerCounter}
{
    updateWareHouse(other);
}

WareHouse& WareHouse::operator=(const WareHouse& other) //Copy Assignment Operator
{
    if(this != &other)
    {
        deleteWareHouse(*this); // deletes memory from the heap and cleans wareHouse

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
customers(move(other.customers)),doesntExist{move(other.doesntExist)}, 
customerCounter{move(other.customerCounter)}, 
volunteerCounter{move(other.volunteerCounter)}
{} 

WareHouse& WareHouse::operator=(WareHouse&& other) noexcept //Move Assignment Operator
{
    if (this != &other)
    {
        deleteWareHouse(*this);
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
    Volunteer * volunteer {volunteers.at(volunteerId)};
    if(volunteer)
        return (*volunteer);
    else
        return (*doesntExist);
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
    cout << "Warehouse is open!" << endl << endl;
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
        Volunteer & volunteer {other.getVolunteer(i)};
        if(volunteer.getId() != -1)
            volunteers.push_back(volunteer.clone());
        else
            volunteers.push_back(nullptr);
    }

    allOrders.resize(other.getNumOrders());

    for(size_t i{}; i < (other.pendingOrders).size(); ++i){
        Order *order = (other.pendingOrders).at(i);
        Order * clone = (*order).clone();
        pendingOrders.push_back(clone);
        allOrders.at(clone->getId()) = clone;
    }

    for(size_t i{}; i < (other.inProcessOrders).size(); ++i){
        Order *order = (other.inProcessOrders).at(i);
        Order * clone = (*order).clone();
        inProcessOrders.push_back(clone);
        allOrders.at(clone->getId()) = clone;
    }
    
    for(size_t i{}; i < (other.completedOrders).size(); ++i){
        Order *order = (other.completedOrders).at(i);
        Order * clone = (*order).clone();
        completedOrders.push_back(clone);
        allOrders.at(clone->getId()) = clone;
    }

    for(size_t i{}; i < (other.customers).size(); ++i){
        Customer *customer {(other.customers).at(i)};
        customers.push_back((*customer).clone());
    }

    doesntExist = (other.doesntExist)->clone();
}
