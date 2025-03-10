//
//  tool_item.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 03/Oct/22 20:28
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


enum enum_tool_item_state : long long
{

   e_tool_item_state_none,
   e_tool_item_state_checked         = 1 << 0,
   e_tool_item_state_pressed         = 1 << 1,
   e_tool_item_state_enabled         = 1 << 2,
   e_tool_item_state_hidden          = 1 << 3,
   e_tool_item_state_indeterminate   = 1 << 4,
   e_tool_item_state_wrap            = 1 << 5,
   e_tool_item_state_ellipses        = 1 << 6,
   e_tool_item_state_marked          = 1 << 7,
   e_tool_item_state_hover           = 1 << 8,

};


enum enum_tool_item_style : long long
{

   e_tool_item_style_none = e_toolbar_style_none,
   e_tool_item_style_separator = e_toolbar_style_separator,
   e_tool_item_style_checkbox = e_toolbar_style_check,
   e_tool_item_style_group = e_toolbar_style_group,
   e_tool_item_style_check_group = e_tool_item_style_group | e_tool_item_style_checkbox,
   e_tool_item_style_dropdown = e_toolbar_style_dropdown,
   e_tool_item_style_autosize = e_toolbar_style_autosize,
   e_tool_item_style_noprefix = e_toolbar_style_noprefix,
   e_tool_item_style_custom_control = 1_uintmax,
//#define TBBS_AUTOSIZE   make_int(TBSTYLE_AUTOSIZE, 0) // autocalc button width
//#define TBBS_NOPREFIX   make_int(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
   e_tool_item_style_checked = make_int(0, e_tool_item_state_checked),
   e_tool_item_style_pressed = make_int(0, e_tool_item_state_pressed),
   e_tool_item_style_disabled = make_int(0, e_tool_item_state_enabled),
   e_tool_item_style_indeterminate = make_int(0, e_tool_item_state_indeterminate),
   e_tool_item_style_hidden = make_int(0, e_tool_item_state_hidden),
   e_tool_item_style_wrapped = make_int(0, e_tool_item_state_wrap),
   e_tool_item_style_ellipses = make_int(0, e_tool_item_state_ellipses),
   e_tool_item_style_marked = make_int(0, e_tool_item_state_marked),
};


DECLARE_ENUMERATION(e_tool_item_state, enum_tool_item_state);
DECLARE_ENUMERATION(e_tool_item_style, enum_tool_item_style);



