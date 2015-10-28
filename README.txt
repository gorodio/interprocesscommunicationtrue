/************************************************************
*  Author: Genaro Orodio, masc1050                          *
*  Class: CS 570, Summer 2015, TTH 6:00 PM                  *
*  Professor: Guy Leonard                                   *  
*  Assignment: Assignment #3, Processes and IPC             *  
*  Completion Date: June 28, 2015                           * 
*                                                           *
*  Filename: README.txt                                     *
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

***********************************************
* FILE MANIFEST:                              *
* Makefile                                    *
* a3.c                                        *  
* a3.h                                        *                               
* README.txt                                  *
***********************************************

***************************************************************************
* #####################  INSTRUCTIONS  #######################            *
*                                                                         *         
* Compile instructions:    type: make                                     *
*                          to compile.                                    *
*                                                                         *
* Operating instructions:  type a3 [number of seconds]                    *
*				   OR                                     *
*		           type a3                                        * 
*			                                                  *
*			   The program will now run for the default       *
*			   10 seconds or the number of seconds specified. *
*			   Current time and the countdown timer will be   *
*			   displayed every second, and the uptime program *
*			   every 5 seconds. Once the timer expires,       *
*			   program will terminate all processes and exit  *
*			   with a friendly message.                       *
***************************************************************************

****************************************************************
* DEFICIENCIES:                                                *
* 1. Odd occurence if the seconds specified is a multiple of   * 
*    5 seconds. Since the uptime program runs every 5 seconds  *
*    this is most likely the problem. After the final uptime   *
*    program is ran, the friendly message will appear before   *
*    the final uptime program everytime. I did a minor fix in  *
*    which the message will sleep for a millisecond and then   *
*    print to screen.                                          *
*                                                              *
* 2. a3 0989 or 07  are valid inputs                           *
*    Numbers with leading zeroes are valid inputs.             *
****************************************************************

*********************************************************
* DESIGN DECISIONS:                                     *
*  1. Again, I wanted to make the program a bit         *
*     customizable, perhaps for my own learning         *
*     purposes.                                         *
*                                                       *
*********************************************************                                                        

*******************************************************
* EXTRA FEATURES:                                     *
* 1. The program has extensive user input validation. * 
*                                                     *       
*******************************************************

************************************************************************************
*   LESSONS LEARNED:                                                               *
*	  Creating processes and utilizing IPC to control your processes is very   *
*	  important, yet very easy to get wrong. "With great power comes great     *
*	  responsibility." I learned this the hard way with this program.          *
*	                                                                           *
*	  I had created a runaway fork() problem within rohan and was not able     * 
*	  to log back in because of it. I had created a situation in which fork()  *
*	  was being called infinitely within my program and there was no way to    *
*	  stop it. I was being careless with the use of fork().                    *
*	                                                                           *
*	  At this time, I had no idea what was happening to my masc account        *
*	  and what had gone wrong. I logged into my other rohan                    *
*	  account to see what the problem was. I typed "ps -u masc1050" to         *
*	  display the locked account's processes. There were many                  *
*	  defunct processes that I had created. Good thing rohan has a             *
*	  quota system that prevents my processes from affecting other users.      *
*	                                                                           *
*	  Once I gained access to my account, I became more aware and              *
*	  careful with the power of fork().                                        * 
*	                                                                           *
*	  Additionally, IPC mechanisms make a lot more sense now. I had            *
*	  no idea what and how pipes worked until now. I now envision them         *
*	  as telephones in which one process can tell another process              *
*	  a message through the pipe. Really powerful stuff.                       *
*                                                                                  *
************************************************************************************
