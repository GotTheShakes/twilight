#include "gui/overlay_toggle.h"

#include <cstdio>

static int g_Failures = 0;

static void expect(bool ok, const char* label)
{
    if (!ok) {
        std::printf("FAIL %s\n", label);
        g_Failures++;
    }
}

int main()
{
    const int classic = OverlayToggleClassic;
    const int twilight = OverlayToggleTwilight;
    const int both = OverlayToggleClassic | OverlayToggleTwilight;

    // Both settings off: the shortcut still shows an overlay.
    expect(performanceOverlaysAfterToggle(false, false, false, false, true) == twilight,
           "both settings off shows the Twilight overlay");
    expect(performanceOverlaysAfterToggle(false, false, false, false, false) == classic,
           "both settings off without the Twilight HUD shows Classic");
    expect(performanceOverlaysAfterToggle(false, true, false, false, true) == OverlayToggleNone,
           "second press hides the overlay the shortcut showed");

    // Overlays enabled in Settings come back on the next press.
    expect(performanceOverlaysAfterToggle(false, false, true, false, true) == classic,
           "classic only");
    expect(performanceOverlaysAfterToggle(false, false, false, true, true) == twilight,
           "twilight only");
    expect(performanceOverlaysAfterToggle(false, false, true, true, true) == both,
           "both enabled shows both");
    expect(performanceOverlaysAfterToggle(false, false, true, true, false) == classic,
           "twilight setting is ignored without the Twilight HUD");

    // Anything showing is hidden by one press.
    expect(performanceOverlaysAfterToggle(true, true, true, true, true) == OverlayToggleNone,
           "both showing hides both");
    expect(performanceOverlaysAfterToggle(true, false, false, true, true) == OverlayToggleNone,
           "classic showing hides it");
    expect(performanceOverlaysAfterToggle(false, true, true, false, true) == OverlayToggleNone,
           "twilight showing hides it");
    expect(performanceOverlaysAfterToggle(false, true, false, false, false) == classic,
           "twilight state is ignored without the Twilight HUD");

    if (g_Failures != 0) {
        std::printf("%d failure(s)\n", g_Failures);
        return 1;
    }
    std::printf("overlay toggle tests passed\n");
    return 0;
}
