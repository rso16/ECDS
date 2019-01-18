#include "ECDH.h"
//made by R. S. Overhorst

uint64_t ECDH::getMAC(char *serverRequest)
{
	std::string mac(serverRequest);
	mac = mac.substr(0, 17);
	printf("mac = %s\n", mac.c_str());
	uint64_t macInt = string_to_mac(mac);
	printf("macInt = %"PRIu64"\n", macInt); 
	return macInt;
}

int ECDH::getRoomId(uint64_t MAC)
{
	MysqlHandler mHandler;
	char *sqlStm = (char*) malloc(sizeof(char) * SQL_SIZE); 	
	sprintf(sqlStm, "%s'%"PRIu64"'", SQL_STM, MAC);
	printf("executing the following sql statement : %s\n", sqlStm);	
	mHandler.connect(SERVER,USER,PASSWORD,DATABASE);
	MYSQL_RES res = mHandler.executeSQL(sqlStm);
	MYSQL_ROW row = mysql_fetch_row(&res);
	mHandler.close();		
	
	if(row == NULL)
	{
		return NULL;
	}
	else
	{
		return atoi(row[0]);	
	}
}



uint64_t ECDH::string_to_mac(std::string const& s)
{
    unsigned char a[6];
    int last = -1;
    int rc = sscanf(s.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%n",
                    a + 0, a + 1, a + 2, a + 3, a + 4, a + 5,
                    &last);
    return
        uint64_t(a[0]) << 40 |
        uint64_t(a[1]) << 32 |
        uint64_t(a[2]) << 24 |
        uint64_t(a[3]) << 16 |
        uint64_t(a[4]) << 8 |
        uint64_t(a[5]);
}


