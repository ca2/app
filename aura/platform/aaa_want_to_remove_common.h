namespace aura
{

   inline void __cdecl strcpy_s(char * _S1, strsize _S1max, const char * _S2)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::strcpy_s(_S1, (rsize_t)_S1max, _S2));
#else
      strcpy(_S1, _S2);
#endif
   }

   inline void __cdecl wcscpy_s(unichar * _S1, strsize _S1max, const unichar * _S2)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::wcscpy_s(_S1, (rsize_t)_S1max, _S2));
#else
      wide_copy(_S1, _S2);
#endif
   }

   inline errno_t __cdecl strncpy_s(char * _Dest, strsize _SizeInChars, const char * _Source, strsize _Count)
   {
#ifdef WINDOWS
      return C_RUNTIME_ERROR_CHECK(::strncpy_s(_Dest, (rsize_t)_SizeInChars, _Source, (rsize_t)_Count));
#else
      ansi_count_copy(_Dest, _Source, _Count);
      return errno;
#endif
   }

   inline errno_t __cdecl wcsncpy_s(unichar * _Dest, strsize _SizeInChars, const unichar * _Source, strsize _Count)
   {
#ifdef WINDOWS
      return C_RUNTIME_ERROR_CHECK(::wcsncpy_s(_Dest, (rsize_t)_SizeInChars, _Source, (rsize_t)_Count));
#elif defined ANDROID || defined APPLEOS || defined(LINUX)
      wide_count_copy(_Dest, _Source, _Count);
      return errno;
#else
      wcsncpy(_Dest, _Source, _Count);
      return errno;
#endif
   }

   inline void __cdecl strcat_s(char * _Dst, strsize _SizeInChars, const char * _Src)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::strcat_s(_Dst, (rsize_t)_SizeInChars, _Src));
#else
      ansi_concatenate(_Dst, _Src);
#endif
   }

   inline void __cdecl wcscat_s(unichar * _Dst, strsize _SizeInChars, const unichar * _Src)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::wcscat_s(_Dst, (rsize_t)_SizeInChars, _Src));
#else
      wide_concatenate(_Dst, _Src);
#endif
   }

   inline void __cdecl strlwr_s(char * Str, strsize _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_strlwr_s(Str, (rsize_t)_SizeInChars));
#elif defined(ANDROID) || defined(APPLEOS)
      ansi_lower(Str);
#else
      ansi_lower(Str);
#endif
   }

   inline void __cdecl wcslwr_s(unichar * Str, strsize _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_wcslwr_s(Str, (rsize_t)_SizeInChars));
#else
      C_RUNTIME_ERROR_CHECK(::wide_lower(Str, _SizeInChars));
#endif
   }

   inline void __cdecl strupr_s(char * Str, strsize _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_strupr_s(Str, (rsize_t)_SizeInChars));
#elif defined(ANDROID) || defined(APPLEOS)
      ansi_upper(Str);
#else
      ansi_upper(Str);
#endif
   }

   inline void __cdecl wcsupr_s(unichar * Str, strsize _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_wcsupr_s(Str, (rsize_t)_SizeInChars));
#else
      C_RUNTIME_ERROR_CHECK(::wide_upper(Str, _SizeInChars));
#endif
   }

   inline void __cdecl itoa_s(i32 _Val, char * _Buf, strsize _SizeInChars, i32 _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_itoa_s(_Val, _Buf, (rsize_t)_SizeInChars, _Radix));
#else
      ansi_from_i64(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl i64toa_s(i64 _Val, char * _Buf, strsize _SizeInChars, i32 _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_i64toa_s(_Val, _Buf, (rsize_t)_SizeInChars, _Radix));
#else
      ansi_from_i64(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl i64tow_s(i64 _Val, unichar * _Buf, strsize _SizeInChars, i32 _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_i64tow_s(_Val, _Buf, (rsize_t)_SizeInChars, _Radix));
#else
      wide_from_i64_base(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl ui64toa_s(u64 _Val, char * _Buf, strsize _SizeInChars, i32 _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_ui64toa_s(_Val, _Buf, (rsize_t)_SizeInChars, _Radix));
#else
      ansi_from_i64(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl ui64tow_s(u64 _Val, unichar * _Buf, strsize _SizeInChars, i32 _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_ui64tow_s(_Val, _Buf, (rsize_t)_SizeInChars, _Radix));
#else
      wide_from_i64_base(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl gcvt_s(char * _Buffer, strsize _SizeInChars, double _Value, i32 _Ndec)
   {
      C_RUNTIME_ERROR_CHECK(::gcvt_dup(_Buffer, (int)_SizeInChars, _Value, _Ndec));
   }

   /*
      inline void __cdecl tsplitpath_s(
         const char *_Path,
         char *_Drive, strsize _Drive_len,
         char *_Dir, strsize _Dir_len,
         char *_Fname, strsize _Fname_len,
         char *_Ext, strsize _Ext_len)
      {
         C_RUNTIME_ERROR_CHECK(::_tsplitpath_s(_Path, _Drive, _Drive_len, _Dir, _Dir_len, _Fname, _Fname_len, _Ext, _Ext_len));
      }

      inline void __cdecl tmakepath_s(char *_Path, strsize _SizeInChars, const char *_Drive,
         const char *_Dir, const char *_Fname, const char *_Ext)
      {
         C_RUNTIME_ERROR_CHECK(::_tmakepath_s(_Path, _SizeInChars, _Drive, _Dir, _Fname, _Ext));
      }*/

   inline strsize __cdecl strnlen(const char * _Str, strsize _Maxsize)
   {
#ifdef WINDOWS
      return ::strnlen(_Str, (rsize_t)_Maxsize);
#else
      return ::strlen(_Str);
#endif
   }

   inline strsize __cdecl wcsnlen(const unichar * _Wcs, strsize _Maxsize)
   {
#ifdef WINDOWS
      return ::wcsnlen(_Wcs, (rsize_t)_Maxsize);
#else
      return ::wide_length(_Wcs);
#endif
   }


} // namespace aura

