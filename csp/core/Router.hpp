#ifndef _ROUTER_HPP_
#define _ROUTER_HPP_ 1

#include <vector>
#include <string.h>

struct atom_route
{
    char *name;
    void (*func)(int, char**);
};

class Router
{
private:
	bool runDone = false;

protected:
	std::vector<struct atom_route> routes;
	char **argv;
	int argc;

public:
	Router(int argc, char **argv)
	{
		this->argv = argv;	// just copy the POINTER
		this->argc = argc;
	}

	int getArgc()
	{
		return this->argc;
	}

	char *getArgv(int i)
	{
		if(i>=this->argc) return NULL;
		return this->argv[i];
	}

	int run()
	{
		if(this->runDone) return 0;
		else
		{
			int i = this->argc, called = 0;
			this->runDone = true;
			while(i--)
			{
				// TODO: if no '=' in argument then it's a function
				if(this->call(this->argv[i])) called++;
			}
			return called;
		}
	}

	bool bind(char *name, void (*func)(int, char**))
	{
		struct atom_route ar;
		ar.name = strdup(name);
		ar.func = func;
		this->routes.push_back(ar);
		return true;
	}

	bool bind(char *name, void (*func)())	// add argumentless function
	{
		struct atom_route ar;
		ar.name = strdup(name);
		ar.func = (void (*)(int, char**))func;
		this->routes.push_back(ar);
		return true;
	}

	bool call(char *name)
	{
		for(int i=this->routes.size();i--;)
		{
			if(!strcmp(this->routes[i].name, name))
			{
				this->routes[i].func(this->argc, this->argv);
				return true;
			}
		}
		return false;
	}
};

#endif