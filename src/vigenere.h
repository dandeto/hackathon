#include <stdio.h>
#include <cstring>

char vigenere(char key, char input, bool e) {
	if(e) return (input + key) % 256;
	else  return (input - key) % 256;
}

// called from command line args only
void readInput(std::string filename, std::string key, bool e) {
	std::ifstream input(filename);
	std::ofstream bak(filename+".bak");
	std::string buffer;
	char data;
	int i = 0, max = key.length();
	
	while(input.get(data)) {
		bak << data;
		if (data == '\n') buffer += '\n';
		else {
			buffer += vigenere(key[i++],data, e);
			if (i >= max) i = 0;
		}
	}
	input.close();
	std::ofstream output(filename);
	output << buffer;
	clear();
	cout << "Operation complete.\n";
}

// called from menu
void readInput(bool e) {
	string key;
	cout << "-- Vigenere " << (e ? "Encryption" : "Decryption") << " --\n"
			 << "Enter a master password: ";
	cin >> key;

	ifstream input;
	string filename = filePrompt("Please enter a file name or path to it: ", input);

	ofstream bak(filename+".bak");
	string buffer;
	char data;
	int i = 0, max = key.length();
	
	while(input.get(data)) {
		bak << data;
		if (data == '\n') buffer += '\n';
		else {
			buffer += vigenere(key[i++],data, e);
			if (i >= max) i = 0;
		}
	}
	input.close();
	ofstream output(filename);
	output << buffer;
	output.close(); // close so users can open in txt editor while this is running
	bak.close();

	// Delete the bak file?

	string cmd;

	do {
		clear();
		cout << "Printing the first 50 characters of the "
				 << (e ? "encrypted " : "decrypted ")
				 << "file: " << filename << "\n\n"
				 << buffer.substr(0,50) << "\n\n"
				 << "Delete the backup file?\n"
				 << "[Y] Yes!\n"
				 << "[N] No!\n";
		cin >> cmd;

		if(cmd == "Y" || cmd == "y") remove((filename+".bak").c_str());
	} while(cmd != "Y" && cmd != "y" && cmd != "N" && cmd != "n"); // please don't do this crap ever again
}

void restoreBak() {
	ifstream tmp;
	string filename = filePrompt("Please enter a file name or path to the file *to restore*: ", tmp);
	tmp.close();

	ifstream bak(filename+".bak");

	if(!bak) {
		cout << "Error: the file \'" << filename << ".bak\' does not exist.\n";
		pause();
		return;
	}
	ofstream output(filename);
	char data;
	while(bak.get(data)) output << data;	
}
