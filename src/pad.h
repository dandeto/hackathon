#include <map>

std::map<char, int> char_to_num = {
  { 'a', 0  }, { 'b', 1  }, { 'c', 2  },
  { 'd', 3  }, { 'e', 4  }, { 'f', 5  },
  { 'g', 6  }, { 'h', 7  }, { 'i', 8  },
  { 'j', 9  }, { 'k', 10 }, { 'l', 11 },
  { 'm', 12 }, { 'n', 13 }, { 'o', 14 },
  { 'p', 15 }, { 'q', 16 }, { 'r', 17 },
  { 's', 18 }, { 't', 19 }, { 'u', 20 },
  { 'v', 21 }, { 'w', 22 }, { 'x', 23 },
  { 'y', 24 }, { 'z', 25 }
};

std::map<int, char> num_to_char = {
  { 0 , 'a' }, { 1 , 'b' }, { 2 , 'c' },
  { 3 , 'd' }, { 4 , 'e' }, { 5 , 'f' },
  { 6 , 'g' }, { 7 , 'h' }, { 8 , 'i' },
  { 9 , 'j' }, { 10, 'k' }, { 11, 'l' },
  { 12, 'm' }, { 13, 'n' }, { 14, 'o' },
  { 15, 'p' }, { 16, 'q' }, { 17, 'r' },
  { 18, 's' }, { 19, 't' }, { 20, 'u' },
  { 21, 'v' }, { 22, 'w' }, { 23, 'x' },
  { 24, 'y' }, { 25, 'z' }
};

/*std::map<int, int> char_to_num = {
  { , 0 }, { , 1 }, { , 2 },
  { , 3 }, { , 4 }, { , 5 },
  { , 6 }, { , 7 }, { , 8 },
  { , 9 }, { , 10 }, { , 11 },
  { , 12 }, {, 13 }, { , 14 },
  { , 15 }, {, 16 }, { , 17 },
  { , 18 }, {, 19 }, { , 20 },
  { , 21 }, {, 22 }, { , 23 },
  { , 24 }, {, 25 }
};*/

std::map<int, float> num_to_freq = {
  { 0 , .08167 }, { 1 , .01492 }, { 2 , .02202 },
  { 3 , .04253 }, { 4 , .12702 }, { 5 , .02228 },
  { 6 , .02015 }, { 7 , .06094 }, { 8 , .06966 },
  { 9 , .00153 }, { 10, .01292 }, { 11, .04025 },
  { 12, .02406 }, { 13, .06749 }, { 14, .07507 },
  { 15, .01929 }, { 16, .00095 }, { 17, .05987 },
  { 18, .06327 }, { 19, .09356 }, { 20, .02758 },
  { 21, .00978 }, { 22, .02560 }, { 23, .00150 },
  { 24, .01994 }, { 25, .00077 }
};

struct Coincidence {
	int round;
	int number;
	Coincidence(int r, int n) : round(r), number(n) {};
};

struct Data {
	int number;
	int occurances;
	float frequency;
	Data(int n, int m) : number(n), occurances(m) {};
};

struct Letters {
	vector<Data> letters;

	void findLetter(int id) {
		for (int i = 0; i < letters.size(); ++i) {
			if(letters[i].number == id) {
				++letters[i].occurances;
				return;
			}
		}
		// not found
		letters.push_back(Data(id, 1));
	}

	bool exists(int id) {
		for (int i = 0; i < letters.size(); ++i)
			if(letters[i].number == id) return true;
		return false;
	}

	/*Data getLetter(int id) {
		for (int i = 0; i < letters.size(); ++i)
			if(letters[i].number == id) return letters[i];
		return NULL;
	}*/

	void calcFreq(float size) {
		for(int i = 0; i < letters.size(); ++i) 
			letters[i].frequency = (float)letters[i].occurances / size;
	}
};

char encrypt(char key, char input, bool e) {
	int i = char_to_num[input];
	int k = char_to_num[key];
	if(e) return num_to_char[(i + k) % 26];
	else  return num_to_char[(i - k) % 26];
}
