#include "Seat_Section.h"
#include <iostream>
#include <string>

using namespace std ;

// New Constructor --> This constructor initializes seat_count to 0.
Seat_Section::Seat_Section(const string& Section_Name) : 
	section_name(Section_Name), seat_count(0)
{
}

// We may not need this constructor...
Seat_Section::Seat_Section(const string Section_Name, string Row_Name[], int First_Seat[], int Last_Seat[] , int rows) 
{
   section_name = Section_Name ;
   int i = 0 ;
   row_count=0;
   int value;
   string name;
   while (i < rows)
   {
      name = Row_Name[i] ;
      row_name[i] = name ;
      value = First_Seat[i] ;
      first_seat[i] = value ;
      value = Last_Seat[i] ;
      last_seat[i] = value ;
      i++ ;
   }

   row_count = rows ;
} ;

void Seat_Section::Display() const
{
   cout << "Section " << section_name << " \n" ;
   int i = 0 ;
   cout << " \n" ;
   while (i < row_count)
   {
      cout << "Row " << row_name[i] << "       " << "Seats " << first_seat[i] << " - " << last_seat[i] << " \n" ;
      i++ ;
   }
}

void Seat_Section::Display_Row() const // modified version of Display().
{
   int i = 0;

   while (i < row_count)
   {
      cout << "Row " << row_name[i] << "       " << "Seats " << first_seat[i] << " - " << last_seat[i] << " \n";
      i++;
   }
   cout << " \n" ;
}

void Seat_Section::Display_Seats() const
{
	for (int i = 0; i < seat_count; i++)
	{
		seat[i]->Display();
		cout << endl;
	}
}

// Iterates through each seat on the seat row and assigns the seat pointers to 
// the seat section's seat pointer array.  Note that 0 corresponds to seat 1, 1 --> 2, etc.
void Seat_Section::Add_Seats_From_Row(const Seat_Row& seat_row, int First_Seat, int Last_Seat)
{
	for (int i = First_Seat; i <= Last_Seat; i++)
	{
		seat[seat_count] = seat_row.Get_Seat(i);

		seat_count++;
	}
}

// Iterates through each seat on the seat row and assigns the seat pointers to 
// the seat section's seat pointer array.  In order to figure out which seats from the row to add,
// the method checks the section_name of each seat. An implementation suggestion may be found in
// main_test.txt.
void Seat_Section::Add_Seats_From_Row(const Seat_Row& seat_row)
{
	for (int i = 0; i < seat_row.Number_of_Seats(); i++)
	{
		Seat* current_seat = seat_row.Get_Seat(i);

		if (current_seat->SEAT_SECTION()->Get_Name() == section_name)
		{
			seat[seat_count] = current_seat;
			seat_count++;
		}
	}
}

// Adds only 1 seat to the seat row
void Seat_Section::Add_Seat(Seat* New_Seat)
{
	// #include <cassert>		--> Added to Seat_Section.h
	assert(seat_count < MAX_SEATS_PER_SECTION);
	seat[seat_count++] = New_Seat;
}

// Sort methods for seat section

// Swap two seats
void Seat_Section::Swap_Seats(Seat*& s1, Seat*& s2)
{
	Seat* temp = s1;
	s1 = s2;
	s2 = temp;
}

// Sorts the current array of seat objects which has a length of seat_count 
void Seat_Section::Sort_Seats()
{
	bool swap_done = false;
	do
	{
		swap_done = false;

		for (int i = 0; i < seat_count - 1; ++i)
		{
			// if (*seat[i] < *seat[i + 1]) --> The '<' operator is not implemented in seat class, so the coding has been written manually.

			// Used 'greater than' comparison to produce seats in ascending order
			bool greater_than = false;

			// Check seat row first
			if (seat[i]->SEAT_ROW()->Name() > seat[i + 1]->SEAT_ROW()->Name())
				greater_than = true;
			else if (seat[i]->SEAT_ROW()->Name() == seat[i + 1]->SEAT_ROW()->Name()) // Seats are in the same row
			{
				if (seat[i]->SEAT_NUM() > seat[i + 1]->SEAT_NUM())
					greater_than = true;

				// The row name and number should *NEVER* be equal!
			}
			else
				greater_than = false;

			if (greater_than)
			{
				Swap_Seats(seat[i], seat[i + 1]);
				swap_done = true;
			}
		}
	} while (swap_done);
}
