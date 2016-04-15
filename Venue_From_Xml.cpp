#include <iostream>
#include <string>
#include "Venue_From_Xml.h"
#include "tinyxml.h"
#include "New_Venue.h"
#include "Address.h"
#include "Seat.h"
#include "Seat_Row.h"
#include "Seat_Section.h"
using namespace std;

Address* Venue_From_Xml::Get_Address(TiXmlNode* venue_node)
{
   string street_address = venue_node->FirstChild()->NextSibling()->FirstChild()->FirstChild()->Value() ; // value of street.
   string city = venue_node->FirstChild()->NextSibling()->FirstChild()->NextSibling()->FirstChild()->Value() ; // ^
   string state = venue_node->FirstChild()->NextSibling()->FirstChild()->NextSibling()->NextSibling()->FirstChild()->Value() ; // ^
   int zip_code = atoi(venue_node->FirstChild()->NextSibling()->FirstChild()->NextSibling()->NextSibling()->NextSibling()->FirstChild()->Value()) ; // ^ , converts the string read in to an int.

   Address* adr = new Address(street_address , city , state , zip_code) ;

   return adr;
}

Seat* Venue_From_Xml::Get_Seat(TiXmlNode* seat_node, Seat_Row* Current_Row, Seat_Section** Section_Array, int& section_count, string& current_sec)
{
	TiXmlNode* number_node = seat_node->FirstChild("number");

	// cout << number_node->Value() << ": ";
	// cout << number_node->FirstChild()->Value() << " ";

	int seat_num = atoi(number_node->FirstChild()->Value());

	TiXmlNode* section_node = seat_node->FirstChild("section");

	/*cout << section_node->Value() << ": ";
	cout << section_node->FirstChild()->Value() << endl;*/

	string new_section_name = section_node->FirstChild()->Value();

	// Adds a new section if one of the same name does not exist
	if (current_sec != new_section_name)
	{
		bool add_new_section = true;
		current_sec = new_section_name;

		for (int i = 0; i < section_count; i++)
		{
			if (Section_Array[i]->Get_Name() == new_section_name)
			{
				add_new_section = false;
				break;
			}
		}

		if (add_new_section)
			Section_Array[section_count++] = new Seat_Section(current_sec);
	}

	// Gets the section which the seat is in
	int seat_section_index = 0;

	for (int i = 0; i < section_count; i++)
	{
		if (Section_Array[i]->Get_Name() == new_section_name)
		{
			seat_section_index = i;
			break;
		}
	}

	// Creates a new seat and then adds that seat to the corresponding seat section
	Seat* s = new Seat(Current_Row, seat_num, Section_Array[seat_section_index]);
	Section_Array[seat_section_index]->Add_Seat(s);

	return s;
}

Seat_Row* Venue_From_Xml::Get_Seat_Row(TiXmlNode* seat_row_node, Seat_Section** Section_Array, int& section_count, string& current_sec)
{
//	cout << seat_row_node->Value() << endl;
	TiXmlNode* name_node = seat_row_node->FirstChild("name");
	assert(name_node != 0);

	Seat_Row* sr = new Seat_Row(name_node->FirstChild()->Value());

//	cout << name_node->Value() << " ";
//	cout << name_node->FirstChild()->Value() << " ";

	TiXmlNode* seat_node = seat_row_node->FirstChild("seat");

	while (seat_node != 0)
	{
		// cout << name_node->Value() << " ";
		// cout << name_node->FirstChild()->Value() << " ";
		// cout << seat_node->Value() << " ";

		sr->Add_Seat(Get_Seat(seat_node, sr, Section_Array, section_count, current_sec));
		seat_node = seat_node->NextSibling();
	}

	return sr;
}

void Venue_From_Xml::Get_Seats(TiXmlNode* seat_row_node, New_Venue& v)
{
	Seat_Section* ss_array[MAX_SEATS_PER_SECTION];

	// # of sections
	int count = 0;
	string current_section = "";

	while (seat_row_node != 0)
	{
		v.Add_Seat_Row(Get_Seat_Row(seat_row_node, ss_array, count, current_section));
		seat_row_node = seat_row_node->NextSibling();
	}

	// Add all new seat sections to the venue object
	for (int i = 0; i < count; i++)
	{
		v.Add_Seat_Section(ss_array[i]);
	}

	// For testing purposes only
	int breakpoint = 0;
}

New_Venue* Venue_From_Xml::Get_Venue(TiXmlNode* venue_node)
{

	TiXmlNode* name_node = venue_node->FirstChild();
	assert(name_node != 0);
//	cout << name_node->Value() << endl;
	cout << endl;

	TiXmlNode* name_text_node = name_node->FirstChild();
	assert(name_text_node != 0);
	//cout << name_text_node->Value() << endl;

	string venue_name = venue_node->FirstChild()->FirstChild()->Value() ;

	TiXmlNode* address_node = name_node->NextSibling();
	assert(address_node != 0);
	//cout << address_node->Value() << endl;

	Address* address = Get_Address(venue_node);

	New_Venue* new_venue = new New_Venue(venue_name , *address);

	TiXmlNode* seat_row_node = address_node->NextSibling();
	assert(seat_row_node != 0);
	Get_Seats(seat_row_node, *new_venue);

	return new_venue;

}
