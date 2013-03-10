#pragma GCC diagnostic ignored "-Wwrite-strings"

#include <stdio.h>
#include <string>
#include "gwan.h"
#include "core/Application.hpp"
#include "core/MySQL.hpp"
#include "core/View/JsonView.hpp"

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
	MYSQL_ROW row;

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

	output->json->addNode("subnode")->add("sample_int", 10)->parent()->add("sample_text", "hi!");

	JSON *argvArr = output->json->addNode("argv");

	int i = 0;
	while(i < argc)
	{
		argvArr->add(argv[i], argv[i]);
		i++;
	}

	MySQL *sql = new MySQL("localhost", 0, "root", "root", "test_db");
	sql->query("SET NAMES utf8");

	MYSQL_RES *res = sql->query("SELECT txt FROM test_table LIMIT 2");

	if(res)
	{
		JSON *arr = output->json->add(jsn_ARRAY, "arr", 0);
		while ((row = mysql_fetch_row(res))!=NULL)
		{
			//output->echo("%s<br>", row[0]);
			arr->addElement(jsn_STRING, (long) row[0]);
		}
		mysql_free_result(res);
	}

	output->flush();

	if(sql) delete sql;		//	we need to close the connecion
	return 200;
}
