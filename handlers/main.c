/*
	Rewrite URL.
*/

#include "gwan.h"

int init(int argc, char *argv[])
{
	u32 *states = (u32*) get_env(argv, US_HANDLER_STATES);
	*states = (1L << HDL_AFTER_READ);
	
//	u8 *query_char = (u8*)get_env(argv, QUERY_CHAR);
//	*query_char = '!';
	
	u8 *lang = (u8*) get_env(argv, DEFAULT_LANG);
	*lang = LG_CPP;
	return 0;
}

void clean(int argc, char *argv[])
{
}

int main(int argc, char *argv[])
{
	long state = (long) argv[0];
	switch(state)
	{
		case HDL_AFTER_READ:
		{
			xbuf_t *read_xbuf = (xbuf_t*) get_env(argv, READ_XBUF);
			
//			printf("%s\n", read_xbuf->ptr);
			
			xbuf_replfrto(read_xbuf, read_xbuf->ptr, read_xbuf->ptr + 16, " /", " /?");
			xbuf_replfrto(read_xbuf, read_xbuf->ptr, read_xbuf->ptr + 16, ".api", ".cpp");
			xbuf_replfrto(read_xbuf, read_xbuf->ptr, read_xbuf->ptr + 16, ".cpp?", ".cpp&");
		}
		break;
	}
	return(255);
}

