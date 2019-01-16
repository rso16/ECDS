// Include Header Files
#include "MysqlHandler.h"


int MysqlHandler::connect(char *server, char *user, char *pass, char *db_name)
{
	connection = mysql_init(NULL);

	if (!connection)
	{
	printf("Mysql Initialization Failed");
	return 1;
	}

	connection = mysql_real_connect(connection, server, user, pass, db_name, 0,NULL,0);

	if (connection)
	{
		printf("Connection Succeeded\n");
		return 1;
	}
	else
	{
		printf("Connection Failed\n");
		return -1;
	}
}

MYSQL_RES MysqlHandler::executeSQL(char* sql)
{
	MYSQL_RES *res_set;

	// Replace MySQL query with your query

	mysql_query (connection, sql);
	res_set=mysql_store_result(connection);
	if(res_set == NULL)
	{
		printf("error\n");
	}

	return *res_set;
}

int MysqlHandler::printMysqlRes(MYSQL_RES *res_set)
{
	unsigned int numrows = mysql_num_rows(res_set);
	MYSQL_ROW row;
	int numOfFields = mysql_num_fields(res_set);
	while (((row=mysql_fetch_row(res_set)) !=NULL))
	{
		for(int i = 0; i < numOfFields; i++)
		{
			printf("%s, ", row[i]);	
		}
		printf("\n");
	}
	return 1;
}

int MysqlHandler::close()
{
	mysql_close(connection);
	return 1;
}
