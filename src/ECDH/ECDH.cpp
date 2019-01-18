#include "ECDH.h"
//made by R. S. Overhorst

char* ECDH::getMAC(char *serverRequest)
{
	nodeList *serverReq = (nodeList*) malloc(sizeof(nodeList));
	char *macAddr = (char*) malloc(sizeof(char) * MAC_SIZE);
	addStrToList(serverReq, serverRequest);
	int err = listToStr(serverReq, macAddr, BEGIN_OF_MAC, MAC_SIZE);
	printf("printing list : ");
	printStrList(serverReq);	
	printf("\nmacAddr = %s\n", macAddr);
	
	char *macAddrInt = (char*) malloc(sizeof(char) * 500);
	std::string macStr = macAddr;
	uint64_t temp = string_to_mac(macStr); 
	sprintf(macAddrInt, "%" PRIu64 , temp);
	printf("%s\n", macAddrInt);
	return macAddrInt; 
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



uint64_t ECDH::string_to_mac(std::string const& s)
{
    unsigned char a[6];
    int last = -1;
    int rc = sscanf(s.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%n",
                    a + 0, a + 1, a + 2, a + 3, a + 4, a + 5,
                    &last);
    if(rc != 6 || s.size() != last)
        throw std::runtime_error("invalid mac address format " + s);
    return
        uint64_t(a[0]) << 40 |
        uint64_t(a[1]) << 32 |
        uint64_t(a[2]) << 24 |
        uint64_t(a[3]) << 16 |
        uint64_t(a[4]) << 8 |
        uint64_t(a[5]);
}


