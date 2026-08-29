#include <switch.h>
#include <cstdio>
#include "core/gba_core.h"
#include "platform/input_switch.h"
#include "platform/video_switch.h"

static const char* ROM_PATH = "sdmc:/switch/gba-emu-switch/rom.gba";

int main(int argc, char* argv[])
{
    consoleInit(NULL);

        printf("GBA Emu Switch - iniciando...\n");
            printf("Buscando ROM en: %s\n", ROM_PATH);
                consoleUpdate(NULL);

                    GbaCore core;
                        if (!core.loadRom(ROM_PATH))
                            {
                                    printf("\nNo se encontro ninguna ROM valida en esa ruta.\n");
                                            printf("Copia un archivo .gba (dumpeado por vos) ahi y volve a abrir.\n");
                                                    printf("\nPresiona + para salir.\n");
                                                            consoleUpdate(NULL);

                                                                    PadState pad;
                                                                            padConfigureInput(1, HidNpadStyleSet_NpadStandard);
                                                                                    padInitializeDefault(&pad);

                                                                                            while (appletMainLoop())
                                                                                                    {
                                                                                                                padUpdate(&pad);
                                                                                                                            if (padGetButtonsDown(&pad) & HidNpadButton_Plus)
                                                                                                                                            break;
                                                                                                                                                        consoleUpdate(NULL);
                                                                                                                                                                }

                                                                                                                                                                        consoleExit(NULL);
                                                                                                                                                                                return 0;
                                                                                                                                                                                    }

                                                                                                                                                                                        InputSwitch input;
                                                                                                                                                                                            VideoSwitch video;
                                                                                                                                                                                                input.init();
                                                                                                                                                                                                    video.init();

                                                                                                                                                                                                        core.reset();

                                                                                                                                                                                                            while (appletMainLoop())
                                                                                                                                                                                                                {
                                                                                                                                                                                                                        input.update();
                                                                                                                                                                                                                                core.setKeys(input.getGbaKeys());

                                                                                                                                                                                                                                        core.runFrame();

                                                                                                                                                                                                                                                video.presentFrame(core.getFramebuffer());

                                                                                                                                                                                                                                                        if (input.exitRequested())
                                                                                                                                                                                                                                                                    break;
                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                            video.exit();
                                                                                                                                                                                                                                                                                consoleExit(NULL);
                                                                                                                                                                                                                                                                                    return 0;
                                                                                                                                                                                                                                                                                    }