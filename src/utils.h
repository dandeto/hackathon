using namespace std;

// Display utils
void clear() {cout << "\033c";}

void pause() { //wait for user input
	char input;
	cout << "\n\n-- Press ENTER to continue --";
	cin.ignore(5,'\n'); //needs this only if cin. will fix later
	cin.ignore(5,'\n');
	clear();
}

int obtainInteger(int lower, int upper) {
	//bounds are inclusive
	int cmd;
	if (cin >> cmd) {
		if (cmd >= lower && cmd <= upper) { //correct!
			return cmd;
		}
	} else { //fail state
		cin.clear();
		cin.ignore(255, '\n'); // INT_MAX?
	}
	return -1; // invalid, try again.
}

//PROMPT SYSTEM

// menu states
enum MENU { init, convert, date, md, arc, mtp, quit };
MENU menu = init;
