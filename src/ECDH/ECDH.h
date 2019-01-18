//made by R. S. Overhorst
//ECDH = E-Classroom Display Handler

#ifndef ECDH_H
#define ECDH_H

//includes
#include "../node/node.h"
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

class ECDH
{
	private:
	public:
		uint64_t getMAC(char *serverRequest);
		char* getRoomId(uint64_t MAC);
		
		//source = https://stackoverflow.com/questions/7326123/convert-mac-address-stdstring-into-uint64-t
		uint64_t string_to_mac(std::string const& s);
		
};

#endif
