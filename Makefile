############################################################
#  Author: Genaro Orodio, masc1050                         #
#  Class: CS 570, Summer 2015, TTH 6:00 PM                 #    
#  Professor: Guy Leonard                                  #  
#  Assignment: Assignment #3, Processes and IPC            # 
#  Completion Date: June 28, 2015                          # 
#                                                          #
#  Filename: Makefile                                      #
#                                                          #                                                   
#  This program was designed to demonstrate the use of     #  
#  IPC mechanisms to control the use of processes. This    # 
#  program utilizes pipes as the IPC mechanism to send     # 
#  messages between processes. Three processes are created # 
#  and controlled accordingly. One process counts down the # 
#  remaining time left for the program to run. Once it     # 
#  finishes it utilizes pipes to tell the other two        #   
#  processes to terminate their jobs. The second process   # 
#  displays the current time every second, and the third   # 
#  runs the uptime program every 5 seconds. The user       # 
#  is able to specify the amount of seconds the program    #  
#  will run. If no time is specified, the program will     #  
#  run for a default 10 seconds.                           #
#                                                          #
############################################################

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
# -g	adds debugging info to the executable file
CFLAGS = -g -lrt

# the build target executable:
TARGET = a3

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
