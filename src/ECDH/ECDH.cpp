#include "ECDH.h"
//made by R. S. Overhorst

char* ECDH::getMAC(char *serverRequest)
{
	nodeList *serverReq = (nodeList*) malloc(sizeof(nodeList));
	char *macAddr = (char*) malloc(sizeof(char) * MAC_SIZE);
	addStrToList(serverReq, serverRequest);
	int err = listToStr(serverReq, macAddr, BEGIN_OF_MAC, MAC_SIZE);
	return macAddr;	
}

char* ECDH::getRoomId(char *MAC)
{
	MysqlHandler mHandler;
	char *sqlStm = (char*) malloc(sizeof(char) * SQL_SIZE); 	
	sprintf(sqlStm, "%s'%s'", SQL_STM, MAC);
	printf("executing the following sql statement : %s\n", sqlStm);	
	mHandler.connect(SERVER,USER,PASSWORD,DATABASE);
	MYSQL_RES res = mHandler.executeSQL(sqlStm);
	//mHandler.printMysqlRes(&res);	
	MYSQL_ROW row = mysql_fetch_row(&res);
	mHandler.close();		
	return row[0];	
}
		
