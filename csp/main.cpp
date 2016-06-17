#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wpointer-arith"

#include <stdio.h>
#include <string>
#include "gwan.h"
#include "core/Application.hpp"
#include "core/MySQL.hpp"
#include "core/Bcrypt.hpp"
#include "core/View/JsonView.hpp"
#include "config/db.cfg"

#pragma link "mysqlclient"
#pragma include "/usr/include/mysql"

using namespace std;

void MyFunction(int argc, char *argv[])
{
	printf("\nExecuting 'MyFunction()'... %s\n", argv[0]);
}

JsonView *output;
Application *app;

int main(int argc, char *argv[])
{
	MYSQL_ROW *rows;

	app = new Application(argc, argv);
	output = new JsonView(argv);
	output->header("Server", "Hello, world (full of headers)!");

	app->router->bind("xxx", MyFunction);
	app->router->bind("yyy", []() -> void
	{
		printf("Lambda call. %s %d\n", app->argv(0), app->argc());
		output->json->add("l_msg", "you've called an anon function ;)");

		return;
	});
	app->run();

	output->json->addNode("subnode")->add("sampleInt", 10)->parent()->add("sampleText", "hi!");

	JSON *argvArr = output->json->addNode("argv");

	int i = 0;
	while (i < argc)
	{
		argvArr->add(argv[i], argv[i]);
		i++;
	}

	MySQL *sql = new MySQL(DB_HOST, DB_PORT, DB_USER, DB_PASSWORD, DB_DB);
	sql->query("SET NAMES utf8");

	if ((rows = sql->rows("SELECT txt FROM test_table LIMIT 2")))
	{
		JSON *arr = output->json->add(jsn_ARRAY, "arr", 0);

		for (int i = 0; i < sql->count; i++)
		{
		    arr->addElement(jsn_STRING, (long) rows[i][0]);
		}
	}

	Bcrypt *crypt = new Bcrypt();
	string hash = crypt->create("CorrectPassword", 12);

	output->json->addNode("bcrypt")->add("hash", (char *) hash.c_str())
	    ->parent()->add("isOk", crypt->verify("CorrectPassword", hash.c_str()))
	    ->parent()->add("isNotOk", crypt->verify("WrongPassword", hash.c_str()));

	output->flush();

	if (sql)
	{
	    //we need to close the connection
	    delete sql;
	}

	return 200;
}
