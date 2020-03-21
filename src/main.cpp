#include <iostream>
#include "utils.h"
#include "vigenere.h"

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
			else if (cmd == "V" || cmd == "v") menu = vig;
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

		case vig:
		{
			clear();

			string cmd;
			cout << "-- Vigenere Cipher --\n"
					 << "[E] Encrypt\n"
					 << "[D] Decrypt\n"
					 << "[R] Restore Backup\n"
					 << "[B] Back\n";
			cin >> cmd;

			if (cmd == "B" || cmd == "b") {
				menu = init;
				break;
			}
			clear();
			if (cmd == "E" || cmd == "e") 		 readInput(true);
			else if (cmd == "D" || cmd == "d") readInput(false);
			else if (cmd == "R" || cmd == "r") restoreBak();
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


int main(int argc, char* argv[]) {
	// enter and exit with command line args only
	if (argc > 1) {
		if((string)argv[1] == "-h" || (string)argv[1] == "-H" || (string)argv[1] == "--help") {

		}
		else if (((string)argv[1] == "V" || (string)argv[1] == "v") && argc == 4) {
			if((string)argv[3] == "-e" || (string)argv[3] == "-E" ||
				 (string)argv[3] == "-d" || (string)argv[3] == "-D") {
				std::string key;
				std::cout << "Enter a master password: ";
				std::cin >> key;
				readInput(argv[2], key, ((string)argv[3] == "-e" || (string)argv[3] == "-E"));
			} else if((string)argv[3] == "-r" || (string)argv[3] == "-R") {
				restoreBak();
			} else {
				std::cout << "Invalid flag. Run --help for more info.\n";
			}
		} else {
			std::cout << "Invalid flags. Run --help for more info.\n";
		}
		return 1;
	}

	// enter menu

	while(menu != quit) {
		setup();
	}
	clear();
	cout << "\xe2\x99\xa5  Goodbye! \xe2\x99\xa5\n";
	return 0;
}
