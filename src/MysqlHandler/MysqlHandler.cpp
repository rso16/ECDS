// Include Header Files
#include "MysqlHandler.h"

/**
* @brief connects to the db-server.
* @returns 1 if succesfull, -1 if the initialization failed & -2 if connection failed.
* @author Rick Overhorst
*/
int MysqlHandler::connect(char *server, char *user, char *pass, char *db_name)
{
	connection = mysql_init(NULL);

	if (!connection)
	{
		printf("Mysql Initialization Failed");
		return -1;
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
		return -2;
	}
}

/**
* @brief Executes the SQL query.
* @returns The Results of the query.
* @author Rick Overhorst
*/
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

/**
* @brief Prints the result of the query
* @returns 1
* @warning Error checking not yet added!
* @author Rick Overhorst
*/
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

/**
* @brief closes the connection with the db-server
* @returns 1
* @warning Error checking not yet added!
* @author Rick Overhorst
*/
int MysqlHandler::close()
{
	mysql_close(connection);
	return 1;
}
