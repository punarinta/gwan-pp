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
	TiXmlDocument *doc;
	TiXmlElement *xmlroot;

public:

	XmlView(char *argv[]) : GenericView(argv)
	{
		this->contentType = "application/xml";
		this->doc = new TiXmlDocument;

		TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "utf-8", "");
		this->doc->LinkEndChild(decl);

		// TODO: decide later if it is necessary/useful to posess an own XML or not
		this->xmlroot = new TiXmlElement("root");  
		this->doc->LinkEndChild(this->xmlroot);  
	}

	~XmlView()
	{
		delete this->doc;
	}

	void echo(char *format, ...)
	{
	}

	TiXmlElement* xml()	// make own XML-object read-only
	{
		return this->xmlroot;
	}

	void flush()
	{
		if(!this->headersSet) this->flushHeaders();

		TiXmlPrinter *printer = new TiXmlPrinter;
		printer->SetIndent("    ");
		this->doc->Accept(printer);
		xbuf_cat(this->httpOut, (char *) printer->CStr());
		GenericView::flush();
		delete printer;
	}
};

#endif