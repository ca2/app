#pragma once


#define _System ::apexacmesystem()
#define _Platform Platform
#define _Application papp
#define _Session get_session()


CLASS_DECL_APEX bool __initialize(bool bDLL, ::u32 dwVersion);

CLASS_DECL_APEX uptr keycode_to_char(uptr n);

//CLASS_DECL_APEX uptr virtualkey_to_char(VirtualKey e);
//
//CLASS_DECL_APEX::user::enum_key virtualkey_to_userkey(VirtualKey e, bool& bSpecialKey);
//
//CLASS_DECL_APEX uptr virtualkey_to_code(VirtualKey e);



