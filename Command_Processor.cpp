#include <iostream>
#include "Command_Processor.h"
using namespace std;

State** Command_Processor::states = 0;
int* Command_Processor::nr_states = 0;
State* Command_Processor::selected_state = 0;

Command_States Command_Processor::command_state = Initial;

Menu* Command_Processor::menus[NR_CMD_STATES];

void Command_Processor::Create_Menus()
{
    // Menu for Initial command state
    Menu* menu = new Menu("Enter command number");
    menu->Add_Command("Select State");
    menu->Add_Command("Add State");
    menu->Add_Command("Quit");
    menus[0] = menu;

    // Menu for State Selected
    menu = new Menu("Enter command number");
    menu->Add_Command("Add City");
    menu->Add_Command("Change State");
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

void Command_Processor::Process_Commands(State** states_,
                                         int* nr_states_)
{
    cout << "Process commands starting\n";

    states = states_;
    nr_states = nr_states_;

    Create_Menus();

    while (command_state != Done)
    {
        if (command_state == State_Selected)
        {
            cout << "Selected state is "
                 << selected_state->Name() << endl;
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
    if (cmd == "Select State")
    {
        // Select state
        //cout << "Select State command\n";
        Select_State();
        command_state = State_Selected;
    }
    else if (cmd == "Add State")
    {
        // Add state
        //cout << "Add State command\n";
        Add_State();
        command_state = State_Selected;
    }
    else
    {
        //cout << "Quit command\n";
        Output_XML();
        command_state = Done;
    }
}

City* Command_Processor::Get_City()
{
    string name;
    cout << "City name: ";
    getline(cin, name);
    City* city = new City(name);
    return city;
}

// Process command in State Selected command state
void Command_Processor::Process_Command_1(const string& cmd)
{
    if (cmd == "Add City")
    {
        // Add City
        //cout << "Add City command\n";
        City* city = Get_City();
        selected_state->Add_City(*city);
        delete city;
        selected_state->Display();
    }
    else if (cmd == "Change State")
    {
        //cout << "Change State command\n";
        command_state = Initial;
    }
    else
    {
        //cout << "Quit command\n";
        Output_XML();
        command_state = Done;
    }
}

void Command_Processor::Select_State()
{
    Menu* menu = new Menu("Select State");
    for (int i = 0; i < *nr_states; ++i)
    {
        menu->Add_Command(states[i]->Name());
    }

    const string* state_name = menu->Get_Command();

    // Find state with this name
    for (int i = 0; i < *nr_states; ++i)
    {
        if (states[i]->Name() == *state_name)
        {
            selected_state = states[i];
            command_state = State_Selected;
            return;
        }
    }
    // Should never reach this point.
    cout << "Error in Command_Processor::Select_State()\n";
}

void Command_Processor::Add_State()
{
    string state_name;
    string capital_name;
    cout << "State name: ";
    getline(cin, state_name);
    cout << "Capital city name: ";
    getline(cin, capital_name);
    City* capital = new City(capital_name);
    State* state = new State(state_name, *capital);
    delete capital;
    states[(*nr_states)++] = state;
    selected_state = state;
}

void Command_Processor::Output_XML()
{
    ofstream outfile;
    outfile.open("states2.xml");
    if (!outfile.is_open())
    {
        cout << "Failed to open file for output\n";
        return;
    }

    outfile << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    outfile << "<USA>\n";
    for (int i = 0; i < *nr_states; ++i)
    {
        states[i]->Output_XML(outfile);
    }
    outfile << "</USA>\n";
    outfile.close();
    cout << "File states2.xml written\n";
}

