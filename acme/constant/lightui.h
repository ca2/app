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

} // namespace lightui
