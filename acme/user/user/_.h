#pragma once


#include  "_constant.h"


#include  "_style.h"


class item;

struct os_theme_colors;


namespace user
{


   DECLARE_ENUMERATION(e_state, enum_state);
   CLASS_DECL_ACME string get_wallpaper(::index iIndex);


} // namespace user


namespace windowing
{


   class cursor;


} // namespace windowing


#include "acme/constant/button_state.h"


//#include "mouse.h"


//#include "os_colors.h"
//#include "theme_colors.h"

//#include "drag.h"



