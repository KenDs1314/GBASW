#pragma once
#include <switch.h>
#include <cstdint>

class VideoSwitch
{
public:
    void init();
        void presentFrame(const uint16_t* gbaFramebufferRGB565);
            void exit();

            private:
                NWindow* m_win = nullptr;
                    Framebuffer m_fb{};
                    };