#include "framework.h"
#include "acme/operating_system.h"


#ifdef WINDOWS_DESKTOP


string read_resource_as_string(hinstance hinst, ::u32 nID, const char * pcszType, strsize iReadAtMostByteCount)
{

   HRSRC hrsrc = ::FindResourceW((HINSTANCE) hinst, MAKEINTRESOURCEW(nID), wstring(pcszType));

   if (hrsrc == nullptr)
   {

      return "";

   }

   HGLOBAL hres = ::LoadResource((HINSTANCE)hinst, hrsrc);

   if (hres == nullptr)
      return "";

   u32 dwResSize = ::SizeofResource((HINSTANCE)hinst, hrsrc);

   string str;
   char * psz = nullptr;

   if (hres != nullptr)
   {

      ::u32 * pnRes = (::u32 *)::LockResource(hres);

      iReadAtMostByteCount = iReadAtMostByteCount < 0 ? dwResSize : minimum(iReadAtMostByteCount, (strsize) dwResSize);

      psz = str.get_string_buffer(iReadAtMostByteCount);

      ::memcpy_dup(psz, pnRes, iReadAtMostByteCount);

      psz[dwResSize] = '\0';

      str.release_string_buffer(iReadAtMostByteCount);

   }

   return str;

}


#endif



//CLASS_DECL_ACME string __str(const estatus & estatus)
//{
//
//   return __str((::i64) estatus.m_estatus);
//
//}


int debug_string_iterator()
{

   string str = "This is a phrase this is a link http://test.com/test_file?test_parameter=test_value";

   int iLinkLen = 0;

   int iColon = 0;

   for(auto character : str)
   {

      if (wide_char_is_alphabetic(character)
          || character == L'.'
          || character == L'/'
          || character == L'?'
          || character == L'&'
          || (character == L':' && iColon++ == 0))
      {

         iLinkLen++;

      }
      else
      {

         break;

      }

   }

   return iLinkLen;

}