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
	MYSQL_RES *result = NULL;

public:
    long count = 0;

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

			this->result = NULL;
		}
		else
		{
		    if (this->result)
		    {
		        delete this->result;
		    }

		    this->result = mysql_store_result(this->connection);
		}

		return this->result;
	}

	MYSQL_ROW row(char *sql_query)
	{
	    if (this->query(sql_query))
	    {
	        return mysql_fetch_row(this->result);
	    }
	    else
	    {
	        return NULL;
	    }
	}

	MYSQL_ROW* rows(char *sql_query)
	{
	    MYSQL_ROW* rows = NULL;

		if (this->query(sql_query))
    	{
    	    long i = 0;
    	    MYSQL_ROW row;

    	    this->count = mysql_num_rows(this->result);
    	    rows = new MYSQL_ROW[count];

    		while ((row = mysql_fetch_row(this->result)) != NULL)
    		{
    			rows[i++] = row;
    		}

    		mysql_free_result(this->result);
    	}

    	return rows;
	}
};

#endif
