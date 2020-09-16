//
//  windowing.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 16/09/20.
//
#pragma once


WINBOOL get_client_rect(oswindow hwnd,LPRECT lprect);

WINBOOL get_window_rect(oswindow hwnd,LPRECT lprect);

void defer_dock_application(int_bool bDock);

