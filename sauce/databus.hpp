    // Copyright 2025 goat5ucker
#pragma once

enum class _panel_control_state{ default, files, settings };

namespace databus
{
    bool quit_call = false;
    bool panel_control_opened = true; // unused
    _panel_control_state panel_control_state = _panel_control_state::default;
}

namespace utils
{ 

}