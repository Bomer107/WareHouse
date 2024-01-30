#pragma once
#include "main.h"

using namespace std;

class Volunteer;

enum class OrderStatus {
    PENDING,
    COLLECTING,
    DELIVERING,
    COMPLETED
};

#define NO_VOLUNTEER -1

class Order {

    public:
        Order(int id, int customerId, int distance);
        Order* clone ();
        int getId() const;
        int getCustomerId() const;
        int getDistance() const;
        void setStatus(OrderStatus status);
        void accepted(int id);
        void setCollectorId(int collectorId);
        void setDriverId(int driverId);
        void setfinish(bool wateFor);
        bool getfinish();
        int getCollectorId() const;
        int getDriverId() const;
        OrderStatus getStatus() const;
        string getStatusString() const;
        const string toString() const;

    private:
        const int id;
        const int customerId;
        const int distance;
        OrderStatus status;
        int collectorId; //Initialized to NO_VOLUNTEER if no collector has been assigned yet
        int driverId; //Initialized to NO_VOLUNTEER if no driver has been assigned yet
        bool finish;
};