#pragma once
#include "tinyxml.h"
#include <iostream>
#include "tinyxml.h"
#include "New_Venue.h"
#include "Address.h"
#include "Seat.h"
#include "Seat_Row.h"
#include "Seat_Section.h"

class Venue_From_Xml
{
public:
	static const int MAX_SEATS_PER_SECTION = 1000;

	static New_Venue* Get_Venue(TiXmlNode* venue_node);
	static Address* Get_Address(TiXmlNode* address_node);


private:
	// Get_Seat_Row() will not use the Section_Array, but will instead pass it to the
	// Get_Seat() method
	static Seat_Row* Get_Seat_Row(TiXmlNode* seat_row_node, Seat_Section** Section_Array, int& seat_count, string& current_sec);

	// Get_Seats() will add sections to the venue and assign seats to each.
	static void Get_Seats(TiXmlNode* seat_row_node, New_Venue& v);

	// Get_Seat must have a method by which to search through an array of sections
	// and assign seats accordingly
	static Seat* Get_Seat(TiXmlNode* seat_node, Seat_Row* Current_Row, Seat_Section** Section_Array, int& seat_count, string& current_sec);
};