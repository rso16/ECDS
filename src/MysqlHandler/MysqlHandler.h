#ifndef MYSQLHANDLER_H
#define MYSQLHANDLER_H

//includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mysql.h> 



class MysqlHandler
{
	private:
		MYSQL *connection;			

	public:
		int connect(char *server, char *user, char *pass, char *db_name);
		MYSQL_RES executeSQL(char* sql);
		int printMysqlRes(MYSQL_RES *res_set);
		int close();
}; 

#endif	
