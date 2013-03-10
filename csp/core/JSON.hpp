#ifndef _JSON_HPP_
#define _JSON_HPP_ 1

#include <cstring>
#include "gwan.h"

// JSN_TYPE { jsn_FALSE = 0, jsn_TRUE, jsn_NULL, jsn_INTEGER, jsn_REAL, jsn_STRING, jsn_NODE, jsn_ARRAY }

class JSON
{
protected:
	jsn_t *obj;
	JSON *pParent;

public:
	JSON()
	{
		this->obj = jsn_add(0, "root", jsn_NODE, 0);
	}

	JSON(JSON *pParent, JSN_TYPE type, char *key, double value)
	{
		this->obj = jsn_add(pParent->obj, key, type, value);
		this->pParent = pParent;
	}

	~JSON()
	{
		if(this->obj) jsn_free(this->obj);
	}

	JSON *add(JSN_TYPE type, char *key, double value)		// Generic add()
	{
		return new JSON(this, type, key, value);
	}

	JSON *add(char *key, char *value)
	{
		return new JSON(this, jsn_STRING, key, (long) value);
	}

	JSON *add(char *key, int value)
	{
		return new JSON(this, jsn_INTEGER, key, value);
	}

	JSON *addElement(JSN_TYPE type, long element)
	{
		return new JSON(this, type, "", element);
	}

	JSON *addNode(char *key)
	{
		return this->add(jsn_NODE, key, 0);
	}

	JSON *parent()
	{
		return this->pParent;
	}

	char *stringify()
	{
		xbuf_t xbuf;
		xbuf_init(&xbuf);
		return jsn_totext(&xbuf, this->obj, 0);		//	0 - compressed, 1 - with tabs etc
	}
};

#endif