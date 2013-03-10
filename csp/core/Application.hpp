#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_ 1

#include "Router.hpp"

class Application
{
public:
	Router *router;

	Application(int argc, char *argv[])
	{
		this->router = new Router(argc, argv);
	}

	~Application()
	{
		delete this->router;
	}

	void run()
	{
		this->router->run();
	}

	int argc()
	{
		return this->router->getArgc();
	}

	char *argv(int i)
	{
		return this->router->getArgv(i);
	}
};

#endif