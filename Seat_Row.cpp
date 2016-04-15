#include <iostream>
#include <string>
#include <cassert>
#include "Seat_Row.h"
using namespace std;

//Seat_Row::Seat_Row(const string& Row_Name, int Number_Of_Seats, const string& Section_Name) :
//	row_name(Row_Name),
//	number_of_seats(0)
//{
//	for (int i = 0; i < Number_Of_Seats; i++)
//	{
//		Add_Seat(new Seat(Row_Name, i + 1, Section_Name));
//	}
//}

Seat_Row::Seat_Row(const string& Row_Name) : row_name(Row_Name), number_of_seats(0)
{}

bool Seat_Row::operator>(const Seat_Row& other) 
{
		if (this->row_name == other.Name()) 
		{ 
			return this->number_of_seats > other.Number_of_Seats(); 
		} 

		return this->row_name > other.Name(); 
	
}

void Seat_Row::Add_Seat(/*const*/ Seat* new_seat)
{
	assert(number_of_seats < MAX_SEATS_PER_ROW);
	seats[number_of_seats++] = new_seat;
}

void Seat_Row::Display() const
{
	for (int i = 0; i < number_of_seats; i++)
	{
		seats[i]->Display();
	}
}

//void Seat_Row::Sort_Seats()const
//{
//	for (int i = 0; i < number_of_seats; ++i)
//	{
//		if (*seats[i]->seat_number < *seats[i + 1]->seat_number)
//		{
//
//		}
//	}
//}