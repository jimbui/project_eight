#pragma once
#include <string>
#include "Address.h"
#include "Seat.h"
#include "Seat_Row.h"
#include "Seat_Section.h"

class New_Venue
{
public:
	static const int MAX_SEAT_ROWS = 1000;
	static const int MAX_SEAT_SECTIONS = 1000;

private:
	string name;
	const Address* address;
	const Seat_Row* seat_rows[MAX_SEAT_ROWS];
	const Seat_Section* seat_sec[MAX_SEAT_SECTIONS];
	int number_of_seat_rows;
	int number_of_seat_sections;

public:
	New_Venue(const string& name_, const Address &address_);

	void Add_Seat_Row(const Seat_Row* seat_row);
	void Add_Seat_Section(const Seat_Section* seat_section);

	int Capacity() const;     // Number of seats

	void Display() const;

	int Number_of_Seat_Rows() const
	{
		return number_of_seat_rows;
	};

	const Seat_Row* Get_Seat_Row(int index) const
	{
		return seat_rows[index];
	}
};



