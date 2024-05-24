#pragma once


#undef ::aceacesystem()
//#undef Platform
////#undef papp
////#undef Session


namespace universal_windows
{


   CLASS_DECL_ACID bool __initialize(bool bDLL, ::u32 dwVersion);

   CLASS_DECL_ACID uptr keycode_to_char(uptr n);

   CLASS_DECL_ACID uptr virtualkey_to_char(::winrt::Windows::aceacesystem()::VirtualKey e);

   CLASS_DECL_ACID::user::enum_key virtualkey_to_userkey(::winrt::Windows::aceacesystem()::VirtualKey e, bool & bSpecialKey);

   CLASS_DECL_ACID uptr virtualkey_to_code(::winrt::Windows::aceacesystem()::VirtualKey e);

 
} // namespace universal_windows


#include "file_winrt.h"


