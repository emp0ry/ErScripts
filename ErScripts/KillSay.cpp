#include "CS2Functions.h"

void CS2Functions::KillSay() {
    std::thread([this]() {
        int oldKills = globals::localPlayerKills;
        while (!globals::finish) {
            if (cfg->killSayState) {
                if (CS2Functions::GetWindowState() && CS2Functions::GetCursorState()) {
                    if (globals::localPlayerKills != oldKills) {
                        CommandsSender(8, std::format("say {}", cfg->killSayText));
                        oldKills = globals::localPlayerKills;
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}