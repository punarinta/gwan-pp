/*
	JsonView is used to output JSON or JSONP.
*/

#ifndef _JSON_VIEW_HPP_
#define _JSON_VIEW_HPP_ 1

#include "../JSON.hpp"
#include "GenericView.hpp"

class JsonView : public GenericView
{
protected:
	bool padding = false;

public:
	JSON *json;

	JsonView(char *argv[]) : GenericView(argv)
	{
		this->contentType = "application/json";
		this->json = new JSON;
	}

	JsonView(char *argv[], bool padding) : GenericView(argv)
	{
		this->contentType = "application/json";
		this->padding = padding;
		this->json = new JSON;
	}

	~JsonView()
	{
		delete this->json;
	}

	void echo(char *format, ...)	// block generic echo by creating a dummy
	{
	}

	void flush()
	{
		if (!this->headersSet)
		{
		    this->flushHeaders();
		}

		if (this->padding)
		{
		    xbuf_cat(this->httpOut, "_jqjsp(");
		}

		xbuf_cat(this->httpOut, this->json->stringify());

		if (this->padding)
		{
		    xbuf_cat(this->httpOut, ");");
		}

		GenericView::flush();
	}
};

#endif