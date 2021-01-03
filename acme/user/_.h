#pragma once


#include  "_const.h"


#include  "_const_key.h"


DECLARE_C_FLAG(e_toolbar_item_state, enum_toolbar_item_state);
DECLARE_C_FLAG(e_toolbar_item_style, enum_toolbar_item_style);


namespace user
{

   DECLARE_C_FLAG(enum_state, enum_state);

   CLASS_DECL_ACME string get_wallpaper(::index iIndex);


} // namespace user


#include "os_colors.h"
#include "os_theme_colors.h"



