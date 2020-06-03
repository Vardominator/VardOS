#ifndef __VARDOS__DRIVERS__DRIVER_H
#define __VARDOS__DRIVERS__DRIVER_H

namespace vardos
{
    namespace drivers
    {
        class Driver
        {
        public:
            Driver();
            ~Driver();

            virtual void Activate();
            virtual int Reset();        // resetting the hardware state upon boot
            virtual void Deactivate();
        };

        class DriverManager
        {
        private:
            // prior to dynamic memory management
            Driver* drivers[255];
            int numDrivers;

        public:
            DriverManager();
            void AddDriver(Driver* drv);
            void ActivateAll();
        };
    }
}

#endif