// Created by camilo on 2025-10-02 06:15 <3ThomasBorregaardSørensen!!
#pragma once


#if defined(WINDOWS)
#include "acme/operating_system/windows_common/networking.h"
#elif defined(LINUX)
#include "acme/operating_system/posix/networking.h"
#endif


CLASS_DECL_ACME::collection::count get_count_of_opened_sockets();
CLASS_DECL_ACME::collection::count increment_count_of_opened_sockets();
CLASS_DECL_ACME::collection::count decrement_count_of_opened_sockets();



