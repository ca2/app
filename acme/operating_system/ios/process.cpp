// Created by camilo on 2026-07-17 16:17 <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-09-13 15:58 <3ThomasBorregaardSorensen!!
// From windows/window.h by camilo on 2026-02-28 21:17 <3ThomasBorregaardSørensen!!
// From macos/window.cpp by camilo on 2026-03-19 08:36 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/posix/termination_handler.h"



void acme_quite_early_construct()
{


   termination_handler::initialize();

}
