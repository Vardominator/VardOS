
#ifndef __VARDOS__HARDWARECOMMUNICATION__PORT_H
#define __VARDOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace vardos
{
    namespace hardwarecommunication
    {
        class Port
        {
            protected:
                Port(vardos::common::uint16_t portnumber);
                ~Port();
                vardos::common::uint16_t portnumber;
        };
        
        class Port8Bit : public Port
        {
            public:
                Port8Bit(vardos::common::uint16_t portnumber);
                ~Port8Bit();

                virtual vardos::common::uint8_t Read();
                virtual void Write(vardos::common::uint8_t data);

            protected:
                static inline vardos::common::uint8_t Read8(vardos::common::uint16_t _port)
                {
                    vardos::common::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(vardos::common::uint16_t _port, vardos::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };

        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(vardos::common::uint16_t portnumber);
                ~Port8BitSlow();

                virtual void Write(vardos::common::uint8_t data);
            protected:
                static inline void Write8Slow(vardos::common::uint16_t _port, vardos::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }

        };

        class Port16Bit : public Port
        {
            public:
                Port16Bit(vardos::common::uint16_t portnumber);
                ~Port16Bit();

                virtual vardos::common::uint16_t Read();
                virtual void Write(vardos::common::uint16_t data);

            protected:
                static inline vardos::common::uint16_t Read16(vardos::common::uint16_t _port)
                {
                    vardos::common::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(vardos::common::uint16_t _port, vardos::common::uint16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };

        class Port32Bit : public Port
        {
            public:
                Port32Bit(vardos::common::uint16_t portnumber);
                ~Port32Bit();

                virtual vardos::common::uint32_t Read();
                virtual void Write(vardos::common::uint32_t data);

            protected:
                static inline vardos::common::uint32_t Read32(vardos::common::uint16_t _port)
                {
                    vardos::common::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(vardos::common::uint16_t _port, vardos::common::uint32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };
    }
}

#endif
