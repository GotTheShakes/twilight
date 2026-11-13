#pragma once

// What Ctrl+Alt+Shift+S (and the gamepad stats combo) does to the two
// performance overlays. The Settings toggles only decide which overlays are
// shown when a stream starts; the shortcut works either way, as in Moonlight.
//
// If any overlay is showing, one press hides them all. If none is showing,
// it shows the overlays enabled in Settings, or the Twilight overlay (the
// Classic one when the Twilight HUD is unavailable) if neither is enabled.

enum OverlayToggleTarget
{
    OverlayToggleNone = 0,
    OverlayToggleClassic = 1 << 0,
    OverlayToggleTwilight = 1 << 1,
};

// Returns the overlays that should be visible after the press.
inline int performanceOverlaysAfterToggle(bool classicVisible, bool twilightVisible,
                                          bool classicEnabled, bool twilightEnabled,
                                          bool twilightAvailable)
{
    if (classicVisible || (twilightAvailable && twilightVisible)) {
        return OverlayToggleNone;
    }

    int shown = OverlayToggleNone;
    if (classicEnabled) {
        shown |= OverlayToggleClassic;
    }
    if (twilightEnabled && twilightAvailable) {
        shown |= OverlayToggleTwilight;
    }
    if (shown == OverlayToggleNone) {
        shown = twilightAvailable ? OverlayToggleTwilight : OverlayToggleClassic;
    }
    return shown;
}
