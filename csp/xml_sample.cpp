#pragma GCC diagnostic ignored "-Wwrite-strings"

#include <stdio.h>
#include "gwan.h"
#include "core/Application.hpp"
#include "core/View/XmlView.hpp"

XmlView *output;
Application *app;

int main(int argc, char *argv[])
{
	app = new Application(argc, argv);
	output = new XmlView(argv);

	

	output->flush();
	return 200;
}