#include <iostream>
#include "Seat.h"
#include "Seat_Row.h"
#include "Seat_Section.h"

using namespace std;

Seat::Seat(const Seat_Row* const Row, int Seat_Number, const Seat_Section* const Section) :
	row(Row),seat_number(Seat_Number), section(Section)
{}

// Code for selling a seat
//void Seat::Sell()
//{
//	sold = true;
//}

void Seat::Display() const
{
	cout << "Row " << row->Name() << " Seat " << seat_number << " Section " << section->Get_Name() << endl;
}

bool Seat::operator>(const Seat& other) const
{
	if (this->row->Name() == other.row->Name())
	{
		return this->seat_number > other.seat_number;
	}
	return this->row->Name() > other.row->Name();
}


