#include "Address.h"
#include <iostream>


Address::Address(string Street_Address,
    string City,
    string State,
    int Zip_Code) :
    street_address(Street_Address),
    city(City),
    state(State),
    zip_code(Zip_Code)
{}


void Address::Display() const
{
    cout.fill('0');
    cout << street_address << endl;
    cout << city << ", " << state << " ";
    cout.width(5);
    cout << zip_code << endl;
}
