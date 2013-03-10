/*
	Requires package 'libtinyxml-dev'

	Requires pragma:
	#pragma link "tinyxml"
*/

#ifndef _XML_VIEW_HPP_
#define _XML_VIEW_HPP_ 1

#include <string>
#include <stdio.h>
#include <tinyxml.h>
#include "GenericView.hpp"

class XmlView : public GenericView
{
private:
	TiXmlDocument doc;
	TiXmlElement *xml;

public:

	XmlView(char *argv[]) : GenericView(argv)
	{
		this->contentType = "application/xml";
	}

	void echo(char *format, ...)	// block generic echo by creating a dummy
	{
		TiXmlDeclaration *decl = new TiXmlDeclaration( "1.0", "utf-8", "");
		this->doc.LinkEndChild(decl);

		this->xml = new TiXmlElement("MyApp");  
		this->xml->SetAttribute("value","5");
		this->xml->SetAttribute("name","me");
		this->doc.LinkEndChild(this->xml);  
	}

	void flush()
	{
		if(!this->headersSet) this->flushHeaders();

		TiXmlPrinter printer;
		printer.SetIndent("    ");
		this->doc.Accept(&printer);
		xbuf_cat(this->httpOut, (char *) printer.CStr());
		GenericView::flush();
	}
};

#endif