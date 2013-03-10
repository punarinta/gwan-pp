#ifndef _HTML_VIEW_HPP_
#define _HTML_VIEW_HPP_ 1

#include "GenericView.hpp"

class HtmlView : public GenericView
{
public:
	HtmlView(char *argv[]) : GenericView(argv)
	{
		this->contentType = "text/html";
		// TODO: add UTF-8 encoding
	}
};

#endif