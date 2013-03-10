#ifndef _XML_VIEW_HPP_
#define _XML_VIEW_HPP_ 1

#include "GenericView.hpp"

class XmlView : public GenericView
{

public:

	XmlView(char *argv[]) : GenericView(argv)
	{
		this->contentType = "application/xml";
	}

	void echo(char *format, ...)	// block generic echo by creating a dummy
	{
	}

	void flush()
	{
		if(!this->headersSet) this->flushHeaders();

		GenericView::flush();
	}
};

#endif