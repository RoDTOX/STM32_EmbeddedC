/******************************************************************************

                      -----
    1. There is a income data read of 32bits
    2. Those bits needs to be allocated in a predefined structure Packet
    3. Structure content needs to be printed out

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>

struct Packet //32bit - 4byte
{
    uint8_t crc : 2;        //2bits
    uint8_t status : 1;     //1bit
    uint16_t payload : 12;    //12bits
    uint8_t bat : 3;        //3bits
    uint8_t sensor : 3;     //3bits
    uint8_t longAddr : 8;   //8bits
    uint8_t shortAddr : 2;  //2bits
    uint8_t addrMode : 1;   //1bit
};

int main(void)
{
    uint32_t u32_packet = 0;

    struct Packet st_Packet = {0};
    
    char *ptr = (char*)&st_Packet;
    
    printf("size of packet is: %dbytes\n", sizeof(st_Packet));

    printf("Provide 32bit(4bytes) of data packet:");
    scanf("%d",&u32_packet);

    printf("\nNo, packaetu desfacut, fiecare impartit astfel:\n");
    for (int i=0; i<sizeof(ptr);i++)
    {
        printf("... = %d\n", (*ptr+i));
    }
    return 0;
}