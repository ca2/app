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


inline errno_t c_runtime_error_check(errno_t error)
{
    switch(error)
    {
        case ENOMEM:
            __throw(error_no_memory);
            break;
        case EINVAL:
        case ERANGE:
            __throw(error_invalid_argument);
            break;
#if defined(WINDOWS)
        case STRUNCATE:
#endif
        case 0:
            break;
        default:
            __throw(error_invalid_argument);
            break;
    }
    return error;
}

inline void __cdecl __clearerr_s(FILE *stream)
{
#ifdef WINDOWS
   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
#else
   ::clearerr(stream);
   C_RUNTIME_ERROR_CHECK(errno);
#endif
}
