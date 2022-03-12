#pragma once


#include "acme/user/nano/_nano.h"
#include "acme/operating_system.h"

#undef new
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.ApplicationModel.Core.h>

inline winrt::hstring __hstring(const char * psz)
{

   wstring wstr(psz);

   return wstr.c_str();

}

#include "window.h"



