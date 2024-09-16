/******************************************************************************

                      -----
    1. There is a income data read of 32bits
    2. Those bits needs to be allocated in a predefined structure Packet
    3. Structure content needs to be printed out

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct Packet //32bit - 4byte
{
    //Using bitfields structure, we fill all the memory space and avoid padding,thus improving memory.
    //Ideally is to use the same datatype in the structure for this to be optimized
    //Order in the structure does not influence structure size, because they use the same amount of bits, there is no padding in this case.
    //Modifying the order influences the memory addressing, and not recommended.
    uint32_t crc        : 2;
    uint32_t status     : 1;
    uint32_t payload    : 12;
    uint32_t bat        : 3;
    uint32_t sensor     : 3;
    uint32_t longAddr   : 8;
    uint32_t shortAddr  : 2;
    uint32_t addrMode   : 1;
    
};

int main(void)
{
    //Var init
    uint32_t u32_packet = 0;
    struct Packet st_Packet = {0};
        
    //Get input from user (4bytes - uint32)
    printf("Provide 32bits(%ubytes) of data packet:", sizeof(struct Packet));
    scanf("%x",&u32_packet);
    //printf("u32_packet = %x\n",u32_packet); //debug, ok

    //Unpack u32_packet raw input per structure
    st_Packet.crc       = u32_packet     & 0b0011;      //2bits
    st_Packet.status    = u32_packet >>2 & 0b0001;      //1bit
    st_Packet.payload   = u32_packet >>3 & 0x0FFF;      //12bits -> 0xFFF or 0b111111111111
    st_Packet.bat       = u32_packet >>15& 0b0111;      //3bits
    st_Packet.sensor    = u32_packet >>18& 0b0111;      //3bits
    st_Packet.longAddr  = u32_packet >>21& 0x00FF;      //8bits -> 0xFF
    st_Packet.shortAddr = u32_packet >>29& 0b0011;      //2bits
    st_Packet.addrMode  = u32_packet >>31& 0b0001;      //1bit

    printf("st_Packet.crc = %#x\n",st_Packet.crc);
    printf("st_Packet.status = %#x\n",st_Packet.status);
    printf("st_Packet.payload = %#x\n",st_Packet.payload);
    printf("st_Packet.bat = %#x\n",st_Packet.bat);
    printf("st_Packet.sensor = %#x\n",st_Packet.sensor);
    printf("st_Packet.longAddr = %#x\n",st_Packet.longAddr);
    printf("st_Packet.shortAddr = %#x\n",st_Packet.shortAddr);
    printf("st_Packet.addrMode = %#x\n",st_Packet.addrMode);

    return 0;
    //Struct pointer init for printing contents
    char *ptr = (char*)&st_Packet;

    printf("\nNo, packaetu desfacut, fiecare impartit astfel:\n");
    for (int i=0; i<sizeof(ptr);i++)
    {
        printf("... = %d\n", (*ptr+i));
    }
    return 0;
}