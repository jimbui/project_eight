#pragma once

#include "Seat.h"
#include "Seat_Row.h"
#include <string>
#include <cassert>

using namespace std;

class Seat_Section
{
   public:

   static const int MAX_SEATS_PER_SECTION = 1000 ;

   private:

   string section_name ;

   string row_name[1000] ; 
   int first_seat[1000] ;
   int last_seat[1000] ;

   // In order to make the seat array modifiable, I have removed const here and in the Add_Seat(...) method.
   Seat* seat[MAX_SEATS_PER_SECTION] ;

   int seat_count ;
   int row_count  ;

   public:

   Seat_Section(){} ;
   
   // This constructor creates a seat section with only a name
   Seat_Section(const string& Section_Name);

   Seat_Section(const string Section_Name, string Row_Name[], int First_Seat[], int Last_Seat[] , int rows);

   // Add seats from a specific row to a seat section
   void Add_Seats_From_Row(const Seat_Row& seat_row, int First_Seat, int Last_Seat);
   void Add_Seats_From_Row(const Seat_Row& seat_row); // This method checks seat section of seats to be added.

   // Adds one seat to a seat section
   void Add_Seat(Seat* New_Seat);
   

   void Display() const ;
   void Display_Row() const;
   
   // Displays all seats in Seat_Section.  Use for testing purposes only.
   void Display_Seats() const;

   // Sorting methods
   void Sort_Seats();

private:
   void Swap_Seats(Seat*& v1, Seat*& v2); // This method should not be visible outside of the Seat_Section class

public:

   string Get_Name() const {return section_name; } ;

   string Get_Row_Element(int index) { return row_name[index]; };
   int Get_First_Seat_Element(int index) { return first_seat[index]; };
   int Get_Last_Seat_Element(int index) { return last_seat[index]; };
   int Get_Row_Count() const { return row_count; };
};

