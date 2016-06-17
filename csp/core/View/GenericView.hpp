#ifndef _GENERIC_VIEW_HPP_
#define _GENERIC_VIEW_HPP_ 1

#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "gwan.h"

class GenericView
{
protected:
	unsigned int headersSize;
	unsigned int ptrHeaderSize;
	std::string payload;
	std::string headers;
	std::string contentType;
	bool headersSet = false;

	static inline void u32toa(char *p, u32 v)
	{
		do *p-- = '0' + (v % 10), v /= 10; while(v);
	}

public:

	xbuf_t* httpOut;

	GenericView(char *argv[])
	{
		std::string contentType = "text/plain";
		this->httpOut = get_reply(argv);
	}

	void echo(char *format, ...)
	{
		va_list args;
		char *buffer = new char[256];

		va_start(args, format);
		vsprintf(buffer, format, args);
		this->payload += buffer;
		va_end(args);
		delete buffer;
	}

	bool header(std::string name, std::string value)
	{
		if (this->headersSet)
		{
		    return false;
		}

		this->headers += name + ": " + value + "\r\n";

		return true;
	}

	void flushHeaders(void)
	{
		this->ptrHeaderSize = 0;
		xbuf_xcat
		(
			this->httpOut,
			"HTTP/1.1 200 OK\r\n"
			"%s"
			"Content-type: %s\r\n"
			"Content-Length:      %n\r\n" 
			"Connection: close\r\n\r\n",
			(char *) this->headers.c_str(),
			(char *) this->contentType.c_str(),
			&ptrHeaderSize
		);

		this->headersSet = true;
		this->headersSize = this->httpOut->len;
	}

	void flush(void)
	{
		// TODO: flush() can later return some info about the flushed data, e.g. size
		if (!this->headersSet)
		{
		    this->flushHeaders();
		}
		xbuf_cat(this->httpOut, (char *) this->payload.c_str());
		u32toa(this->httpOut->ptr + this->ptrHeaderSize, this->httpOut->len - this->headersSize);		
	}
};

#endif