/*
	A simple servlet. No Application entity needed, Router is enough.
	TODO: authorization.
*/

#include <stdio.h>
#include <stdlib.h>
#include "core/Router.hpp"
#include "core/View/HtmlView.hpp"

HtmlView *output;
Router *router;

int main(int argc, char *argv[])
{
	output = new HtmlView(argv);
	router = new Router(argc, argv);
	router->bind("stop", []() -> void
	{
		// 'output' is useless here as you stop the server before xbuffer is flushed
		printf("\nServer stopped.\n");
		exit(0);
	});

	if(!router->run()) output->echo("No valid method specified.");

	output->flush();
	return 200;
}