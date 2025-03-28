#include "ErScripts.h"

void ErScripts::CS2Binds() {
    std::thread([]() {
        while (!globals::finish) {
            if (ErScripts::GetWindowState() && ErScripts::GetCursorState()) {
                if (cfg->longJumpBind) {
                    if (GetAsyncKeyState(cfg->longJumpBind) & 0x8000) {
                        ErScripts::CommandsSender(7, "jump 1 1 0");
                        std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5) + 1));
                        ErScripts::CommandsSender(7, "duck 1 1 0");
                        std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5) + 1));
                        ErScripts::CommandsSender(7, "jump -999 1 0");
                        while ((GetAsyncKeyState(cfg->longJumpBind) & 0x8000)) {
                            if (globals::finish) break;
                            std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5) + 1));
                        }
                        ErScripts::CommandsSender(7, "duck -999 1 0");
                    }
                }

                if (cfg->jumpThrowBind) {
                    if (GetAsyncKeyState(cfg->jumpThrowBind) & 0x8000) {
                        ErScripts::CommandsSender(7, "jump 1 1 0");
                        std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5) + 1));
                        ErScripts::CommandsSender(7, "attack -999 1 0");
                        std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5) + 1));
                        ErScripts::CommandsSender(7, "jump -999 1 0");
                    }
                }

                if (cfg->dropBombBind) {
                    if (globals::isBombInWeapons) {
                        if (GetAsyncKeyState(cfg->dropBombBind) & 0x8000) {
                            ErScripts::CommandsSender(7, "slot5");
                            std::this_thread::sleep_for(std::chrono::milliseconds(64));
                            ErScripts::CommandsSender(7, "drop;lastinv");
                            std::this_thread::sleep_for(std::chrono::milliseconds(128));
                        }
                    }
                }

                if (cfg->selfKickBind) {
                    if (GetAsyncKeyState(cfg->selfKickBind) & 0x8000) {
                        ErScripts::CommandsSender(7, "status");
                        std::this_thread::sleep_for(std::chrono::milliseconds(256));
                        ErScripts::CommandsSender(7, std::format("callvote kick {}", globals::localPlayerSlotNumber));
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }).detach();
}