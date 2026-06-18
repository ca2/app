//
//  lightui.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once



namespace lightui
{

enum enum_notification
{
   e_notification_default = 0, // WM_COMMAND wparam.hiword
   e_CBN_SELENDOK = 9, // WM_COMMAND wparam.hiword
   e_CBN_DROPDOWN = 7, // WM_COMMAND wparam.hiword
};


enum enum_SWP
{
e_SWP_NOSIZE =      0x0001,
e_SWP_NOMOVE  =     0x0002,
e_SWP_NOZORDER =    0x0004,
e_SWP_NOACTIVATE =  0x0010,
   
};

enum enum_SW
{
e_SW_HIDE =      0,
   
};


enum enum_MK : unsigned int
{
   e_MK_LBUTTON  = 0x0001, // Left mouse button is down.
   e_MK_RBUTTON  = 0x0002, // Right mouse button is down.
   e_MK_SHIFT    = 0x0004, // Shift key is down.
   e_MK_CONTROL  = 0x0008, // Control key is down.
   e_MK_MBUTTON  = 0x0010, // Middle mouse button is down.
   e_MK_XBUTTON1 = 0x0020, // XBUTTON1 is down.
   e_MK_XBUTTON2 = 0x0040, // XBUTTON2 is down.
};



} // namespace lightui
