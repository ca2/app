#pragma once





#ifdef __cplusplus


CLASS_DECL_AQUA void throw_interface_only_exception(const char * psz = NULL);


CLASS_DECL_AQUA void wtf(const char * psz = NULL);


#else


CLASS_DECL_AQUA void throw_interface_only_exception(const char * psz);


CLASS_DECL_AQUA void wtf(const char * psz);


#endif






