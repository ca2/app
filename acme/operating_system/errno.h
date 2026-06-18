#pragma once


#define C_RUNTIME_ERROR_CHECK(expr) ::c_errno::s_throw_exception(expr)


#include "acme/operating_system/shared_posix/c_errno.h"


CLASS_DECL_ACME ::i32 get_errno();
CLASS_DECL_ACME void set_errno(::i32 _Value);



