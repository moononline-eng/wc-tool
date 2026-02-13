#include <fstream>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif
using namespace std;

int main(int argc, char* argv[]) {
	if (argc > 3) {
		return 1;
	}
	
	string flag;
	string textfile;

	bool useStdin = false;

	if (argc == 1) {
		flag = "";
		useStdin = true;
	}
	else if (argc == 2) {
		if (argv[1][0] == '-') {
			flag = argv[1];
			useStdin = true;
		}
		else {
			flag = "";
			textfile = argv[1];
		}
	}
	else if (argc == 3) {
		flag = argv[1];
		textfile = argv[2];
	}
	else {
		flag = "";
		textfile = argv[1];
	}

	istream* input; 
	ifstream file;

	if (useStdin) {
		#ifdef _WIN32
			_setmode(_fileno(stdin), _O_BINARY);
		#endif
		input = &cin;
	}
	else {
		file.open(textfile, ios::binary);
		if (!file) {
			std::cout << textfile << " : No such file or directory" << endl;
			return -1;
		}
		input = &file;
	}


	int lineCount = 0;
	int wordCount = 0;
	int charCount = 0;
	int byteCount = 0;
	bool inWord = false;

	char ch;
	
	while (input->get(ch)) {
		byteCount++;

		if ((ch & 0xC0) != 0x80) { //Check if there is no leading byte
			charCount++;
		}

		if (ch == '\n') {
			lineCount++;
			inWord = false;
		}
		else if (isspace(ch)) {
			inWord = false;
		}
		else if (!inWord) {
			wordCount++;
			inWord = true;
		}
	}
	
	if (!useStdin) {
		file.close();
	}

	string counts = flag == "-c" ? to_string(byteCount) :
					flag == "-l" ? to_string(lineCount) :
					flag == "-w" ? to_string(wordCount) :
					flag == "-m" ? to_string(charCount) :
					to_string(lineCount) + " " + to_string(wordCount) + " " + to_string(byteCount);
					

	cout << counts << " " << textfile << endl;
	return 0;
}