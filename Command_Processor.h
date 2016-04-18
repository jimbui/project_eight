#pragma once
#include <string>
#include "Menu.h"
#include "New_Venue.h"


enum Command_States { Initial, State_Selected, Done };
using namespace std;
class Command_Processor
{
public:
    //static void Process_Commands();
    static void Process_Commands(New_Venue** venues_, int* nr_venues_);

private:
    static const int NR_CMD_STATES = (int)Done + 1;
    static Command_States command_state;

    static Menu* menus[NR_CMD_STATES];
    Command_Processor(void) {};
    static void Create_Menus();
    static void Process_Command_0(const string& cmd);
    static void Process_Command_1(const string& cmd);
    static void Select_Venue();
    static New_Venue** venues;
    static int* nr_venues;
    static New_Venue* selected_venue;
    //static void Add_State();
    //static City* Get_City();
   // static void Output_XML();

};


