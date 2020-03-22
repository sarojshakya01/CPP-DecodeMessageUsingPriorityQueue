#include<iostream>
#include <queue>
#include <cstring>
#include <fstream>
#include "ArgumentManager.h"

#define max_cmnd_length 512
#define max_cmnd_of_same_priority 100
#define tot_priority 10

using namespace std;

// funtion to fing any string in given source string
bool isFound(string src, string str) {
	bool found = false;
	for (int i = 0; i < src.length(); ++i) {
		if (src[i] == str[0]) {
			found = true;
			for (int j = 0; j < str.length(); ++j) {
				if (src[i+j] != str[j]) {
					found = false;
					break;
				}
			}
			if (found) break;
		}
	}
	return found;
}

// function to extract command only
string getCommand(string str) {
	char *temp = new char[max_cmnd_length];
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '(') {
			temp[i] = '\0';
			break;
		}
		temp[i] = str[i];
	}
	return temp;
}

// funtion to extract priority only
int getPriority(string str) {
	char b = ' ';
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '(') {
			b = str[i+1];
		}
	}
	return int(b-48);
}

// array to define cutomized priority
static int aprio[tot_priority] = {1*max_cmnd_of_same_priority,
								  2*max_cmnd_of_same_priority,
								  3*max_cmnd_of_same_priority,
								  4*max_cmnd_of_same_priority,
								  5*max_cmnd_of_same_priority,
								  6*max_cmnd_of_same_priority,
								  7*max_cmnd_of_same_priority,
								  8*max_cmnd_of_same_priority,
								  9*max_cmnd_of_same_priority,
								  10*max_cmnd_of_same_priority};

// structure to store command with given priority and cutomized priority
struct Command {
	int prio;
	int cprio;
	string cmnd;
	Command(){}
	Command(int p, string c) : prio(p),cmnd(c) {
		int idx = p-1;

		if (p == 1) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 2) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 3) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 4) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 5) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 6) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 7) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 8) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 9) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
		else if (p == 10) {
			cprio = aprio[idx];
			aprio[idx] = aprio[idx]+1;
		}
	}
};

// operator function to store the priority que based on customized priority
bool operator < (Command const & c1, Command const & c2) {
	return c1.cprio > c2.cprio;
}

// class to decode message
class decode_message {
	ifstream ifile;
	ofstream ofile;
	priority_queue <Command> pquecmnd; // priority que to store command
	queue <string> quemsg; // que to store message

public:

	decode_message() {}

	decode_message(string, string);

	~decode_message() {
		ifile.close();
		ofile.close();
	}

	void decode(string);
	void replace(string);
	void add(string);
	void remove(string);
	void swap(string);
	void print();
	void dispQue(queue <string>);
	void dispPQue(priority_queue <Command>);
	void process();
};

// constructor to create priority que based on given priority with the help of cutomized priority
decode_message :: decode_message(string infilename, string outfilename) {
	ifile.open(infilename);
	string line;
	while(getline(ifile, line)) {
		pquecmnd.push(Command(getPriority(line),getCommand(line)));
	}
	ofile.open(outfilename);
}

// funtion to copy the decoded message to quemsg
void decode_message :: decode(string msg) {
	char *temp = new char[max_cmnd_length];
	int j = 0;
	bool ismsg = false;
	for (int i = 0; i < msg.length(); ++i) {
		if (msg[i] == '[') {
			ismsg = true;
		} else if (msg[i] == ']'){
			ismsg = false;
		} else if (ismsg) {
			temp[j] = msg[i];
			j++;
		}
	}
	temp[j] = '\0';
	quemsg.push(temp);
}

// function to replace the character 'a' in decoded message by 'b' character as in format [a,b]
void decode_message :: replace(string msg) {
	char ch1,ch2;
	for (int i = 0; i < msg.length(); ++i) {
		if (msg[i] == '[') {
			ch1 = msg[i+1];
		}
		if (msg[i] == ']') {
			ch2 = msg[i-1];
		}
	}

	string oldmsg = quemsg.front();
	string newmsg = oldmsg;
	for (int i = 0; i < oldmsg.length(); ++i) {
		if (newmsg[i] == ch1) {
			newmsg[i] = ch2;
		}
	}
	quemsg.pop();
	quemsg.push(newmsg);
}

