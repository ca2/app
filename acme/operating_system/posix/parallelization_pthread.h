//
// Created by camilo on 2022-10-25 19:14 <3ThomasBorregaardSorensen!!
//
#pragma once


using hsynchronization = ::subparticle *;


::e_status MsgWaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * pparticle, const class ::time & tickTimeout, unsigned int dwWakeMask, unsigned int dwFlags);

::e_status MsgWaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout, unsigned int dwWakeMask);

::e_status WaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout, int_bool bAlertable);

::e_status WaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout);

::e_status WaitForSingleObjectEx(hsynchronization hsynchronization, const class ::time & tickTimeout, int_bool bAlertable);

::e_status WaitForSingleObject(hsynchronization hsynchronization, const class ::time & tickTimeout);



