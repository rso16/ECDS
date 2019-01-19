/** @file */ 
/*!
*@mainpage E-Classroom Display server
*@author Rick Ovehorst, Gerjon Eilander & Gerben van 't Ooster
*@version 1.0
*@section intro_sec Introduction
*
*This server program sends schedule data from the Windesheim's systems to the modules upon request.
*
*@section compile_sec Compilation
*@subsection install neccesary packages
*The packages that are neccesary, can be optained by using folowing commands :
* - list item 2 
* files neccesary for compiling
* - sudo apt-get install gcc
* - sudo apt-get install make
*/


#ifndef CBACKEND_MAIN_H
#define CBACKEND_MAIN_H

#include <stdio.h>
#include "Server/Server.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "MysqlHandler/MysqlHandler.h"
#include "ECDH/ECDH.h"
#include "CurlHandler/CurlHandler.h"

#if defined(_WIN32)
	#include <winsock2.h>
#elif defined(__linux__)
	#include <netdb.h>
	#include <sys/types.h>
	#include <sys/socket.h>
#endif

//functions
int main(int argc, const char* argv[]) 



//global vars
MysqlHandler mHandler;
ECDH eHandler;
Server server;
CurlHandler cHandler;

#endif
