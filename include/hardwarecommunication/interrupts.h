
#ifndef __VARDOS__HARDWARECOMMUNICATION__INTERRUPTMANAGER_H
#define __VARDOS__HARDWARECOMMUNICATION__INTERRUPTMANAGER_H

#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/port.h>

namespace vardos
{
    namespace hardwarecommunication
    {
        class InterruptManager;

        class InterruptHandler
        {
        protected:
            vardos::common::uint8_t interrupt;
            InterruptManager* interruptManager;
            // should not be instantiated outside of the manager
            InterruptHandler(InterruptManager* interruptManager, vardos::common::uint8_t interrupt);
            ~InterruptHandler();
        public:
            virtual vardos::common::uint32_t HandleInterrupt(vardos::common::uint32_t esp);
        };

        class InterruptManager
        {
            // allow interrupt manager to instantiate InterruptHandler
            friend class InterruptHandler;

        protected:
            static InterruptManager* ActiveInterruptManager;
            InterruptHandler* handlers[256];

            struct GateDescriptor
            {
                vardos::common::uint16_t handlerAddressLowBits;
                vardos::common::uint16_t gdt_codeSegmentSelector;
                vardos::common::uint8_t reserved;
                vardos::common::uint8_t access;
                vardos::common::uint16_t handlerAddressHighBits;
            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                vardos::common::uint16_t size;
                vardos::common::uint32_t base;
            } __attribute__((packed));

            vardos::common::uint16_t hardwareInterruptOffset;
            static void SetInterruptDescriptorTableEntry(vardos::common::uint8_t interrupt,
                vardos::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),
                vardos::common::uint8_t DescriptorPrivilegeLevel, vardos::common::uint8_t DescriptorType);


            static void InterruptIgnore();

            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();

            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();

            static vardos::common::uint32_t HandleInterrupt(vardos::common::uint8_t interrupt, vardos::common::uint32_t esp);
            vardos::common::uint32_t DoHandleInterrupt(vardos::common::uint8_t interrupt, vardos::common::uint32_t esp);

            Port8BitSlow programmableInterruptControllerMasterCommandPort;
            Port8BitSlow programmableInterruptControllerMasterDataPort;
            Port8BitSlow programmableInterruptControllerSlaveCommandPort;
            Port8BitSlow programmableInterruptControllerSlaveDataPort;

        public:
            InterruptManager(vardos::common::uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable);
            ~InterruptManager();
            vardos::common::uint16_t HardwareInterruptOffset();
            void Activate();
            void Deactivate();
        };
    }
}

#endif