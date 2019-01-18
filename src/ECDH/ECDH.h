//made by R. S. Overhorst
//ECDH = E-Classroom Display Handler

#ifndef ECDH_H
#define ECDH_H

//includes
#include "../MysqlHandler/MysqlHandler.h"
#include <iostream>
#include <string>
#include <inttypes.h>

//defines
#define BEGIN_OF_MAC 0
#define MAC_SIZE 17
#define SQL_SIZE 53
#define SQL_STM "select RID from Boards where MAC = "
#define __STDC_FORMAT_MACROS

//Defines 
#define PI_BOX 0
#define U_BOX 1
#define BOX U_BOX

#if BOX == PI_BOX 
	#define SERVER "localhost"
	#define USER "Epaper"
	#define PASSWORD "Display"
	#define DATABASE "windesheim"
#elif BOX == U_BOX
	#define SERVER "localhost"
	#define USER "root"
	#define PASSWORD ""
	#define DATABASE "windesheim"
#endif

class ECDH
{
	private:
	public:
		uint64_t getMAC(char *serverRequest);
		int getRoomId(uint64_t MAC);
		
		//source = https://stackoverflow.com/questions/7326123/convert-mac-address-stdstring-into-uint64-t
		uint64_t string_to_mac(std::string const& s);
		
};

#endif
