#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_ 1

#include "Util.hpp"
#include "Session.hpp"
#include "Router.hpp"
#include "gwan.h"
#include <string>

static char *szHTTP_Method[] =
{
    [HTTP_ANY]        = "?",
    [HTTP_GET]        = "GET",
    [HTTP_HEAD]       = "HEAD",
    [HTTP_POST]       = "POST",
    [HTTP_PUT]        = "PUT",
    [HTTP_DELETE]     = "DELETE",
    [HTTP_OPTIONS]    = "OPTIONS"
};

class Application
{
private:
    char **argv_root;

public:
	Router *router;
	Session *session;

	Application(int argc, char *argv[])
	{
		this->router = new Router(argc, argv);
		this->argv_root = argv;

        http_t *http = (http_t*)get_env(argv, HTTP_HEADERS);
        char *request  = (char*)get_env(argv, REQUEST);
        u32   method   = (u32)  get_env(argv, REQUEST_METHOD);
        const char *req_ptr = request - strlen(szHTTP_Method[method]);
        const char *h_cookies = (http->h_cookies ? req_ptr + http->h_cookies : "-") - 1;

        this->session = new Session(get_cookie((char *)h_cookies, "__session_id"));
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

	char **argvs()
	{
		return this->argv_root;
	}
};

#endif