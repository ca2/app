#pragma once


#undef System
#undef Platform
#undef Application
#undef Session


CLASS_DECL_APEX bool __initialize(bool bDLL, DWORD dwVersion);

CLASS_DECL_APEX uptr keycode_to_char(uptr n);

CLASS_DECL_APEX uptr virtualkey_to_char(::Windows::System::VirtualKey e);

CLASS_DECL_APEX::user::e_key virtualkey_to_userkey(::Windows::System::VirtualKey e, bool& bSpecialKey);

CLASS_DECL_APEX uptr virtualkey_to_code(::Windows::System::VirtualKey e);



