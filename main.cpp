#include <iostream>
#include <cassert>
#include <string>
#include "Address.h"
#include "New_Venue.h"
#include "Seat.h"
#include "Seat_Row.h"
#include "Seat_Section.h"
#include "tinyxml.h"
#include "Venue_From_Xml.h"
#include "Menu.h"
#include "Command_Processor.h"

using namespace std ;



int main()
{
   std::cout << "This is Project Booth 1." << " \n\n" ;
   string filename = "Venues.xml" ; // test file.

   // loading file and creating first node venue_node.

   TiXmlDocument doc(filename) ;
   bool loadOkay = doc.LoadFile() ; 

   if (!loadOkay)
   {
      std::cout << "Could not load file " << filename << "." << " \n" ;
      cout << "Error = \"" << doc.ErrorDesc() << "\".  Exiting." << " \n" ;
      cin.get() ; exit(1) ;
   }

   //std::cout << "file " << filename << " read in." << " \n\n" ;
   
    TiXmlNode* venue_file_node = doc.FirstChild("venue_file");
    assert(venue_file_node != 0);
    //cout << venue_file_node->Value() << endl;

    TiXmlNode* venue_node = venue_file_node->FirstChild();
    assert(venue_node != 0);

	// Initialize an array of venues
	New_Venue* venue[1000];
	int num_venues = 0;

	// Iterates through all venue pointers
	while (venue_node != 0)
	{
		venue[num_venues++] = Venue_From_Xml::Get_Venue(venue_node);
		venue_node = venue_node->NextSibling();
	}
	
	//// Debugging only
	//for (int i = 0; i < num_venues; i++)
	//{
	//	venue[i]->Display();
	//	cout << endl;
	//}

	Command_Processor::Process_Commands(venue, &num_venues);

    cout << "\nNormal Termination\n";
    cin.get();
	cin.get();
}