// Created by camilo on 2021-12-29 00:06 BRT <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME ::enum_status _last_error_to_status(DWORD dwLastError);
inline ::e_status last_error_to_status(DWORD dwLastError) { return _last_error_to_status(dwLastError); }


CLASS_DECL_ACME ::enum_status _hresult_to_status(HRESULT hresult);
inline ::e_status hresult_to_status(HRESULT hresult) { return _hresult_to_status(hresult); }


CLASS_DECL_ACME string last_error_message(DWORD dwError);



