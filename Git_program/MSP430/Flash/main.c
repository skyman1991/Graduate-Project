#include "common.h"

uint8 normal_test[MAX_PACK_LENGTH];
uint8 test_rssi = 0;
uint16 address = 0;
#define    PHY_ADDRESS_WRITE          0x0006
int main(void)
{	    
    __disable_interrupt();
    halBoardInit();    
    FLASH_Erase((uint16 *)PHY_ADDRESS_SEGMENT);
    FLASH_Writew((uint16 *)PHY_ADDRESS_SEGMENT,PHY_ADDRESS_WRITE);
    address = GetPhyAddress();

    if(address == PHY_ADDRESS_WRITE)
    {
        halLedSet(1);
    }
    for(;;)
    {
        
    }
    
}
