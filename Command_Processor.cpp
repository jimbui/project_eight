#include <iostream>
#include "Command_Processor.h"
using namespace std;

New_Venue** Command_Processor::venues = 0;
int* Command_Processor::nr_venues = 0;
New_Venue* Command_Processor::selected_venue = 0;

Command_States Command_Processor::command_state = Initial;

Menu* Command_Processor::menus[NR_CMD_STATES];

void Command_Processor::Create_Menus()
{
    // Menu for Initial command state
    Menu* menu = new Menu("Enter command number");
    menu->Add_Command("Select Venue");
    menu->Add_Command("Quit");
    menus[0] = menu;

    // Menu for Venue Selected
    menu = new Menu("Enter command number");
    menu->Add_Command("Display Venue");
    menu->Add_Command("Select Show");
	menu->Add_Command("Change Venue");
    menu->Add_Command("Quit");
    menus[1] = menu;
}

//void Command_Processor::Process_Commands()
//{
//    cout << "Process_Commands starting\n";
//
//    while (command_state != Done)
//    {
//        // Execute next command
//        cout << "Process_Commands running\n";
//        command_state = Done;
//    }
//
//    cout << "Process_Commands  exiting\n";
//}

void Command_Processor::Process_Commands(New_Venue** venues_,
                                         int* nr_venues_)
{
    cout << "Process commands starting\n";

    venues = venues_;
    nr_venues = nr_venues_;

    Create_Menus();

    while (command_state != Done)
    {
        if (command_state == State_Selected)
        {
            cout << "Selected venue is "
                 << selected_venue->Name() << endl;
        }
        const string* cmd = menus[command_state]->Get_Command();


        switch (command_state)
        {
        case Initial:   Process_Command_0(*cmd);
            break;

        case State_Selected:    Process_Command_1(*cmd);
            break;

        case Done:  break;      // Can't happen
        }
    }

    cout << "Command_Processor exiting\n";
}

// Process command in Initial command state
void Command_Processor::Process_Command_0(const string& cmd)
{
    if (cmd == "Select Venue")
    {
        // Select venue
        //cout << "Select venue command\n";
        Select_Venue();
        command_state = State_Selected;
    }
    else
    {
        //cout << "Quit command\n";
        command_state = Done;
    }
}

// Process command in State Selected command state
void Command_Processor::Process_Command_1(const string& cmd)
{
    if (cmd == "Display Venue")
    {
        // Add City
        //cout << "Add City command\n";
        selected_venue->Display();
    }
    else if (cmd == "Select Show")
    {
        //cout << "Change State command\n";
		cout << "Select_Show Called" << endl;
        //command_state = State_Selected;
    }
	else if (cmd == "Change Venue")
    {
        //cout << "Change State command\n";
        command_state = Initial;
    }
    else
    {
        //cout << "Quit command\n";
        command_state = Done;
    }
}

void Command_Processor::Select_Venue()
{
    Menu* menu = new Menu("Select Venue");
    for (int i = 0; i < *nr_venues; ++i)
    {
		menu->Add_Command(venues[i]->Name());
    }


    const string* venue_name = menu->Get_Command();

    // Find venue with this name
    for (int i = 0; i < *nr_venues; ++i)
    {
        if (venues[i]->Name() == *venue_name)
        {
            selected_venue = venues[i];
            command_state = State_Selected;
            return;
        }
    }
    // Should never reach this point.
    cout << "Error in Command_Processor::Select_Venue()\n";
}


