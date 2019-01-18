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

//global vars
MysqlHandler mHandler;
ECDH eHandler;
Server server;
CurlHandler cHandler;

#endif
