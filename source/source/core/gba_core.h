#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

constexpr int GBA_WIDTH  = 240;
constexpr int GBA_HEIGHT = 160;

enum GbaKey : uint16_t
{
    GBA_KEY_A      = 1 << 0,
        GBA_KEY_B      = 1 << 1,
            GBA_KEY_SELECT = 1 << 2,
                GBA_KEY_START  = 1 << 3,
                    GBA_KEY_RIGHT  = 1 << 4,
                        GBA_KEY_LEFT   = 1 << 5,
                            GBA_KEY_UP     = 1 << 6,
                                GBA_KEY_DOWN   = 1 << 7,
                                    GBA_KEY_R      = 1 << 8,
                                        GBA_KEY_L      = 1 << 9,
                                        };

                                        class GbaCore
                                        {
                                        public:
                                            bool loadRom(const std::string& path);
                                                void reset();
                                                    void setKeys(uint16_t keys);
                                                        void runFrame();

                                                            const uint16_t* getFramebuffer() const { return m_framebuffer.data(); }

                                                            private:
                                                                std::vector<uint8_t> m_rom;
                                                                    std::vector<uint16_t> m_framebuffer =
                                                                            std::vector<uint16_t>(GBA_WIDTH * GBA_HEIGHT, 0);
                                                                                uint16_t m_keys = 0;
                                                                                };