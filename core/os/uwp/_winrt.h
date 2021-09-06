#pragma once


#undef System
#undef Platform
#undef papplication
#undef Session


CLASS_DECL_CORE bool __initialize(bool bDLL, ::u32 dwVersion);

CLASS_DECL_CORE uptr keycode_to_char(uptr n);

CLASS_DECL_CORE uptr virtualkey_to_char(::winrt::Windows::System::VirtualKey e);

CLASS_DECL_CORE::user::enum_key virtualkey_to_userkey(::winrt::Windows::System::VirtualKey e, bool& bSpecialKey);

CLASS_DECL_CORE uptr virtualkey_to_code(::winrt::Windows::System::VirtualKey e);



