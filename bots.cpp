#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

// Semsphore that controls access to QUOTE.txt
sem_t FLAG;

// Function that each thread will run
void* botThread(void* arg)
{
	int threadNum = *((int*)arg);
	
	for (int i = 0; i < 8; i++) // Each thread writes its quote  8 times
	{
		// Even threads wait 2 seconds, odd threads wait 3 seconds
		if (threadNum % 2 == 0)
			sleep(2);
		else
			sleep(3);

		// Lock semaphore before writing to shared file
		sem_wait(&FLAG);

		ofstream quoteFile;
		quoteFile.open("QUOTE.txt", ios::app);

		if (threadNum % 2 == 0)
		{
			quoteFile << "Thread ID " << threadNum
				  << ": \"Controlling complexity is the essence of computer programming.\" --Brian Kernighan"
				  << endl;
	}
	else
	{
		quoteFile << "Thread ID " << threadNum
			  << ": \"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra"
			  << endl;
	}
	
	cout << "Thread " << threadNum << " is running" << endl;

	quoteFile.close();

	// Release semaphore after writing 
	sem_post(&FLAG);
     }
     
     pthread_exit(NULL);
}

int main()
{
	ofstream quoteFile; // Create object that writes to files
	quoteFile.open("QUOTE.txt"); //creates/opens QUOTE.txt
	quoteFile << "Process ID: " << getpid() << endl;
	quoteFile.close();

	pthread_t threads[7];
	int threadNums[7];

	// Initialize semaphore with value 1
	sem_init(&FLAG, 0, 1);

	// Create 7 threads
	for (int i = 0; i < 7; i++)
	{
		threadNums[i] = i + 1; // + 1 ensures 1-7 and not 0-6
		cout << "Creating thread, in main(): " << threadNums[i] << endl;
		pthread_create(&threads[i], NULL, botThread, &threadNums[i]);
}

	// Wait for all threads to finish
	for (int i = 0; i < 7; i++)
	{
		pthread_join(threads[i], NULL);
	}

	// Destroy Semaphore
	sem_destroy(&FLAG);

	cout << "All chatbot threads have finished. Program exiting safely." << endl;

return 0;

}

