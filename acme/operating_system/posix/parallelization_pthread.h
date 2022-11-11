//
// Created by camilo on 2022-10-25 19:14 <3ThomasBorregaardSorensen!!
//
#pragma once


using HSYNC = ::particle_pointer;


::e_status MsgWaitForMultipleObjectsEx(::u32 dwSize, HSYNC * pparticle, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags);

::e_status MsgWaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, ::u32 dwWakeMask);

::e_status WaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable);

::e_status WaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout);

::e_status WaitForSingleObjectEx(HSYNC hsync, ::u32 tickTimeout, int_bool bAlertable);

::e_status WaitForSingleObject(HSYNC hsync, ::u32 tickTimeout);