// function to add the character 'a' in decoded message after 'b' character as in format [b,a]
void decode_message :: add(string msg) {
	char ch1,ch2;

	for (int i = 0; i < msg.length(); ++i) {
		if (msg[i] == '[') {
			ch1 = msg[i+1];
		}
		if (msg[i] == ']') {
			ch2 = msg[i-1];
		}
	}

	string oldmsg = quemsg.front();
	string temp = oldmsg;
	char * newmsg = new char[max_cmnd_length];
	bzero(newmsg,0);
	int j = 0;
	for (int i = 0; i < temp.length(); ++i, ++j) {
		newmsg[j] = temp[i];
		if (temp[i] == ch1) {
			newmsg[j+1] = ch2;
			j++;
		}
	}
	newmsg[j] = '\0';
	quemsg.pop();
	quemsg.push(newmsg);
}

// function to remove the character 'a' in decoded messageas in format [a]
void decode_message :: remove(string msg) {
	char ch;
	for (int i = 0; i < msg.length(); ++i) {
		if (msg[i] == '[') {
			ch = msg[i+1];
		}
	}

	string oldmsg = quemsg.front();
	char * newmsg = new char[max_cmnd_length];
	bzero(newmsg,0);
	int j = 0;
	for (int i = 0; i < oldmsg.length(); ++i) {
		if (oldmsg[i] != ch) {
			newmsg[j] = oldmsg[i];
			j++;
		}
	}
	newmsg[j] = '\0';
	quemsg.pop();
	quemsg.push(newmsg);
}

// function to swap the character 'a' and 'b' in decoded messageas in format [a,b]
void decode_message :: swap(string msg) {
	char ch1,ch2;
	for (int i = 0; i < msg.length(); ++i) {
		if (msg[i] == '[') {
			ch1 = msg[i+1];
		}
		if (msg[i] == ']') {
			ch2 = msg[i-1];
		}
	}

	string oldmsg = quemsg.front();
	string newmsg = oldmsg;
	for (int i = 0; i < oldmsg.length(); ++i) {
		if (newmsg[i] == ch1) {
			newmsg[i] = ch2;
		} else if (newmsg[i] == ch2) {
			newmsg[i] = ch1;
		}
	}
	quemsg.pop();
	quemsg.push(newmsg);
}

// function to print the message fron top of quemsg and pop it from the que
void decode_message :: print() {
	if (!quemsg.empty()) {
		string msg = quemsg.front();
		ofile << msg << endl;
		cout << msg << endl;
		quemsg.pop();
	}
}

// function to display String Queue
void decode_message :: dispQue(queue<string> que) {
	while (!que.empty()) {
		cout << que.front() << endl;
		que.pop();
	}
}

// funtion to display Comnnad type priority Queue
void decode_message :: dispPQue(priority_queue <Command> pq) {
	while (!pq.empty()) {
		Command sc = pq.top();
		cout << sc.prio << " " << sc.cprio << " " << sc.cmnd << endl;
		pq.pop();
	}
}

// funtion to process the decoding
void decode_message :: process() {

	Command topcmnd;
	while (!pquecmnd.empty()) {
		topcmnd = pquecmnd.top();
		if (isFound(topcmnd.cmnd, "DECODE")) {
			decode(topcmnd.cmnd);
		} else if (isFound(topcmnd.cmnd, "REPLACE")) {
			replace(topcmnd.cmnd);
		}  else if (isFound(topcmnd.cmnd, "ADD")) {
			add(topcmnd.cmnd);
		}  else if (isFound(topcmnd.cmnd, "REMOVE")) {
			remove(topcmnd.cmnd);
		}  else if (isFound(topcmnd.cmnd, "SWAP")) {
			swap(topcmnd.cmnd);
		}  else if (isFound(topcmnd.cmnd, "PRINT")) {
			print();
		}
		pquecmnd.pop();
	}
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		cout << "Invalid parameters" << endl;
		exit(EXIT_FAILURE); // terminate with error
	}

	ArgumentManager am(argc, argv);

	string infilename = am.get("input");// get the input filename
	string outfilename = am.get("output"); // get the output filename

	decode_message dm(infilename,outfilename);
	dm.process();
	return 0;
}