#pragma once



#define CALLSTACK_DEFAULT_SKIP_TRIGGER (-2)

#define SKIP_callstack (-1)


#if defined(APPLE)

#define callstack_DEFAULT_SKIP 3

#elif defined(ANDROID)

#define callstack_DEFAULT_SKIP 4

#else

#define callstack_DEFAULT_SKIP 3

#endif


//
//enum enum_exception
//{
//
//   e_exception_out_of_bounds,
//   e_exception_interface_only,
//   e_exception_invalid_argument,
//   e_exception_invalid_character,
//   e_exception_invalid_handle,
//   e_exception_invalid_index,
//   e_exception_invalid_type,
//   e_exception_not_implemented,
//   e_exception_not_installed,
//   e_exception_not_licensed,
//   e_exception_not_supported,
//   e_exception_memory,
//   e_exception_operation_cancelled,
//   e_exception_overflow,
//   e_exception_parsing,
//   e_exception_range,
//   e_exception_resource,
//   e_exception_runtime,
//   e_exception_temporary,
//   e_exception_todo,
//   e_exception_void_implementation,
//   e_exception_user,
//   e_exception_system,
//   e_exception_os,
//   e_exception_io,
//   e_exception_installing,
//   
//};