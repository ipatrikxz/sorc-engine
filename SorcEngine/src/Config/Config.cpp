#include "Config.h"


namespace Config {
    Resolutions g_resolutions;

    void Init() {
        g_resolutions.gBuffer = { 1920, 1080 };
        g_resolutions.finalImage = { 1920 / 2, 1080 / 2 };
        g_resolutions.ui = { 1920, 1080 };
    }

    const Resolutions& GetResolutions() {
        return g_resolutions;
    }

}
