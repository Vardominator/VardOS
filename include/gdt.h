#ifndef __VARDOS__GDT_H
#define __VARDOS__GDT_H

#include <common/types.h>

namespace vardos
{
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    vardos::common::uint16_t limit_lo;
                    vardos::common::uint16_t base_lo;
                    vardos::common::uint8_t base_hi;
                    vardos::common::uint8_t type;
                    vardos::common::uint8_t limit_hi;
                    vardos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(vardos::common::uint32_t base, vardos::common::uint32_t limit, vardos::common::uint8_t type);
                    vardos::common::uint32_t Base();
                    vardos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            vardos::common::uint16_t CodeSegmentSelector();
            vardos::common::uint16_t DataSegmentSelector();
    };
}

#endif