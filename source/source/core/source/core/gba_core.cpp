#include "gba_core.h"
#include <cstdio>

bool GbaCore::loadRom(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "rb");
        if (!f)
                return false;

                    fseek(f, 0, SEEK_END);
                        long size = ftell(f);
                            fseek(f, 0, SEEK_SET);

                                if (size <= 0)
                                    {
                                            fclose(f);
                                                    return false;
                                                        }

                                                            m_rom.resize(static_cast<size_t>(size));
                                                                size_t read = fread(m_rom.data(), 1, m_rom.size(), f);
                                                                    fclose(f);

                                                                        return read == m_rom.size();
                                                                        }

                                                                        void GbaCore::reset()
                                                                        {
                                                                            std::fill(m_framebuffer.begin(), m_framebuffer.end(), 0);
                                                                            }

                                                                            void GbaCore::setKeys(uint16_t keys)
                                                                            {
                                                                                m_keys = keys;
                                                                                }

                                                                                void GbaCore::runFrame()
                                                                                {
                                                                                    uint16_t color = m_keys ? 0xFFFF : 0x001F;
                                                                                        std::fill(m_framebuffer.begin(), m_framebuffer.end(), color);
                                                                                        }