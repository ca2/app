#pragma once





#ifdef __cplusplus


CLASS_DECL_ACME void throw_interface_only_exception(const char * psz = NULL);


CLASS_DECL_ACME void wtf(const char * psz = NULL);


#else


CLASS_DECL_ACME void throw_interface_only_exception(const char * psz);


CLASS_DECL_ACME void wtf(const char * psz);


#endif






