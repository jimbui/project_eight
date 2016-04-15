#pragma once
#include <string>
#include "Menu.h"
#include "City.h"
#include "State.h"

enum Command_States { Initial, State_Selected, Done };
using namespace std;
class Command_Processor
{
public:
    //static void Process_Commands();
    static void Process_Commands(State** states_, int* nr_states_);

private:
    static const int NR_CMD_STATES = (int)Done + 1;
    static Command_States command_state;

    static Menu* menus[NR_CMD_STATES];
    Command_Processor(void) {};
    static void Create_Menus();
    static void Process_Command_0(const string& cmd);
    static void Process_Command_1(const string& cmd);
    static void Select_State();
    static State** states;
    static int* nr_states;
    static State* selected_state;
    static void Add_State();
    static City* Get_City();
    static void Output_XML();

};


