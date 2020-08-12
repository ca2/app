#pragma once


//#include "macos_windowing.h"


#define MAC_WINDOW(pwnd) (dynamic_cast < ::macos::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))


//#include "base/graphics/graphics_window_graphics.h"

// bool macos_set_user_wallpaper(const char * psz);
