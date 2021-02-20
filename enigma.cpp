#include <iostream>

using namespace std;

struct rotor {
	int** alphabet;
	int number_of_notch;
	int* notch;
	int position;
};
struct reflector {
	int* alphabet;
};
struct machine {
	reflector ref;
	rotor* rot;
	int number_of_rot;
};
void rotorsinput(rotor* tabrot, int number, int number_of_rotors);

void reflectorsinput(reflector* tabref, int number, int number_of_ref);

void settings(machine* machine, rotor* tabrot, reflector* tabref);

void rotation(int* position, int number);

void coding(machine* machine, int number, int* message);

void check_if_rotate(machine* machine, int number, bool first, bool* secondturned);


int main() {
	int number = 0;
	int number_of_tasks = 0;
	int number_of_rotors=0;
    int number_of_reflectors = 0;
	cin >> number;
    rotor* tabrot;
	cin >> number_of_rotors;
	tabrot = new rotor[number_of_rotors];
	rotorsinput(tabrot, number, number_of_rotors);
	reflector* tabref;
	cin >> number_of_reflectors;
	tabref = new reflector[number_of_reflectors];
	reflectorsinput(tabref, number, number_of_reflectors);
	cin >> number_of_tasks;

	for (int i = 0; i < number_of_tasks; i++)
	{
		machine enigma;
		bool secondturned = false;
		bool first = true;

		settings(&enigma, tabrot, tabref);
		
		while (true)
		{
			int message;
			cin >> message;
			if (message == 0)
				break;
            rotation(&enigma.rot[0].position, number);
		     
			check_if_rotate(&enigma, number, first, &secondturned);

			coding(&enigma, number, &message);
			
			cout << message << " ";

			first = false;

		}
		cout << endl;
		delete[] enigma.rot;
	}

	for (int i = 0; i < number_of_rotors; i++)
	{
		delete[] tabrot[i].alphabet[0];
		delete[] tabrot[i].alphabet[1];
		delete[] tabrot[i].alphabet;
		delete[] tabrot[i].notch;
	}
	for (int i = 0; i < number_of_reflectors; i++)
	{
		delete[] tabref[i].alphabet;
	}

	delete[]tabrot;
	delete[]tabref;

}
void rotorsinput(rotor* tabrot, int number, int number_of_rotors)
{
	
	for (int i = 0; i < number_of_rotors; i++)
	{
		tabrot->alphabet = new int* [2];
		tabrot->alphabet[0] = new int[number];
		tabrot->alphabet[1] = new int[number];

		for (int j = 0; j < number; j++)
		{
			int input;
			cin >> input;
			tabrot->alphabet[0][j] = input - (j + 1);
			tabrot->alphabet[1][input - 1] = 1 + j - input;
		}

		cin >> tabrot->number_of_notch;
		if (tabrot->number_of_notch) {
			tabrot->notch = new int[tabrot->number_of_notch];
			for (int j = 0; j < tabrot->number_of_notch; j++)
				cin >> tabrot->notch[j];
		}
		else {
			tabrot->notch = new int[1];
			tabrot->notch[0] = 0;
		}
		tabrot++;
	}
	
}
void reflectorsinput(reflector* tabref, int number, int number_of_ref)
{
	int input;
	for (int i = 0; i < number_of_ref; i++)
	{
		tabref->alphabet = new int[number];

		for (int j = 0; j < number; j++)
		{
			
			cin >> input;
			tabref->alphabet[j] = input - (j + 1);
		}
		tabref++;
	}
	
}
void settings(machine* machine, rotor* tabrot, reflector* tabref)
{
	int rot_number, wchichposition;
	int ref_number;
	cin >> machine->number_of_rot;
	machine->rot = new rotor[machine->number_of_rot];
	
	for (int i = 0; i < machine->number_of_rot; i++)
	{
		cin >> rot_number >> wchichposition;

		tabrot[rot_number].position = wchichposition;
		machine->rot[i] = tabrot[rot_number];

	}
	
	cin >> ref_number;
	machine->ref = tabref[ref_number];
}
void rotation(int* position, int number)
{
	(*position)++;
	if (*position > number)*position = 1;

}
void check_if_rotate(machine* machine,  int number, bool first, bool* secondturned )
{
	bool turn2 = false;
	bool turn3 = false;
	if ((machine->number_of_rot > 2) && *secondturned)
	{
		int temporary = machine->rot[1].position + 1;
		if (temporary > number) temporary = 1;
		for (int i = 0; i < machine->rot[1].number_of_notch; i++)
		{
			if (temporary == machine->rot[1].notch[i])
			{
				turn2 = true;
				turn3 = true;
			}
		}
	}
	if (machine->number_of_rot > 1 && !first)
	{
		for (int i = 0; i < machine->rot[0].number_of_notch; i++)
			if (machine->rot[0].position == machine->rot[0].notch[i])
			{
				turn2 = true;
			}
		
	}
	(*secondturned) = false;
	if (turn2) {
		rotation(&machine->rot[1].position, number);
		*secondturned = true;
	}
	if (turn3) {
		rotation(&machine->rot[2].position, number);
		
	}
}
void coding(machine* machine, int number, int* message)
{
	int pos;
	(*message)--;
	for (int i = 0; i < machine->number_of_rot; i++)
	{
		pos = machine->rot[i].position - 1;
		(*message) += machine->rot[i].alphabet[0][(*message + pos) % number];
		while (*message < 0) *message += number;
		if (*message >= number) *message %= number;
	}
	(*message) += machine->ref.alphabet[*message];
	while (*message < 0) (*message) += number;
	if (*message >= number) (*message) %= number;

	for (int i = machine->number_of_rot - 1; i >= 0; i--)
	{
		pos = machine->rot[i].position - 1;
		*message += machine->rot[i].alphabet[1][(*message + pos) % number];
		while (*message < 0) (*message) += number;
		if (*message >= number) (*message) %= number;
	}
	(*message)++;
	if (*message > number) *message %= number;

}