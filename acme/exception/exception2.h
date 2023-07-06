#define C_RUNTIME_ERROR_CHECK(expr) ::c_runtime_error_check(expr)
#ifndef C_RUNTIME_ERRORCHECK_SPRINTF
#define C_RUNTIME_ERRORCHECK_SPRINTF(expr) \
do { \
   errno_t _saveErrno = errno; \
   errno = 0; \
   (expr); \
   if(0 != errno) \
   { \
      ::c_runtime_error_check(errno); \
   } \
   else \
   { \
      errno = _saveErrno; \
   } \
} while (0)
#endif // C_RUNTIME_ERRORCHECK_SPRINTF


CLASS_DECL_ACME c_error_number c_runtime_error_check(c_error_number error);
//{
//    switch(error)
//    {
//        case ENOMEM:
//            throw ::exception(error_no_memory);
//            break;
//        case EINVAL:
//        case ERANGE:
//            throw ::exception(error_bad_argument);
//            break;
//#if defined(WINDOWS)
//        case STRUNCATE:
//#endif
//        case 0:
//            break;
//        default:
//            throw ::exception(error_bad_argument);
//            break;
//    }
//    return error;
//}






