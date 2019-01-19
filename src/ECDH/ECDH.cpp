#include "ECDH.h"
//made by R. S. Overhorst

/**
* @brief This Function gets the MAC-address from the server request and changes it to an int (the way the MAC-address is stored in the db).
* @returns The MAC-address in database form.
* @author Rick Overhorst
*/
uint64_t ECDH::getMAC(char *serverRequest)
{
	//Gets the MAC-address part of the server request.
	std::string mac(serverRequest);
	mac = mac.substr(0, 17);
	printf("mac = %s\n", mac.c_str());
	//turns the MAC-Address into int
	uint64_t macInt = string_to_mac(mac);
	printf("macInt = %"PRIu64"\n", macInt); 
	return macInt;
}

/**
* @brief Gets the room id from the db.
* @returns The room Id.
* @author Rick Overhorst
*/
int ECDH::getRoomId(uint64_t MAC)
{
	//by using the mysql lib a room id is retrieved.
	MysqlHandler mHandler;
	char *sqlStm = (char*) malloc(sizeof(char) * SQL_SIZE); 	
	sprintf(sqlStm, "%s'%"PRIu64"'", SQL_STM, MAC);//combining the standard SQL query with the mac address
	printf("executing the following sql statement : %s\n", sqlStm);	
	mHandler.connect(SERVER,USER,PASSWORD,DATABASE);
	MYSQL_RES res = mHandler.executeSQL(sqlStm);
	MYSQL_ROW row = mysql_fetch_row(&res);
	mHandler.close();		
	//check if the query returned a value	
	if(row == NULL)
	{
		return NULL;
	}
	else
	{
		return atoi(row[0]);	
	}
}

/**
* @brief This Function turns the MAC-address into an int (the way the MAC-address is stored in the db).
* @returns The MAC-address in database form.
* @author Maxim Egorushkin
*/
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
