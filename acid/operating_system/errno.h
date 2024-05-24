#pragma once


#define C_RUNTIME_ERROR_CHECK(expr) ::c_error_number::s_throw_exception(expr)


#include "acid/operating_system/shared_posix/c_error_number.h"


CLASS_DECL_ACID i32 get_errno();
CLASS_DECL_ACID void set_errno(i32 _Value);



