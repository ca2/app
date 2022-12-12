#include "framework.h"


#ifndef WINDOWS
#include <unistd.h>


static inline void *AllocateForBSTR(size_t cb)
{

   return ::malloc(cb);

}

static inline void FreeForBSTR(void *pv)
{

   ::free(pv);

}


static ::u32 MyStringLen(const ::wd16_character *s)
{
  ::u32 i;
  for (i = 0; s[i] != '\0'; i++);
  return i;
}

BSTR SysAllocStringByteLen(const ::string & psz, ::u32 len)
{
  i32 realLen = len + sizeof(::u32) + sizeof(OLECHAR) + sizeof(OLECHAR);
  void *point = AllocateForBSTR(realLen);
  if (point == 0)
    return 0;
  *(::u32 *)point = len;
  BSTR bstr = (BSTR)((::u32 *)point + 1);
  __memmov(bstr, psz, len);
  u8 *pb = ((u8 *)bstr) + len;
  for (i32 i = 0; less_than(i, sizeof(OLECHAR) * 2); i++)
    pb[i] = 0;
  return bstr;
}

BSTR SysAllocString(const OLECHAR *sz)
{
  if (sz == 0)
    return 0;
  ::u32 strLen = MyStringLen(sz);
  ::u32 len = (strLen + 1) * sizeof(OLECHAR);
  void *point = AllocateForBSTR(len + sizeof(::u32));
  if (point == 0)
    return 0;
  *(::u32 *)point = strLen;
  BSTR bstr = (BSTR)((::u32 *)point + 1);
  __memmov(bstr, sz, len);
  return bstr;
}

void SysFreeString(BSTR bstr)
{
  if (bstr != 0)
    FreeForBSTR((::u32 *)bstr - 1);
}

::u32 SysStringByteLen(BSTR bstr)
{
  if (bstr == 0)
    return 0;
  return *((::u32 *)bstr - 1);
}

::u32 SysStringLen(BSTR bstr)
{
  return SysStringByteLen(bstr) / sizeof(OLECHAR);
}

HRESULT VariantClear(VARIANTARG *prop)
{
  if (prop->vt == VT_BSTR)
    SysFreeString(prop->bstrVal);
  prop->vt = VT_EMPTY;
  return S_OK;
}

HRESULT VariantCopy(VARIANTARG *dest, VARIANTARG *src)
{
  HRESULT res = ::VariantClear(dest);
  if (res != S_OK)
    return res;
  if (src->vt == VT_BSTR)
  {
    dest->bstrVal = SysAllocStringByteLen((const ::string &)src->bstrVal,
        SysStringByteLen(src->bstrVal));
    if (dest->bstrVal == 0)
      return E_OUTOFMEMORY;
    dest->vt = VT_BSTR;
  }
  else
    *dest = *src;
  return S_OK;
}

::i32 CompareFileTime(const FILETIME* ft1, const FILETIME* ft2)
{
  if (ft1->dwHighDateTime < ft2->dwHighDateTime) return -1;
  if (ft1->dwHighDateTime > ft2->dwHighDateTime) return 1;
  if (ft1->dwLowDateTime < ft2->dwLowDateTime) return -1;
  if (ft1->dwLowDateTime > ft2->dwLowDateTime) return 1;
  return 0;
}

#endif // !defined(WINDOWS)



#ifdef _UWP

BOOL WINAPI LockFile(HANDLE hfile, u32 dwLo, u32 dwHi, u32 dwCountLo, u32 dwCountHi);

BOOL WINAPI LockFile(HANDLE hfile, u32 dwLo, u32 dwHi, u32 dwCountLo, u32 dwCountHi)
{
   OVERLAPPED ov;
   zero(&ov, sizeof(ov));
   ov.Offset = dwLo;
   ov.OffsetHigh = dwHi;
   return LockFileEx(hfile, LOCKFILE_FAIL_IMMEDIATELY, 0, dwCountLo, dwCountHi, &ov);

}

BOOL WINAPI UnlockFile(HANDLE hfile, u32 dwLo, u32 dwHi, u32 dwCountLo, u32 dwCountHi)
{
   OVERLAPPED ov;
   zero(&ov, sizeof(ov));
   ov.Offset = dwLo;
   ov.OffsetHigh = dwHi;
   return UnlockFileEx(hfile, 0, dwCountLo, dwCountHi, &ov);

}


#endif


VARIANT_BOOL BoolToVARIANT_BOOL(int_bool v) { return (v ? VARIANT_TRUE: VARIANT_FALSE); }
int_bool VARIANT_BOOLToBool(VARIANT_BOOL v) { return (v != VARIANT_FALSE); }



CLASS_DECL_AURA int_bool is_windows_nt()
{

   return false;

}


CLASS_DECL_AURA int_bool is_windows_2000_or_greater()
{

   return false;

}


CLASS_DECL_AURA int_bool is_windows_nt_lesser_than_2000()
{

   return false;

}


#if !defined(_UWP)
::u32 get_current_process_id()
{

    return getpid();

}
#endif




