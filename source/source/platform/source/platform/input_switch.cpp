#include "input_switch.h"
#include "../core/gba_core.h"

void InputSwitch::init()
{
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
        padInitializeDefault(&m_pad);
        }

        void InputSwitch::update()
        {
            padUpdate(&m_pad);
                u64 held = padGetButtons(&m_pad);

                    uint16_t keys = 0;
                        if (held & HidNpadButton_A)      keys |= GBA_KEY_A;
                            if (held & HidNpadButton_B)      keys |= GBA_KEY_B;
                                if (held & HidNpadButton_Minus)  keys |= GBA_KEY_SELECT;
                                    if (held & HidNpadButton_Plus)   keys |= GBA_KEY_START;
                                        if (held & HidNpadButton_AnyRight
                                             || held & HidNpadButton_StickLRight) keys |= GBA_KEY_RIGHT;
                                                 if (held & HidNpadButton_AnyLeft
                                                      || held & HidNpadButton_StickLLeft)  keys |= GBA_KEY_LEFT;
                                                          if (held & HidNpadButton_AnyUp
                                                               || held & HidNpadButton_StickLUp)    keys |= GBA_KEY_UP;
                                                                   if (held & HidNpadButton_AnyDown
                                                                        || held & HidNpadButton_StickLDown)  keys |= GBA_KEY_DOWN;
                                                                            if (held & HidNpadButton_R)      keys |= GBA_KEY_R;
                                                                                if (held & HidNpadButton_L)      keys |= GBA_KEY_L;

                                                                                    m_gbaKeys = keys;

                                                                                        m_exitRequested = (held & HidNpadButton_Plus) && (held & HidNpadButton_Minus);
                                                                                        }