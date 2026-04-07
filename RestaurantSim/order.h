#pragma once

class order {
private:
    int orderID;
    int numPeople;

public:
    // Constructor
    order(int id, int people);

    // Getters
    int getOrderID() const;
    int getNumPeople() const;

    // You can add more variables (like arrival time, order type) 
    // here later based on Person 3's exact requirements.
};