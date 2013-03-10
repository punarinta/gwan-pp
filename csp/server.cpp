#include <stdio.h>
#include <stdlib.h>
#include "core/Router.hpp"
#include "core/View/HtmlView.hpp"

HtmlView *output;
Router *router;

void stop_server()
{
	output->echo("Stopping the server...");
	output->flush();
	printf("\n\nServer stopped.\n\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	output = new HtmlView(argv);
	router = new Router(argc, argv);
	router->bind("stop", stop_server);

	if(!router->run()) output->echo("No method specified.");

	output->flush();
	return 200;
}