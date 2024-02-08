#pragma once
#include "main.h"
#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"



// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        ~WareHouse(); //Deconstrucor
        WareHouse(const WareHouse& other); //Copy constructor
        WareHouse& operator=(const WareHouse& other); //Copy Assignment Operator
        WareHouse(WareHouse&& other) noexcept; //Move Constructor
        WareHouse& operator=(WareHouse&& other) noexcept; //Move Assignment Operator
        void deleteWareHouse(WareHouse &wareHouse);
        void clearWareHouse(WareHouse &wareHouse);
        void updateWareHouse(const WareHouse &other);
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        void addCustomer(Customer *customer);
        void addVolunteer(Volunteer *volunteer);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        BaseAction &getAction(int id) const;
        vector<Order*> &getInproccessOrders();
        vector<Order*> &getPendingOrders() ;
        vector<Order*> &getCompleted();
        vector<Volunteer*> &getVolunteers();
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();
        int getNumOrders() const;
        int getNumCustomers() const;
        int getNumVolunteers() const;
        

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> allOrders;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        Volunteer* doesntExist;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
};