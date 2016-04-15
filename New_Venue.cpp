#include <string.h>
#include <iostream>
#include <cassert>
#include "New_Venue.h"
#include "Seat_Row.h"
#include "Seat.h"
#include "Seat_Section.h"
using namespace std;

New_Venue::New_Venue(const string& name_, const Address &address_) : 
	name(name_), address(&address_), number_of_seat_rows(0), number_of_seat_sections(0)
{}

void New_Venue::Add_Seat_Row(const Seat_Row* seat_row)
{
	assert(number_of_seat_rows < MAX_SEAT_ROWS - 1);
	seat_rows[number_of_seat_rows++] = seat_row;
}

void New_Venue::Add_Seat_Section(const Seat_Section* seat_section)
{
	assert(number_of_seat_sections < MAX_SEAT_SECTIONS - 1);
	seat_sec[number_of_seat_sections++] = seat_section;
}


void New_Venue::Display() const
{
	cout << name << endl;
	address->Display();

	for (int i = 0; i < number_of_seat_rows; i++)
		seat_rows[i]->Display();
}


int New_Venue::Capacity() const
{
	int count = 0;
	for (int i = 0; i < number_of_seat_rows; ++i)
	{
		count += seat_rows[i]->Number_of_Seats();
	}
	return count;
}
