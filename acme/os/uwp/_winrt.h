#pragma once


#undef ::acme::get_system()
//#undef Platform
////#undef papplication
////#undef Session


CLASS_DECL_ACME bool __initialize(bool bDLL, ::u32 dwVersion);

CLASS_DECL_ACME uptr keycode_to_char(uptr n);

CLASS_DECL_ACME uptr virtualkey_to_char(::Windows::::acme::get_system()::VirtualKey e);

CLASS_DECL_ACME::user::enum_key virtualkey_to_userkey(::Windows::::acme::get_system()::VirtualKey e, bool& bSpecialKey);

CLASS_DECL_ACME uptr virtualkey_to_code(::Windows::::acme::get_system()::VirtualKey e);



