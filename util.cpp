#include <stdint.h>
#include <string.h>

#include "util.h"

void fill_with_spaces(char * s, uint8_t count)
{
	uint8_t len = 0;
	if (s)
	{
		len = strlen(s);
		while(len < count)
		{
			s[len++] = ' ';
		}
	}
}
