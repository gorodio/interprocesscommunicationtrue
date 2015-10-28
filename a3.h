/************************************************************
*  Author: Genaro Orodio, masc1050                          *
*  Class: CS 570, Summer 2015, TTH 6:00 PM                  *
*  Professor: Guy Leonard                                   *  
*  Assignment: Assignment #3, Processes and IPC             *  
*  Completion Date: June 28, 2015                           * 
*                                                           *
*  Filename: a3.h                                           *
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

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

void countdown(int remainingMinutes, int remainingSeconds);

void runUptimeProgram();

void displayTime();

void secondsToMinutes(int totalSeconds);

void friendlyMessage();

void processManager(int time);

void checkInput(int numArg, char *arg);
