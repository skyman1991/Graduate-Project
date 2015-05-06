#include "common.h"

uint8 PackTypeJudge(uint8 *type)
{
		type++;
		return (*type&0xFC)>>2;
}
