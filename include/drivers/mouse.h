#ifndef __VARDOS__DRIVERS__MOUSE_H
#define __VARDOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace vardos
{
    namespace drivers
    {
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(vardos::common::uint8_t button);
            virtual void OnMouseUp(vardos::common::uint8_t button);
            virtual void OnMouseMove(vardos::common::int8_t x, vardos::common::int8_t y);
        };

        class MouseDriver : public vardos::hardwarecommunication::InterruptHandler, public Driver
        {
            vardos::hardwarecommunication::Port8Bit dataport;
            vardos::hardwarecommunication::Port8Bit commandport;
            vardos::common::uint8_t buffer[3];
            vardos::common::uint8_t offset;
            vardos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(vardos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual vardos::common::uint32_t HandleInterrupt(vardos::common::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif