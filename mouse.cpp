#include "mouse.h"
    
MouseDriver::MouseDriver(InterruptManager* manager)
: InterruptHandler(0x2C, manager),
dataport(0x60),
commandport(0x64)
{
    // initialize cursor; start with center of the screen
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    offset = 0;
    buttons = 0;
    x = 40;
    y = 12;
 
    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xF000) >> 4 | (VideoMemory[80*y+x] & 0x0F00) << 4 | (VideoMemory[80*y+x] & 0x00FF);

    // activate mouse interrupts
    commandport.Write(0xAB);
    // get current state
    commandport.Write(0x20);
    // set rightmost bit to one and clear the 5th bit
    uint8_t status = dataport.Read() | 2;
    // set state
    commandport.Write(0x60);
    // and write it back
    dataport.Write(status);
    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}

MouseDriver::~MouseDriver()
{
}

void printf(char*);

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();
    if(!(status & 0x20))
    {
        return esp;
    }

    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;

    // highlight pixel containing mouse position
    if(offset == 0)
    {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;

        // switch old cursor back
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xF000) >> 4 | (VideoMemory[80*y+x] & 0x0F00) << 4 | (VideoMemory[80*y+x] & 0x00FF);

        x += buffer[1];
        y -= buffer[2];

        // switch background and foreground colors of new cursor
        VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4) | ((VideoMemory[80*y+x] & 0x0F00) << 4) | ((VideoMemory[80*y+x] & 0x00FF));
    
        // capture button clicks, but only change the buffer if the new state is different from the previous one
        for(uint8_t i = 0; i < 3; i++)
        {
            if((buffer[0] & (0x01 << i)) != (buttons & (0x01 << i)))
            {
                // switch background and foreground colors of new cursor
                VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4) | ((VideoMemory[80*y+x] & 0x0F00) << 4) | ((VideoMemory[80*y+x] & 0x00FF));
            }
        }
        buttons = buffer[0];
    }

    return esp;
}