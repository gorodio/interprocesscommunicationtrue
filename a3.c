/************************************************************
*  Author: Genaro Orodio, masc1050                          *
*  Class: CS 570, Summer 2015, TTH 6:00 PM                  *
*  Professor: Guy Leonard                                   *  
*  Assignment: Assignment #3, Processes and IPC             *  
*  Completion Date: June 28, 2015                           * 
*                                                           *
*  Filename: a3.c                                           *
*                                                           *
*  This program was designed to demonstrate the use of      *
*  IPC mechanisms to control the use of processes. This     *
*  program utilizes pipes as the IPC mechanism to send      *
*  messages between processes. Three processes are created  *
*  and controlled accordingly. One process counts down the  *
*  remaining time left for the program to run. Once it      *
*  finishes it utilizes pipes to tell the other two         *  
*  processes to terminate their jobs. The second process    *
*  displays the current time every second, and the third    *
*  runs the uptime program every 5 seconds. The user        *
*  is able to specify the amount of seconds the program     *
*  will run. If no time is specified, the program will      *
*  run for a default 10 seconds.                            *
************************************************************/

#include "a3.h"

#define MESSAGE_SIZE 5
#define TIME_BUFFER 28		// will hold text for displaying current time
#define NUM_PIPES 2
#define FILE "/usr/bin/uptime"
#define FRIENDLY_MESSAGE "\nProcesses are finished! Have a Nice Day!\n\n"

int minutes, seconds;
int totalTime;		// will store the user's input
int pfd[NUM_PIPES];
char message[MESSAGE_SIZE];	// message buffer to be transmitted between processes

// will take the amount of minutes and seconds user specified and count down; will be displayed on screen every second
// once countdown is finished, it will send "DIE" via pipes to the other processes to signify a termination
void countdown(int remainingMinutes, int remainingSeconds) {

	// close any unused pipes
	close(pfd[0]);
	while (remainingSeconds > 0 || remainingMinutes > 0 ) {
		printf("Time Remaining: %02d:%02d\n", remainingMinutes, remainingSeconds--);
		if (remainingSeconds < 0) {	// decrements minutes if seconds go to zero
			remainingSeconds = 59;
			remainingMinutes--;
		}	
		strcpy(message, "LIVE");  // send message to other processes that it is still running
		write(pfd[1], message, MESSAGE_SIZE);
		sleep(1);
	}
	strcpy(message, "DIE");
	write(pfd[1], message, MESSAGE_SIZE);  // tell other processes to terminate
	close(pfd[1]);
	exit(0);
}

// method runs the uptime program every five seconds
void runUptimeProgram() {
	int time = totalTime;
	char *args[] = {FILE, (char*)0};
	close(pfd[0]);
	close(pfd[1]);
	while(time >= 5) {
		sleep(5);
		switch(fork()) {
			case 0:
				execv(FILE, args);
			case -1:
				printf("ERROR: Can't fork in uptime method.\n");
				exit(0);
			default:
				break;
		}		
		time -= 5;
	}
	exit(0);
}

// will display current time every second to the screen
// will keep displaying time until it is told to terminate
void displayTime() {
	time_t currentTime;
	struct tm *localTime;
	char timeBuffer[TIME_BUFFER];
	char test[MESSAGE_SIZE];
	strcpy(test, "DIE");
	close(pfd[1]);
	while(1) {
		// check if message came in to terminate
		read(pfd[0], message, MESSAGE_SIZE);
		if(strcmp(test, message) == 0) {
			close(pfd[0]);
			break;
		}
		currentTime = time(NULL);
		localTime = localtime(&currentTime);
		strftime(timeBuffer, TIME_BUFFER, "Current Time = %I:%M:%S %p\n", localTime);
		fputs(timeBuffer, stdout);
		sleep(1);
	}
	exit(0);
}

// conversion method that takes the user's input
// converts seconds to corresponding amount of minutes and seconds
// example: 61 seconds will convert to 1 minute and 1 second
void secondsToMinutes(int totalSeconds) {
	totalTime = seconds = totalSeconds;
	minutes = 0;
	if (totalSeconds >= 60) {
		minutes = totalSeconds / 60;
		seconds =  totalSeconds - (minutes*60);
	}
}

// customizable end message for program
// will wait a millisecond to print
void friendlyMessage() {
	usleep(1);	
	printf(FRIENDLY_MESSAGE);
}

// method creates and manages the three needed processes
// pipes are created and seconds are converted
void processManager(int time) {
	int status;	
	secondsToMinutes(time);
	pipe(pfd);
	
	// current time process
	switch(fork()) {
		case -1: 
			printf("Error creating child process one.");
			exit(0);
		case 0:
			displayTime();
			
		default:
			break;
	}
	
	// uptime program process
	switch(fork()) {
		case -1: 
			printf("Error creating child process two.");
			exit(0);
		case 0:
			runUptimeProgram();
			
		default:
			break;
	}		
	
	// remaining time process
	switch(fork()) {
		case -1: 
			printf("Error creating child process three.");
			exit(0);
		case 0:
			countdown(minutes, seconds);
			
		default:
			break;
	}	
	
	//parent closes unused pipes
	close(pfd[0]);
	close(pfd[1]);
	wait(&status);
	wait(&status);
	wait(&status);
	friendlyMessage();
	return;
	
}	

// will check if user input is valid
// if user input has no arguements, default 10 seconds will be used
// if user input has more than 3 arguments or the second argument is
// not a valid integer, then error is printed and program exits
void checkInput(int numArg, char *arg) {
	if (numArg == 1) {
		processManager(10);
		return;
	}	
	int i;
      	char* end;
      	long val = strtol(arg, &end, 10);  // check the whole argument
      	if (numArg == 2 && !end[0] && val >= 0){
        	processManager(val);
		return;
      	} 
	else {
		printf("ERROR: Usage = a3 or a3 [number >= 0]\n");
		exit(0);
	}	
  	
}
	

int main(int argc, char **argv) {
	checkInput(argc, *(argv+1));	
	return 0;
	
}
