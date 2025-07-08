    // Copyright 2025 goat5ucker
#pragma once

#include <filesystem>

namespace databus
{
    inline bool quit_call = false;
    inline bool conpan_open = true;
    // 0 for standby, 1 for view, 2 for editing;
    inline int editor_mode = 0; 
    // updates on error call, time in milliseconds (it also fades out with time of 256 milliseconds);
    inline unsigned int sfml_error_msg_display = 0;
}

// read, convert and write utils
namespace r_c_w_utils
{
    namespace fs = std::filesystem;
    
    // checks a file to be an svg or constellation. returns 1 on svg (TODO), returns 2 on constellation, returns -1 on invalid file
    [[nodiscard]] inline int file_check(fs::path path) 
    {
        int ret = -1;


        return ret;
    }
}