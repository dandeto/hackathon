#include <iostream>
#include "utils.h"





void setup() {
	switch(menu) {
		case init: // start menu
		{
			clear();
			string cmd;
			cout << "Welcome Adventurer!\n"
					 << "[H] Hex Converter\n"
					 << "[D] Date Hack\n"
					 << "[M] Display Metadata attached to an image\n"
					 << "[C] Crack a password protected archive with a dictionary attack\n"
					 << "[V] Encrypt / Decrypt a file with a Vigenere Cipher\n"
					 << "[P] Crack Many-Time-Pad encryption\n"
					 << "[Q] Quit\n";
			cin >> cmd;

			if (cmd == "H" || cmd == "h") 	   menu = convert;
			else if (cmd == "D" || cmd == "d") menu = date;
			else if (cmd == "M" || cmd == "m") menu = md;
			else if (cmd == "C" || cmd == "c") menu = arc;
			else if (cmd == "P" || cmd == "p") menu = mtp;
			else if (cmd == "Q" || cmd == "q") menu = quit;
			clear();
		}
		break;

		case convert:
		{
			cout << "converting goes here (maybe another menu) \n";
			pause();
			menu = init;
		}
		break;

		case md:
		{
			//menu for metadata
			ifstream input;
			filePrompt("Enter the name or path to an image: ", input);
			readImage(input);
			
		}
		break;

		default:
			cout << "This option has not been implemented yet :/\n";
			pause();
			menu = init;
		break;
	}
}


int main() {
	while(menu != quit) {
		setup();
	}
	clear();
	cout << "Goodbye! \xe2\x99\xa5\n";
	return 0;
}
