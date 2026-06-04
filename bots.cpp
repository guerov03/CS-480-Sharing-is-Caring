#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main(){
	ofstream quoteFile; // Create object that writes to files
	quoteFile.open("QUOTE.txt"); //creates/opens QUOTE.txt
	quoteFile << "Process ID: " << getpid() << endl;
	quoteFile.close();

return 0;

}

