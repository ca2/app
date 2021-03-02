#pragma once



// Format a message using format string_base < TYPE_CHAR > 'pszFormat'
template < typename TYPE_CHAR >
void __cdecl string_base < TYPE_CHAR >::FormatMessage(const CHAR_TYPE * pszFormat, ...)
{
   if (pszFormat == nullptr)
   {

      __throw(error_invalid_argument);

   }

   va_list argList;

   va_start(argList, pszFormat);

   FormatMessageV(pszFormat, argList);

   va_end(argList);

}


void FormatMessageV(const CHAR_TYPE * pszFormat, va_list args);

// Format a message using format string_base < TYPE_CHAR > 'pszFormat' and va_list
template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::FormatMessageV(const CHAR_TYPE * pszFormat, va_list argList)
{

#ifdef WINDOWS_DESKTOP

   // format message into temporary buffer pszTemp

   CHAR_TYPE * pszTemp;

   u32 dwResult = ::str::format_message(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER, pszFormat, 0, 0, reinterpret_cast<CHAR_TYPE *>(&pszTemp), 0, &argList);

   if (dwResult == 0)
   {

      throw_memory_exception();

   }

   *this = pszTemp;

   LocalFree(pszTemp);

#else

   FormatV(pszFormat, argList);

#endif

}



#ifdef WINDOWS

// OLE BSTR support

// allocate a BSTR containing a copy of the string_base < TYPE_CHAR >
template < typename TYPE_CHAR >
BSTR string_base < TYPE_CHAR >::AllocSysString() const
{
   BSTR bstrResult = ::str::AllocSysString(data(), get_length());
   if (bstrResult == nullptr)
   {
      throw_memory_exception();
   }
   return(bstrResult);
}


template < typename TYPE_CHAR >
BSTR string_base < TYPE_CHAR >::SetSysString(BSTR * pbstr) const
{

   ASSERT(__is_valid_address(pbstr, sizeof(BSTR)));

   if (!::str::ReAllocSysString(pbstr, data(), get_length()))
   {

      throw_memory_exception();

   }

   ASSERT(*pbstr != nullptr);

   return(*pbstr);

}

#endif

