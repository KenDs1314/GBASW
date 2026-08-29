#pragma once
#include <switch.h>
#include <cstdint>

class InputSwitch
{
public:
    void init();
        void update();
            uint16_t getGbaKeys() const { return m_gbaKeys; }
                bool exitRequested() const { return m_exitRequested; }

                private:
                    PadState m_pad{};
                        uint16_t m_gbaKeys = 0;
                            bool m_exitRequested = false;
                            };