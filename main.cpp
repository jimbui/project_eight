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

using namespace std ;



int main()
{
   std::cout << "testing the XML stuff." << " \n\n" ;
   string filename = "Venue.xml" ; // test file.

   // loading file and creating first node venue_node.

   TiXmlDocument doc(filename) ;
   bool loadOkay = doc.LoadFile() ; 

   if (!loadOkay)
   {
      std::cout << "Could not load file " << filename << "." << " \n" ;
      cout << "Error = \"" << doc.ErrorDesc() << "\".  Exiting." << " \n" ;
      cin.get() ; exit(1) ;
   }

   std::cout << "file " << filename << " read in." << " \n\n" ;
   
    TiXmlNode* venue_file_node = doc.FirstChild("venue_file");
    assert(venue_file_node != 0);
    //cout << venue_file_node->Value() << endl;

    TiXmlNode* venue_node = venue_file_node->FirstChild();
    assert(venue_node != 0);
    //cout << venue_node->Value() << endl;


   New_Venue* venue = Venue_From_Xml::Get_Venue(venue_node);
   venue->Display();


   std::cout << " \n" << "end program." << " \n\n" ;

   cin.get();
   cin.get();
}