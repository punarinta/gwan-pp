/*
	http://blog.trilabs.co.tz/2011/09/connect-to-mysql-using-c-on-ubuntu.html

	Requires package 'libmysqlclient-dev'

	Requires pragma:
	#pragma link "mysqlclient"
	#pragma include "/usr/include/mysql"
*/

#ifndef _MYSQL_HPP_
#define _MYSQL_HPP_ 1

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

class MySQL
{
private:
	MYSQL *connection;

public:
	MySQL(const char *server, unsigned int port, const char *user, const char *password, const char *database)
	{
		this->connection = mysql_init(NULL);
		if (!mysql_real_connect(this->connection, server, user, password, database, port, NULL, 0))
		{
			printf("DB error: %s\n", mysql_error(this->connection));
		}
	}

	~MySQL()
	{
		mysql_close(this->connection);
	}

	MYSQL_RES* query(char *sql_query)
	{
		if (mysql_query(this->connection, sql_query))
		{
			printf("DB error: %s\n", mysql_error(this->connection));
			return NULL;
		}
		else return mysql_use_result(this->connection);
	}
};

#endif
