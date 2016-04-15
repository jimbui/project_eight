#pragma once
#include "Seat.h"

class Seat_Row
{
public:
	static const int MAX_SEATS_PER_ROW = 1000;

private:
	string row_name;
	Seat* seats[MAX_SEATS_PER_ROW];
	int  number_of_seats;

public:
	/*Seat_Row(const string& Row_Name, int Number_Of_Seats, const string& Seat_Section);*/
	Seat_Row(const string& Row_Name);
	string Name() const { return row_name; };
	void Add_Seat(/*const*/ Seat* new_seat);
	void Display() const;
	//void Sort_Seats() const;
	//Comparison();

	int Number_of_Seats() const { return number_of_seats; }

	bool operator>(const Seat_Row& other) ;

	/*const*/ Seat* Get_Seat(int idx) const { return seats[idx]; };
};

//ostream& operator<<(ostream& os, const Seat_Row& seat);

