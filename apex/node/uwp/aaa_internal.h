#pragma once


#undef new
#include <GdiPlus.h>
#include <Gdipluseffects.h>

#define new ACME_NEW

#include <wincrypt.h>


#include "_UWP_dir.h"
#include "_UWP_file_find.h"
#include "_UWP_file_system.h"
#include "_UWP_file.h"
#include "_UWP_shell.h"
//#include "ca2/ex1_resource.h"
#include "_UWP_resource.h"
//#include "application.h"
#include "_UWP_stdio_file.h"
#include "_UWP_file_set.h"

#include "_UWP_copydesk.h"
#include "_UWP_crypto.h"
#include "_UWP_ip_enum.h"
#include "_UWP_registry.h"

#include "_UWP_os.h"


// Sanity checks for ATOMs
//CLASS_DECL_APEX bool __is_valid_atom(ATOM nAtom);
//CLASS_DECL_APEX bool __is_valid_atom(const char * psz);
