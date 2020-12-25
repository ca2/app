#pragma once


#include  "_const.h"


#include  "_const_key.h"


DECLARE_C_FLAG(e_toolbar_item_state, enum_toolbar_item_state);
DECLARE_C_FLAG(e_toolbar_item_style, enum_toolbar_item_style);


namespace user
{


   using estate = cflag < enum_state >;

   using eelement = cflag < enum_element >;


   CLASS_DECL_ACME string get_wallpaper(::index iIndex);


} // namespace user


#include "os_colors.h"
#include "os_theme_colors.h"



