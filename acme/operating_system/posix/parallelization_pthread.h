//
// Created by camilo on 2022-10-25 19:14 <3ThomasBorregaardSorensen!!
//
#pragma once


using hsynchronization = ::subparticle *;


::e_status MsgWaitForMultipleObjectsEx(::u32 dwSize, hsynchronization * pparticle, const class ::time & tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags);

::e_status MsgWaitForMultipleObjects(::u32 dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout, ::u32 dwWakeMask);

::e_status WaitForMultipleObjectsEx(::u32 dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout, int_bool bAlertable);

::e_status WaitForMultipleObjects(::u32 dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout);

::e_status WaitForSingleObjectEx(hsynchronization hsynchronization, const class ::time & tickTimeout, int_bool bAlertable);

::e_status WaitForSingleObject(hsynchronization hsynchronization, const class ::time & tickTimeout);



