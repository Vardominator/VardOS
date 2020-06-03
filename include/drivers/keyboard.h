#ifndef __VARDOS__DRIVERS__KEYBOARD_H
#define __VARDOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace vardos
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
        public: 
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };

        class KeyboardDriver : public vardos::hardwarecommunication::InterruptHandler, public Driver
        {
            vardos::hardwarecommunication::Port8Bit dataport;
            vardos::hardwarecommunication::Port8Bit commandport;
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(vardos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler* handler);
            ~KeyboardDriver();
            virtual vardos::common::uint32_t HandleInterrupt(vardos::common::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif