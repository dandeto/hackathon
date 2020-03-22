#include <iostream>
#include <vector>
#include "utils.h"
#include "vigenere.h"
#include "pad.h"

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

		case mtp:
		{
			string key = "lemo";
			//string plaintext = "cryptoisshortforcryptography";
			string plaintext = "twasnovemberalthoughitwasnotyetlatetheskywasdarkwheniturnedintolaundresspassagefatherhadfinishedforthedayswitchedofftheshoplightsandclosedtheshuttersbutsoiwouldnotcomehometodarknesshehadleftonthelightoverthestairstotheflatthroughtheglassinthedooritcastafoolscaprectangleofpalenessontothewetpavementanditwaswhileiwasstandinginthatrectangleabouttoturnmykeyinthedoorthatifirstsawtheletteranotherwhiterectangleitwasonthefifthstepfromthebottomwhereicouldntmissiticlosedthedoorandputtheshopkeyinitsusualplacebehindbaileysadvancedprinciplesofgeometrypoorbaileynoonehaswantedhisfatgraybookforthirtyyearssometimesiwonderwhathemakesofhisroleasguardianofthebookshopkeysidontsupposeitsthedestinyhehadinmindforthemasterworkthathespenttwodecadeswriting";
			string ciphertext;
			int max = key.length(), j = 0;

			for (int i = 0; i < plaintext.length(); ++i) {
				ciphertext += encrypt(key[j++], plaintext[i], true);
				if(j >= max) j=0;
			}
			//cout << plaintext << "\n" << ciphertext << "\n";

			int coincidences[26] = {0}; // one entry for each character. index in using the mapping
			vector<Coincidence> rounds;
			// shift one space for each character and count # of coincidences.
			for (int i = 1; i < ciphertext.length(); ++i) {
				string shift = ciphertext.substr(0,ciphertext.length()-i);
				cout << ciphertext << '\n' << string(i, ' ') << shift << '\n';
				cout << "Coincidences: ";
				int num_coincidences = 0;
				for (int j = 0; j < shift.length(); ++j) {
					if(shift[j] == ciphertext[j+i]) {
						cout << shift[j] << ciphertext[j+i] << " ";
						++coincidences[char_to_num[shift[j]]];
						++num_coincidences;
					}
				}
				//add to vector
				/*if(num_coincidences)*/ rounds.push_back(Coincidence(i, num_coincidences));
				cout << "\n\n";
			}

			// then find the numbers (in the key)

			cout << "-- Coincidence Data --\n";
			for (int i = 0; i < rounds.size(); ++i) {
				cout << "Round " << rounds[i].round << " had " << rounds[i].number << " coincidences.\n";
			}

			// ask user to determine the length of the key
			int key_length = -1;
			while(key_length == -1) {
				cout << "\nBased on the data, please provide a guess as to the key length: ";
				key_length = obtainInteger(1, 1000);
			}

			vector<string> chunks;
			// for each key length, group letters and determine their freq in cipher text.
			for(int i = 0; i < key_length; ++i) { //ex: if key_length = 4 count freq of each at every 4th.
				chunks.push_back("");
				for(int j = 0; j < ciphertext.length() / key_length; ++j) {
					if(j*key_length <= ciphertext.length()-1) chunks[i] += ciphertext[j*key_length + i];
				}
				cout << chunks[i] << '\n';
			}

			string build_key = "";

			for (int k = 0; k < key_length; ++k) {

				Letters l;
				for (int i = 0; i < chunks[k].size(); ++i) {
					l.findLetter(char_to_num[chunks[k][i]]);
				}
				// determine frequency of letters
				for (int i = 0; i < l.letters.size(); ++i) {
					l.calcFreq(chunks[k].size());
					cout << "letter: " << num_to_char[l.letters[i].number] << " occurs: " << l.letters[i].occurances
							 << " frequency: " << l.letters[i].frequency << "\n\n";
				}

				// shift 25 times, each time multiplying by the freq of each letter in english to get its true freq

			
				float current_freq = 0, max_freq = 0;
				int shift_number = 0;
				for (int i = 0; i < 26; ++i) {
					for (int j = 0; j < l.letters.size(); ++j) { // loop thru the numbers
						cout << ((j+i) %26) << " ";
						current_freq += l.letters[j].frequency*num_to_freq[(j+i) % 26]; // shift by i
					}
					cout << "freq: " << current_freq << '\n';
					if (max_freq < current_freq) {
						max_freq = current_freq; //save shift number too
						current_freq = 0;
						shift_number = i;
					}
				}
				cout << "\nmax freq: " << max_freq << " shift number: " << shift_number << '\n';
				// shift number that yields the highest value shouold be the shift for that space of the key.
				build_key += num_to_char[shift_number];
			}

			cout << build_key << '\n'; // you got the key!
			

			// ask user to verify or give a guess as to what the key is, or go back to a different number of letters in the key.


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
