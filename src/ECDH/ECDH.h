//made by R. S. Overhorst
//ECDH = E-Classroom Display Handler

#ifndef ECDH_H
#define ECDH_H

//includes
#include "../node/node.h"
#include "../MysqlHandler/MysqlHandler.h"

//defines
#define BEGIN_OF_MAC 0
#define MAC_SIZE 17
#define SQL_SIZE 53
#define SQL_STM "select RID from boards where MAC = "


class ECDH
{
	private:

	public:
		char* getMAC(char *serverRequest);
		char* getRoomId(char *MAC);
		
};

#endif
