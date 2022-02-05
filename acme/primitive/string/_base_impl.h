#pragma once



template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::construct() noexcept
{

   POINTER::natural_release();

}


//#ifdef WINDOWS
//
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(const USHORT* pshSrc)
//{
//
//   *this = pshSrc;
//
//}
//
//
//#endif


//#ifdef _UWP
//
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(Array <byte >^ a)
//{
//
//   *this = string_base < TYPE_CHAR >((const ansichar *) a->begin(), a->Length);
//
//}
//
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(Object^ o)
//{
//
//   *this = o->ToString()->Begin();
//
//}
//
//
//
//
//
//#endif



//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(strsize nLength, CHAR_TYPE ch)
//{
//
//   ASSERT(nLength >= 0);
//
//   if (nLength > 0)
//   {
//
//      CHAR_TYPE* pszBuffer = get_string_buffer(nLength);
//
//      ::str::flood_characters(ch, nLength, pszBuffer);
//
//      release_string_buffer(nLength);
//
//   }
//
//}



//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(const CHAR_TYPE* pszSrc)
//{
//
//   string_base < TYPE_CHAR >::operator=(pszSrc);
//
//   return *this;
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(string_base < TYPE_CHAR >&& str)
//{
//   get_data()->Release();
//   this->m_pdata = str.m_pdata;
//   str.m_pdata = nullptr;
//   return *this;
//
//}

//#ifdef WINDOWS
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(const USHORT* pshSrc)
//{
//
//   return operator=((const widechar*)pshSrc);
//
//}
//
//#endif


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(const widechar* pszSrc)
//{
//
//   strsize nDestLength = (pszSrc != nullptr) ? ::str::get_char_length(pszSrc) : 0;
//
//   if (nDestLength > 0)
//   {
//
//      CHAR_TYPE* pszBuffer = get_string_buffer(nDestLength);
//
//      ::str::ConvertTochar(pszBuffer, nDestLength, pszSrc);
//
//      release_string_buffer(nDestLength);
//
//   }
//   else
//   {
//
//      Empty();
//
//   }
//
//   return *this;
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(const wd32char* pszSrc)
//{
//   // nDestLength is in XCHARs
//   strsize nDestLength = (pszSrc != nullptr) ? wd32_to_wd16_len(pszSrc) : 0;
//   if (nDestLength > 0)
//   {
//      CHAR_TYPE* pszBuffer = get_string_buffer(nDestLength);
//      wd32_to_ansi(pszBuffer, pszSrc, nDestLength);
//      release_string_buffer(nDestLength);
//   }
//   else
//   {
//      Empty();
//   }
//
//   return *this;
//}
//

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(const uchar* pszSrc)
//{
//   return(operator=(reinterpret_cast<const CHAR_TYPE*>(pszSrc)));
//}
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(CHAR_TYPE ch)
//{
//   CHAR_TYPE ach[2] = { ch,0 };
//
//   return(operator=(ach));
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator=(widechar ch)
//{
//   widechar ach[2] = { ch,0 };
//
//   return(operator=(ach));
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(const string_base < TYPE_CHAR >& str)
//{
//   append(str);
//
//   return *this;
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(const CHAR_TYPE* pszSrc)
//{
//   string_base < TYPE_CHAR >::operator+=(pszSrc);
//
//   return *this;
//}

//#ifdef WINDOWS
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(const USHORT* pshSrc)
//{
//
//   string_base < TYPE_CHAR > str(pshSrc);
//
//   return operator+=(str);
//
//}
//
//#endif

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(const widechar* pszSrc)
//{
//   string_base < TYPE_CHAR > str(pszSrc, GetManager());
//
//   return(operator+=(str));
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(CHAR_TYPE ch)
//{
//
//   append_char((CHAR_TYPE)ch);
//
//   return *this;
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(uchar ch)
//{
//
//   append_char((CHAR_TYPE)ch);
//
//   return *this;
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator+=(widechar ch)
//{
//
//   append_char((CHAR_TYPE)ch);
//
//   return *this;
//
//}

//// Override from acme class
//template < typename TYPE_CHAR >
//string_manager* string_base < TYPE_CHAR >::GetManager() const noexcept
//{
//   string_manager* pstringmanager = string_base < TYPE_CHAR >::GetManager();
//   if (pstringmanager) { return pstringmanager; }
//
//   pstringmanager = ::str::GetDefaultManager();
//   return pstringmanager->Clone();
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(const string_base < TYPE_CHAR >& str)
//{
//   return operator = (str);
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(const string_base < TYPE_CHAR >& str, strsize pos, strsize n)
//{
//   return operator = (str.substr(pos, n));
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(const CHAR_TYPE* s, strsize n)
//{
//   return operator = (string_base < TYPE_CHAR >(s, n));
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(const CHAR_TYPE* s)
//{
//   return operator = (s);
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(strsize n, CHAR_TYPE ca)
//{
//   return operator = (string_base < TYPE_CHAR >(ca, n));
//}

//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(i32 n, i32 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(i64 n, i64 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(u32 n, u32 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(u64 n, u64 ca)
//{
//   string_base < TYPE_CHAR > strChar = ::str::uni_to_utf8(ca);
//   while (n > 0)
//   {
//      *this += strChar;
//   }
//   return *this;
//}



//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare(const CHAR_TYPE* psz) const noexcept
//{
//   return POINTER::string_compare(data(), psz);
//}

//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare_ci(const CHAR_TYPE* psz) const noexcept
//{
//   return POINTER::string_compare_ci(data(), psz);
//}

//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate(const CHAR_TYPE* psz) const noexcept
//{
//   return POINTER::string_collate(data(), psz);
//}

//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate_ci(const CHAR_TYPE* psz) const noexcept
//{
//   return POINTER::string_collate_ci(data(), psz);
//}

//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare(const CHAR_TYPE * psz, strsize n) const
//{
//   return POINTER::string_n_compare(data(), psz, n);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare_ci(const CHAR_TYPE * psz) const noexcept
//{
//  return POINTER::string_n_compare_ci(data(), psz, n);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate(const CHAR_TYPE * psz) const noexcept
//{
//  return POINTER::string_n_collate(data(), psz, n);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate_ci(const CHAR_TYPE * psz) const noexcept
//{
//  return POINTER::string_n_collate_ci(data(), psz, n);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare(strsize iStart, strsize nCount, const CHAR_TYPE* psz) const
//{
//   return substr(iStart, nCount).compare(psz);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare_ci(strsize iStart, strsize nCount, const CHAR_TYPE* psz) const
//{
//   return substr(iStart, nCount).compare_ci(psz);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate(strsize iStart, strsize nCount, const CHAR_TYPE* psz) const
//{
//   return substr(iStart, nCount).collate(psz);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate_ci(strsize iStart, strsize nCount, const CHAR_TYPE* psz) const
//{
//   return substr(iStart, nCount).compare_ci(psz);
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare(strsize iStart, strsize nCount, const CHAR_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).compare(string_base < TYPE_CHAR >(psz).substr(start2, count2));
//
//}
//
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::compare_ci(strsize iStart, strsize nCount, const CHAR_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).compare_ci(string_base < TYPE_CHAR >(psz).substr(start2, count2));
//
//}
//
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate(strsize iStart, strsize nCount, const CHAR_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).collate(string_base < TYPE_CHAR >(psz).substr(start2, count2));
//
//}
//
//template < typename TYPE_CHAR >
//i32 string_base < TYPE_CHAR >::collate_ci(strsize iStart, strsize nCount, const CHAR_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).collate_ci(string_base < TYPE_CHAR >(psz).substr(start2, count2));
//
//}

template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains(const CHAR_TYPE * psz, strsize iStart, strsize nCount) const
{

   return find(psz, iStart, nCount) >= 0;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_ci(const CHAR_TYPE * psz, strsize iStart, strsize nCount) const
{

   return find_ci(psz, iStart, nCount) >= 0;

}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains(const CHAR_TYPE * psz, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
//{
//
//   strsize iFind = find(psz, iStart, nCount, ppszEnd);
//
//   if (iFind < 0)
//   {
//
//      return false;
//
//   }
//
//   if (ppszBeg)
//   {
//
//      *ppszBeg = psz + iFind;
//
//   }
//
//   return true;
//
//}
//
//
//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_ci(const CHAR_TYPE * psz, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
//{
//
//   strsize iFind = find_ci(psz, iStart, nCount, ppszEnd);
//
//   if (iFind < 0)
//   {
//
//      return false;
//
//   }
//
//   if (ppszBeg)
//   {
//
//      *ppszBeg = psz + iFind;
//
//   }
//
//   return true;
//
//}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains(CHAR_TYPE ch, strsize iStart, strsize nCount) const
//{
//
//   return find(ch, iStart, nCount) >= 0;
//
//}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains(widechar wch, strsize iStart, strsize nCount) const
//{
//
//   return find_w(::str::uni_to_utf8(wch), iStart, nCount) >= 0;
//
//}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains(i32 i, strsize iStart, strsize nCount) const // utf8 CHAR_TYPE index
//{
//
//   return find_w(::str::uni_to_utf8(i), iStart, nCount) >= 0;
//
//}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains(const CHAR_TYPE* psz, strsize iStart, strsize nCount) const
//{
//
//   return find(psz, iStart, nCount) >= 0;
//
//}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains(const string_base < TYPE_CHAR >& str, strsize iStart, strsize nCount) const
{

   return find(str, iStart, nCount) >= 0;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains(CHAR_TYPE ch, strsize iStart, strsize nCount) const
{

   return find_ci(ch, iStart, nCount) >= 0;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_ci(CHAR_TYPE ch, strsize iStart, strsize nCount) const
{

   return find_ci(ch, iStart, nCount) >= 0;

}

template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains(CHAR_TYPE ch, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg) const
{

   auto find = this->find(ch, iStart, nCount);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_ci(CHAR_TYPE ch, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg) const
{

   auto find = find_ci(ch, iStart, nCount);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}



//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_ci(widechar wch, strsize iStart, strsize nCount) const
//{
//
//   return find_wci(::str::uni_to_utf8(wch), iStart, nCount) >= 0;
//
//}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_ci(i32 i, strsize iStart, strsize nCount) const// utf8 CHAR_TYPE index
//{
//
//   return find_wci(::str::uni_to_utf8(i), iStart, nCount) >= 0;
//
//}

//
//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_ci(const CHAR_TYPE* psz, strsize iStart, strsize nCount) const
//{
//
//   return find_ci(psz, iStart, nCount) >= 0;
//
//}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_ci(const string_base < CHAR_TYPE >& str, strsize iStart, strsize nCount) const
{

   return find_ci(str, iStart, nCount) >= 0;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains(const string_base < CHAR_TYPE > & str, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
{

   auto find = this->find(str, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_ci(const string_base < CHAR_TYPE > & str, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
{

   auto find = find_ci(str, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}

template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_wci(const string_base < CHAR_TYPE > & str, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
{

   auto find = find_wci(str, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_wci(CHAR_TYPE ch, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg) const
//{
//
//   auto find = find_wci(ch, iStart, nCount);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->m_pdata + find;
//
//   }
//
//   return true;
//
//}

template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains(const CHAR_TYPE * psz, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
{

   auto find = this->find(psz, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_ci(const CHAR_TYPE * psz, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
{

   auto find = find_ci(psz, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}

template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_wci(const CHAR_TYPE * psz, strsize iStart, strsize nCount, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd) const
{

   auto find = find_wci(psz, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}

//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_wci(CHAR_TYPE wch, strsize iStart, strsize nCount) const
//{
//
//   return find_wci(wch, iStart, nCount) >= 0;
//
//}

//
//template < typename TYPE_CHAR >
//bool string_base < TYPE_CHAR >::contains_wci(i32 i, strsize iStart, strsize nCount) const// utf8 CHAR_TYPE index
//{
//
//   return find_wci(::str::uni_to_utf8(i), iStart, nCount) >= 0;
//
//}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_wci(const CHAR_TYPE * psz, strsize iStart, strsize nCount) const
{

   return find_wci(psz, iStart, nCount) >= 0;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_wci(const string_base < TYPE_CHAR >& str, strsize iStart, strsize nCount) const
{

   return find_wci(str, iStart, nCount) >= 0;

}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::erase(strsize iStart, strsize strsize)
//{
//
//   if (iStart < 0)
//   {
//
//      strsize = 0;
//
//   }
//
//   if (strsize < 0)
//   {
//
//      strsize = get_length();
//
//   }
//
//   Delete(iStart, strsize);
//
//   return *this;
//
//}


template < typename TYPE_CHAR >
string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::erase(strsize iIndex, strsize nCount)
{

   strsize nLength = get_length();

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (nCount < 0)
   {

      nCount = nLength;

   }

   if (nCount + iIndex > nLength)
   {

      nCount = nLength - iIndex;

   }

   if (nCount < 0)
   {

      return *this;

   }

   if (nCount + iIndex > nLength)
   {

      nCount = nLength - iIndex;

   }

   if (nCount > 0)
   {

      strsize nNewLength = nLength - nCount;

      strsize nCopy = nLength - (iIndex + nCount) + 1;

      CHAR_TYPE* pszBuffer = get_string_buffer();

      memmove(pszBuffer + iIndex, pszBuffer + iIndex + nCount, (size_t)nCopy);

      release_string_buffer(nNewLength);

   }

   return *this;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::Insert(strsize iIndex, CHAR_TYPE ch)
{

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (iIndex > get_length())
   {

      iIndex = get_length();

   }

   strsize nNewLength = get_length() + 1;

   CHAR_TYPE* pszBuffer = get_string_buffer(nNewLength);

   memmove(pszBuffer + iIndex + 1, pszBuffer + iIndex, nNewLength - iIndex);

   pszBuffer[iIndex] = ch;

   release_string_buffer(nNewLength);

   return nNewLength;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::Insert(strsize iIndex, const CHAR_TYPE * psz)
{

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (iIndex > get_length())
   {

      iIndex = get_length();

   }

   // nInsertLength and nNewLength are in XCHARs

   strsize nInsertLength = ::str::string_safe_length(psz);

   strsize nNewLength = get_length();

   if (nInsertLength > 0)
   {

      nNewLength += nInsertLength;

      CHAR_TYPE* pszBuffer = get_string_buffer(nNewLength);
      // move existing bytes down
      memmove(pszBuffer + iIndex + nInsertLength, pszBuffer + iIndex, (nNewLength - iIndex - nInsertLength + 1) * sizeof(CHAR_TYPE));
      memcpy(pszBuffer + iIndex, psz, nInsertLength * sizeof(CHAR_TYPE));
      release_string_buffer(nNewLength);
   }

   return(nNewLength);
}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::replace_with(CHAR_TYPE charNew, CHAR_TYPE charOld, strsize iStart)
{
   strsize nCount = 0;

   // i16-circuit the nop case
   if (charOld != charNew)
   {
      // otherwise modify each character that matches in the string_base < TYPE_CHAR >
      bool bCopied = false;
      CHAR_TYPE* pszBuffer = const_cast<CHAR_TYPE*>(data() + iStart);  // We don't actually write to pszBuffer until we've called get_string_buffer().

      strsize nLength = get_length();
      strsize iChar = 0;
      while (iChar < nLength)
      {
         // replace instances of the specified character only
         if (pszBuffer[iChar] == charOld)
         {
            if (!bCopied)
            {
               bCopied = true;
               pszBuffer = get_string_buffer(nLength);
            }
            pszBuffer[iChar] = charNew;
            nCount++;
         }
         iChar = strsize((pszBuffer + iChar + 1) - pszBuffer);
      }
      if (bCopied)
      {
         release_string_buffer(nLength);
      }
   }

   return(nCount);
}

//template < typename TYPE_CHAR >
//strsize string_base < TYPE_CHAR >::xxx_replace(CHAR_TYPE charOld, CHAR_TYPE charNew, strsize iStart)
//{
//
//   return replace_with(charNew, charOld, iStart);
//
//}


template < typename TYPE_CHAR >
template < raw_pointer_castable < TYPE_CHAR > PCHARNEW, raw_pointer_castable < TYPE_CHAR > PCHAROLD >
strsize string_base < TYPE_CHAR >::replace_with(PCHARNEW pszNew, PCHAROLD pszOld, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   // nSourceLen is in XCHARs
   strsize nSourceLen = ::str::string_safe_length(pszOld);
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = ::str::string_safe_length(pszNew);

   // loop once to figure out the size_i32 of the result string_base < TYPE_CHAR >
   strsize nCount = 0;
   {
      const CHAR_TYPE* pszStart = data() + iStart;
      //      const CHAR_TYPE * pszEnd = pszStart+get_length();
      const CHAR_TYPE* pszTarget;
      while ((pszTarget = ::str::string_find_string(pszStart, pszOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHAR_TYPE* pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHAR_TYPE* pszStart = pszBuffer + iStart;
      CHAR_TYPE* pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {
         CHAR_TYPE* pszTarget;
         while ((pszTarget = (CHAR_TYPE *) ::str::string_find_string(pszStart, pszOld)) != nullptr)
         {
            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHAR_TYPE));
            memcpy(pszTarget, pszNew, nReplacementLen * sizeof(CHAR_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);
         }
         pszStart += ::str::string_safe_length(pszStart) + 1;
      }
      ASSERT(pszBuffer[nNewLength] == 0);
      release_string_buffer(nNewLength);
   }

   return(nCount);
}


template < typename TYPE_CHAR >
template < raw_pointer_castable < TYPE_CHAR > PCHARNEW, raw_pointer_castable < TYPE_CHAR > PCHAROLD >
strsize string_base < TYPE_CHAR >::replace_with_ci(PCHARNEW pszOld, PCHAROLD pszNew, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   // nSourceLen is in XCHARs
   strsize nSourceLen = ::str::string_safe_length(pszOld);
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = ::str::string_safe_length(pszNew);

   // loop once to figure out the size_i32 of the result string_base < TYPE_CHAR >
   strsize nCount = 0;
   {
      const CHAR_TYPE * pszStart = data() + iStart;
      //      const CHAR_TYPE * pszEnd = pszStart+get_length();
      const CHAR_TYPE * pszTarget;
      while ((pszTarget = ::str::string_find_string_ci(pszStart, pszOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHAR_TYPE * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHAR_TYPE * pszStart = pszBuffer + iStart;
      CHAR_TYPE * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {
         CHAR_TYPE * pszTarget;
         while ((pszTarget = (CHAR_TYPE *)::str::string_find_string_ci(pszStart, pszOld)) != nullptr)
         {
            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHAR_TYPE));
            memcpy(pszTarget, pszNew, nReplacementLen * sizeof(CHAR_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);
         }
         pszStart += ::str::string_safe_length(pszStart) + 1;
      }
      ASSERT(pszBuffer[nNewLength] == 0);
      release_string_buffer(nNewLength);
   }

   return(nCount);
}

template < typename TYPE_CHAR >
template < raw_pointer_castable < TYPE_CHAR > PCHARNEW, raw_pointer_castable < TYPE_CHAR > PCHAROLD >
::count string_base < TYPE_CHAR >::replace_with_count(PCHARNEW pszOld, PCHAROLD pszNew, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   ::count c = 0;

   // nSourceLen is in XCHARs
   strsize nSourceLen = ::str::string_safe_length(pszOld);
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = ::str::string_safe_length(pszNew);

   // loop once to figure out the size_i32 of the result string_base < TYPE_CHAR >
   strsize nCount = 0;
   {
      const CHAR_TYPE* pszStart = data() + iStart;
      //      const CHAR_TYPE * pszEnd = pszStart+get_length();
      const CHAR_TYPE* pszTarget;
      while ((pszTarget = ::str::string_find_string(pszStart, pszOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
         c++;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHAR_TYPE* pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      const CHAR_TYPE* pszStart = pszBuffer + iStart;
      const CHAR_TYPE* pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHAR_TYPE* pszTarget;

         while ((pszTarget = (CHAR_TYPE *) ::str::string_find_string(pszStart, pszOld)) != nullptr)
         {

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove((void *) (pszTarget + nReplacementLen), pszTarget + nSourceLen, nBalance * sizeof(CHAR_TYPE));

            memcpy((void *) pszTarget, pszNew, nReplacementLen * sizeof(CHAR_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += ::str::string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return c;

}


template < typename TYPE_CHAR >
template < raw_pointer_castable < TYPE_CHAR > PCHARNEW, raw_pointer_castable < TYPE_CHAR > PCHAROLD >
::count string_base < TYPE_CHAR >::replace_with_ci_count(PCHARNEW pszOld, PCHAROLD pszNew, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   ::count c = 0;

   // nSourceLen is in XCHARs
   strsize nSourceLen = ::str::string_safe_length(pszOld);
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = ::str::string_safe_length(pszNew);

   // loop once to figure out the size_i32 of the result string_base < TYPE_CHAR >
   strsize nCount = 0;
   {
      const CHAR_TYPE * pszStart = data() + iStart;
      //      const CHAR_TYPE * pszEnd = pszStart+get_length();
      const CHAR_TYPE * pszTarget;
      while ((pszTarget = ::str::string_find_string_ci(pszStart, pszOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
         c++;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHAR_TYPE * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHAR_TYPE * pszStart = pszBuffer + iStart;
      CHAR_TYPE * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHAR_TYPE * pszTarget;

         while ((pszTarget = (CHAR_TYPE *) ::str::string_find_string_ci(pszStart, pszOld)) != nullptr)
         {

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHAR_TYPE));

            memcpy(pszTarget, pszNew, nReplacementLen * sizeof(CHAR_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += ::str::string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return c;

}

template < typename TYPE_CHAR >
string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::replace(strsize iStart, strsize nCount, const CHAR_TYPE * psz)
{

   if (nCount < 0)
   {

      return operator = (Left(iStart) + psz);

   }
   else
   {

      return operator = (Left(iStart) + psz + Mid(nCount));

   }

}


template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::replace(strsize iStart, strsize nCount, const CHAR_TYPE * psz, strsize nSubLen)
{

   if (nCount < 0)
   {

      return operator = (Left(iStart) + string_base < TYPE_CHAR >(psz, nSubLen));

   }
   else
   {

      return operator = (Left(iStart) + string_base < TYPE_CHAR >(psz, nSubLen) + Mid(nCount));

   }

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::erase_character(CHAR_TYPE chRemove)
{

   strsize nLength = get_length();

   CHAR_TYPE* pszBuffer = get_string_buffer(nLength);

   CHAR_TYPE* pszSource = pszBuffer;

   CHAR_TYPE* pszDest = pszBuffer;

   CHAR_TYPE* pszEnd = pszBuffer + nLength;

   while (pszSource < pszEnd)
   {
      CHAR_TYPE* pszNewSource = pszSource + 1;
      if (*pszSource != chRemove)
      {
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         size_t NewSourceGap = (pszNewSource - pszSource);
         CHAR_TYPE* pszNewDest = pszDest + NewSourceGap;
         size_t i = 0;
         for (i = 0; pszDest != pszNewDest && i < NewSourceGap; i++)
         {
            *pszDest = *pszSource;
            pszSource++;
            pszDest++;
         }
      }
      pszSource = pszNewSource;
   }
   *pszDest = 0;
   strsize nCount = strsize(pszSource - pszDest);
   release_string_buffer(nLength - nCount);

   return(nCount);

}

// find the first occurrence of character 'ch', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find(CHAR_TYPE ch) const RELEASENOTHROW
{

   auto psz = ::str::string_find_char(this->m_pdata, ch);

   if (!psz)
   {

      return -1;

   }

   return psz - this->m_pdata;

}



template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find(CHAR_TYPE ch, strsize start) const RELEASENOTHROW
{

   auto psz = ::str::string_find_char(this->m_pdata + start, ch);

   if (!psz)
   {

      return -1;

   }

   return psz - this->m_pdata;

}

// find routines

// find the first occurrence of character 'ch', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find(CHAR_TYPE ch, strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart >= nLength)
   {
      return -1;
   }

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart > nLength)
      nCount = nLength - iStart;

   if (nCount < 0)
      return -1;

   const CHAR_TYPE* psz = data() + iStart;
   for (i32 i = 0; i < nCount; i++)
   {
      if (psz[i] == ch)
      {
         return iStart + i;
      }
   }
   return -1;
}

// find the first occurrence of character 'ch', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_ci(CHAR_TYPE ch, strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart >= nLength)
   {
      return(-1);
   }

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart > nLength)
      nCount = nLength - iStart;

   if (nCount < 0)
      return -1;

   const CHAR_TYPE* psz = data() + iStart;
   for (i32 i = 0; i < nCount; i++)
   {
      if (tolower(psz[i]) == tolower(ch))
      {
         return iStart + i;
      }
   }
   return -1;
}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_whitespace_or_length(strsize iStart) const RELEASENOTHROW
{

   if (iStart >= get_length())
   {

      return get_length();

   }

   strsize iFound = find_first_in("\t\n\r ", iStart);

   if (iFound < 0)
   {

      return get_length();

   }

   return iFound;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_of(CHAR_TYPE ch, strsize iStart) const RELEASENOTHROW
{
   return find(ch, iStart);
}
// look for a specific sub-string_base < TYPE_CHAR >

// find the first occurrence of string_base < TYPE_CHAR > 'pszSub', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find(const CHAR_TYPE* pszSub, strsize iStart, strsize nCount, const CHAR_TYPE** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {
      return(-1);
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart > nLength)
   {
      return(-1);
   }

   strsize nLength2 = ::str::string_get_length(pszSub);

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart + nLength2 > nLength)
      nCount = nLength - iStart - nLength2;

   if (nCount < 0)
      return -1;

   const CHAR_TYPE* psz = data() + iStart;
   for (i32 i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      i32 j;
      for (j = 0; j < nLength2; j++)
      {
         if (psz[j] != pszSub[j])
         {
            bFound = false;
            break;
         }
      }
      if (bFound && j == nLength2)
      {
         if (pszTail)
            *pszTail = &psz[j];
         return i + iStart;
      }
      psz++;
   }
   return -1;
}

// find the first occurrence of string_base < TYPE_CHAR > 'pszSub', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_ci(const CHAR_TYPE* pszSub, strsize iStart, strsize nCount, const CHAR_TYPE** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {
      return(-1);
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart > nLength)
   {
      return(-1);
   }

   strsize nLength2 = ::str::string_get_length(pszSub);

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart + nLength2 > nLength)
      nCount = nLength - iStart - nLength2;

   if (nCount < 0)
      return -1;

   i32 j;

   const CHAR_TYPE* psz = data() + iStart;
   for (i32 i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      for (j = 0; j < nLength2; j++)
      {
         if (tolower(psz[j]) != tolower(pszSub[j]))
         {
            bFound = false;
            break;
         }
      }
      if (bFound)
      {
         if (pszTail)
            *pszTail = &psz[j];
         return i + iStart;
      }
      psz++;
   }
   return -1;
}

// find the first occurrence of string_base < TYPE_CHAR > 'pszSub', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_w(const CHAR_TYPE * pszSub, strsize iStart, strsize nCount, const CHAR_TYPE ** pszTail) const RELEASENOTHROW
{

   // iStart is in XCHARs

   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {
      return(-1);
   }

   if (iStart < 0)
      return -1;

   const CHAR_TYPE* psz = data() + iStart;

   if (*psz == '\0')
      return -1;
   while (*psz != '\0' && (psz - data() - iStart) < nCount)
   {
      bool bFound = true;
      const CHAR_TYPE* psz2 = psz;
      const CHAR_TYPE* pszSub2 = pszSub;
      strsize len1;
      strsize len2;
      while (*psz2 != '\0' && *pszSub2 != '\0')
      {
         if (::str::uni_index(psz2, &len1) != ::str::uni_index(pszSub2, &len2))
         {
            bFound = false;
            break;
         }
         //psz2 = ::str::uni_inc(psz2);
         psz2 += len1;
         //pszSub2 = ::str::uni_inc(pszSub2);
         pszSub2 += len2;
      }
      if (bFound)
      {
         if (*pszSub2 == '\0')
         {
            if (pszTail)
               *pszTail = psz2;
            return psz - data();
         }
         else
         {
            return -1;
         }
      }
      psz++;
   }
   return -1;
}


// find the first occurrence of string_base < TYPE_CHAR > 'pszSub', starting at strsize 'iStart'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_wci(const CHAR_TYPE* pszSub, strsize iStart, strsize nCount, const CHAR_TYPE** pszTail) const RELEASENOTHROW
{

   // iStart is in XCHARs
   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {

      return -1;

   }

   if (iStart < 0)
   {

      return -1;

   }

   const CHAR_TYPE* psz = data() + iStart;

   if (*psz == '\0')
   {

      return -1;

   }

   while (*psz != '\0' && (psz - data() - iStart) < nCount)
   {

      bool bFound = true;

      const CHAR_TYPE* psz2 = psz;

      const CHAR_TYPE* pszSub2 = pszSub;

      strsize len1;

      strsize len2;

      while (*psz2 != '\0' && *pszSub2 != '\0')
      {

         if (::str::ch::to_lower_case(::str::uni_index(psz2, &len1)) !=
            ::str::ch::to_lower_case(::str::uni_index(pszSub2, &len2)))
         {

            bFound = false;

            break;

         }

         psz2 += len1;

         psz2 += len2;

      }

      if (bFound)
      {

         if (*pszSub2 == '\0')
         {

            if (pszTail)
            {

               *pszTail = psz2;

            }

            return psz - data();

         }
         else
         {

            return -1;

         }

      }

      psz++;

   }

   return -1;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_tail(const CHAR_TYPE* pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHAR_TYPE* pszTail = nullptr;

   if (find(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_w_tail(const CHAR_TYPE* pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHAR_TYPE* pszTail = nullptr;

   if (find_w(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_ci_tail(const CHAR_TYPE* pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHAR_TYPE* pszTail = nullptr;

   if (find_ci(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_wci_tail(const CHAR_TYPE* pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHAR_TYPE* pszTail = nullptr;

   if (find_wci(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


// find the first occurrence of any of the characters in string_base < TYPE_CHAR > 'pszCharSet'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::FindOneOf(const CHAR_TYPE* pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{

   string_base < TYPE_CHAR > strCharSet(pszCharSet, n);

   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();

   if (iStart < 0 || iStart >= nLength)
   {

      return -1;

   }

   const CHAR_TYPE* psz = ::str::string_scan_set(&data()[iStart], strCharSet);

   return((psz == nullptr) ? -1 : strsize(psz - data()));

}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_of(const CHAR_TYPE* pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return FindOneOf(pszCharSet, iStart, -1);
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_of(const CHAR_TYPE* pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{
   return FindOneOf(pszCharSet, iStart, n);
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_of(const string_base < TYPE_CHAR >& strCharSet, strsize pos) const RELEASENOTHROW
{
   return FindOneOf(strCharSet, pos, strCharSet.get_length());
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_not_of(const string_base < TYPE_CHAR >& str, strsize pos) const
RELEASENOTHROW
{
   return find_first_not_of(str, pos, str.get_length());
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_not_of(const CHAR_TYPE* s, strsize pos) const
RELEASENOTHROW
{
   return find_first_not_of(s, pos, ::str::string_get_length(s));
}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_not_of(CHAR_TYPE ca, strsize pos) const
RELEASENOTHROW
{
   strsize nLength = get_length();

   if (pos < 0 || pos >= nLength)
      return -1;
   const CHAR_TYPE* psz = &data()[pos];
   while (*psz != '\0' && *psz == ca)
   {
      psz++;
   }
   if (*psz == '\0')
      return -1;
   else
      return psz - data();
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_first_not_of(const CHAR_TYPE* s, strsize pos, strsize n) const
RELEASENOTHROW
{
   string_base < TYPE_CHAR > strChars(s, n);

   strsize nLength = get_length();

   if (pos < 0 || pos >= nLength)
      return -1;
   const CHAR_TYPE* psz = &data()[pos];
   while (*psz != '\0' && strChars.contains(*psz))
   {
      psz++;
   }
   if (*psz == '\0')
      return -1;
   else
      return psz - data();
}


// find the first occurrence of any of the characters in string_base < TYPE_CHAR > 'pszCharSet'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_of(CHAR_TYPE ca, strsize pos) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   const CHAR_TYPE* psz = data();
   while (pos >= 0 && psz[pos] != ca)
   {
      pos--;
   }
   return pos;
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_of(const CHAR_TYPE* pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return find_last_of(pszCharSet, iStart, -1);
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_of(const CHAR_TYPE* pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   string_base < TYPE_CHAR > strChars(pszCharSet, n);
   const CHAR_TYPE* psz = data();
   while (pos >= 0 && !strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_of(const string_base < TYPE_CHAR >& strCharSet, strsize pos) const RELEASENOTHROW
{
   return find_last_of(strCharSet, pos, strCharSet.get_length());
}


// find the first occurrence of any of the characters in string_base < TYPE_CHAR > 'pszCharSet'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_not_of(CHAR_TYPE ca, strsize pos) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   const CHAR_TYPE* psz = data();
   while (pos >= 0 && psz[pos] == ca)
   {
      pos--;
   }
   return pos;
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_not_of(const CHAR_TYPE* pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return find_last_not_of(pszCharSet, iStart, -1);
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_not_of(const CHAR_TYPE* pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   string_base < TYPE_CHAR > strChars(pszCharSet, n);
   const CHAR_TYPE* psz = data();
   while (pos >= 0 && strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::find_last_not_of(const string_base < TYPE_CHAR >& strCharSet, strsize pos) const RELEASENOTHROW
{
   return find_last_not_of(strCharSet, pos, strCharSet.get_length());
}


// find the last occurrence of character 'ch'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::reverse_find(CHAR_TYPE ch, strsize iStart) const RELEASENOTHROW
{
   // find last single character
   const CHAR_TYPE* psz = ::str::string_find_char_reverse(data(), ch, iStart);

   // return -1 if not found, distance from beginning otherwise
   return((psz == nullptr) ? -1 : strsize(psz - data()));
}

template < typename TYPE_CHAR >
TYPE_CHAR string_base < TYPE_CHAR >::last_char(strsize count) const
{

   return *(this->m_pdata + length() + count);
}



// find the last occurrence of character 'ch'
template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::reverse_find(const CHAR_TYPE* ch, strsize iStart) const RELEASENOTHROW
{
   // find last single character
   const CHAR_TYPE* psz = ::str::string_find_string_reverse(data(), ch, iStart);

   // return -1 if not found, distance from beginning otherwise
   return((psz == nullptr) ? -1 : strsize(psz - data()));
}

// manipulation

// Convert the string_base < TYPE_CHAR > to uppercase
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::make_upper()
{
   strsize nLength = get_length();
   CHAR_TYPE* pszBuffer = get_string_buffer(nLength);
   ::str::string_uppercase(pszBuffer, nLength + 1);
   release_string_buffer(nLength);

   return *this;
}

// Convert the string_base < TYPE_CHAR > to lowercase
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::make_lower()
{
   strsize nLength = get_length();
   CHAR_TYPE* pszBuffer = get_string_buffer(nLength);
   ::str::string_lowercase(pszBuffer, nLength + 1);
   release_string_buffer(nLength);

   return *this;
}

// Reverse the string_base < TYPE_CHAR >
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::MakeReverse()
{
   strsize nLength = get_length();
   CHAR_TYPE* pszBuffer = get_string_buffer(nLength);
   ::str::string_reverse(pszBuffer);
   release_string_buffer(nLength);

   return *this;
}

// trimming

// erase all trailing whitespace
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_right()
{

   const CHAR_TYPE* pszLast = nullptr;
   const CHAR_TYPE* pszMax = data() + get_length();
   const CHAR_TYPE* psz = pszMax;

   if (psz != nullptr)
   {

      while (true)
      {

         psz = ::str::uni_dec(data(), psz);

         if (psz < data())
         {

            break;

         }

         if (!::str::ch::is_whitespace(psz))
         {

            pszLast = ::str::uni_inc(psz);

            break;

         }

      }

   }

   if (pszLast != nullptr && pszLast < pszMax)
   {

      // truncate at trailing space iStart

      strsize iLast = strsize(pszLast - data());

      truncate(iLast);

   }

   return *this;

}

// erase all leading whitespace
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_left()
{
   // find first non-space character

   const CHAR_TYPE* psz = data();

   strsize iHere;

   while (::str::ch::is_whitespace(psz))
   {

      psz = ::str::char_next(psz);

      iHere = (strsize)(psz - data());

      if (iHere >= get_length())
      {

         if (iHere == get_length())
         {

            break;

         }
         else
         {

            return *this;

         }


      }

   }


   if (psz != data())
   {
      // fix up data and length
      strsize iFirst = strsize(psz - data());

      CHAR_TYPE* pszBuffer = get_string_buffer(get_length());

      psz = pszBuffer + iFirst;

      strsize nDataLength = get_length() - iFirst;

      memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHAR_TYPE));

      release_string_buffer(nDataLength);

   }

   return *this;
}

// erase all leading and trailing whitespace
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim()
{
   return(trim_right().trim_left());
}

// erase all leading and trailing occurrences of character 'chTarget'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim(CHAR_TYPE chTarget)
{
   return(trim_right(chTarget).trim_left(chTarget));
}

// erase all leading and trailing occurrences of any of the characters in the string_base < TYPE_CHAR > 'pszTargets'
template < typename TYPE_CHAR >
template < raw_pointer_castable < TYPE_CHAR > PCHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim(PCHAR szTargets)
{
   return(trim_right(szTargets).trim_left(szTargets));
}

// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_right(CHAR_TYPE chTarget)
{
   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   const CHAR_TYPE* psz = data();
   const CHAR_TYPE* pszLast = nullptr;

   while (*psz != 0)
   {
      if (*psz == chTarget)
      {
         if (pszLast == nullptr)
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = nullptr;
      }
      psz = ::str::char_next(psz);
   }

   if (pszLast != nullptr)
   {
      // truncate at left-most matching character
      strsize iLast = strsize(pszLast - data());
      truncate(iLast);
   }

   return *this;

}


// erase all trailing occurrences of any of the characters in string_base < TYPE_CHAR > 'pszTargets'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_right(const CHAR_TYPE * szTargets)
//template < pointer_castable < TYPE_CHAR > PCHAR>
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_right(PCHAR szTargets)
{

   const CHAR_TYPE * pszTargets = szTargets;

   // if we're not trimming anything, we're not doing any work
   if ((pszTargets == nullptr) || (*pszTargets == 0))
   {
      return *this;
   }

   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   const CHAR_TYPE* psz = data();
   const CHAR_TYPE* pszStart = psz;
   const CHAR_TYPE* pszLast = nullptr;

   while (!is_ptr_null(psz, 1024) && *psz != 0)
   {
      if (::str::string_find_char(pszTargets, *psz) != nullptr)
      {
         if (pszLast == nullptr)
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = nullptr;
      }
      psz = ::str::char_next(psz);
   }

   if (pszLast != nullptr)
   {
      // truncate at left-most matching character
      strsize iLast = strsize(pszLast - pszStart);
      truncate(iLast);
   }

   return *this;

}


// erase all leading occurrences of character 'chTarget'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_left(CHAR_TYPE chTarget)
{
   // find first non-matching character
   const CHAR_TYPE* psz = data();

   while (chTarget == *psz)
   {
      psz = ::str::char_next(psz);
   }

   if (psz != data())
   {
      // fix up data and length
      strsize iFirst = strsize(psz - data());
      CHAR_TYPE* pszBuffer = get_string_buffer(get_length());
      psz = pszBuffer + iFirst;
      strsize nDataLength = get_length() - iFirst;
      memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHAR_TYPE));
      release_string_buffer(nDataLength);
   }

   return *this;
}

// erase all leading occurrences of any of the characters in string_base < TYPE_CHAR > 'pszTargets'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_left(const CHAR_TYPE * szTargets)
//template < pointer_castable < TYPE_CHAR > PCHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::trim_left(PCHAR szTargets)
{

   const CHAR_TYPE * pszTargets = szTargets;

   // if we're not trimming anything, we're not doing any work
   if ((pszTargets == nullptr) || (*pszTargets == 0))
   {
      return *this;
   }

   const CHAR_TYPE* psz = data();
   while ((*psz != 0) && (::str::string_find_char(pszTargets, *psz) != nullptr))
   {
      psz = ::str::char_next(psz);
   }

   if (psz != data())
   {
      // fix up data and length
      strsize iFirst = strsize(psz - data());
      CHAR_TYPE* pszBuffer = get_string_buffer(get_length());
      psz = pszBuffer + iFirst;
      strsize nDataLength = get_length() - iFirst;
      memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHAR_TYPE));
      release_string_buffer(nDataLength);
   }

   return *this;
}


// erase all trailing whitespace
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::right_trimmed() const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim_right();

   return str;

}


// erase all leading whitespace
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::left_trimmed() const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim_left();

   return str;

}


// erase all leading and trailing whitespace
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::trimmed() const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim();

   return str;

}


// erase all leading and trailing occurrences of character 'chTarget'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::trimmed(CHAR_TYPE chTarget) const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim(chTarget);

   return str;

}


// erase all leading and trailing occurrences of any of the characters in the string_base < TYPE_CHAR > 'pszTargets'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::trimmed(const CHAR_TYPE * pszTargets) const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim(pszTargets);

   return str;

}


// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::right_trimmed(CHAR_TYPE chTarget) const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim_right(chTarget);

   return str;

}


// erase all trailing occurrences of any of the characters in string_base < TYPE_CHAR > 'pszTargets'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::right_trimmed(const CHAR_TYPE * pszTargets) const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim_right(pszTargets);

   return str;

}


// erase all leading occurrences of character 'chTarget'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::left_trimmed(CHAR_TYPE chTarget) const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim_left(chTarget);

   return str;

}


// erase all leading occurrences of any of the characters in string_base < TYPE_CHAR > 'pszTargets'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::left_trimmed(const CHAR_TYPE* pszTargets) const
{

   string_base < TYPE_CHAR > str(*this);

   str.trim_left(pszTargets);

   return str;

}

//CLASS_DECL_ACME void __throw_what_exclamation_exclamation(const char * ::payload);


// Convert the string_base < TYPE_CHAR > to the OEM character set
template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::AnsiToOem()
{
   __throw(error_what_exclamation_exclamation, "AnsiToOem WTF AnsiToOem ANSI is already WTF, Oem is very WTF, and what to say about ANSItoOEM");
   //strsize nLength = get_length();
   //CHAR_TYPE* pszBuffer = get_string_buffer(nLength);
   //::str::ConvertToOem(pszBuffer, nLength + 1);
   //release_string_buffer(nLength);
}

// Convert the string_base < TYPE_CHAR > to the ANSI character set
template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::OemToAnsi()
{
   __throw(error_what_exclamation_exclamation, "AnsiToOem WTF AnsiToOem ANSI is already WTF, Oem is very WTF, and what to say about ANSItoOEM Ah?!?! :/ OEMtoANSI, now a bit lesser (or more?) WTF, WHAT?! WTF Power 10!!");
   //strsize nLength = get_length();
   //CHAR_TYPE* pszBuffer = get_string_buffer(nLength);
   //::str::convert_to_ansi(pszBuffer, nLength + 1);
   //release_string_buffer(nLength);
}

// Very simple sub-string_base < TYPE_CHAR > extraction

// Return the substring starting at strsize 'iFirst'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::Mid(strsize iFirst) const
{
   return Mid(iFirst, -1);
}

template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::substr(strsize iFirst) const
{
   return Mid(iFirst);
}

// Return the substring starting at strsize 'iFirst', with length 'nCount'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::Mid(strsize iFirst, strsize nCount) const
{
   // nCount is in XCHARs

   // out-of-bounds requests return sensible things

   strsize nLength = get_length();

   if (iFirst < 0)
      iFirst = 0;

   if (nCount < 0)
      nCount = nLength + nCount + 1;

   if (nCount + iFirst > nLength)
      nCount = nLength - iFirst;

   if (nCount < 0)
      return "";

   if (iFirst + nCount > get_length())
   {

      nCount = get_length() - iFirst;

   }

   if (iFirst > get_length())
   {
      nCount = 0;
   }

   ASSERT((nCount == 0) || ((iFirst + nCount) <= get_length()));

   // optimize case of returning entire string_base < TYPE_CHAR >
   if ((iFirst == 0) && ((iFirst + nCount) == get_length()))
   {
      return *this;
   }

   return(string_base < TYPE_CHAR >(data() + iFirst, nCount));

}


template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::substr(strsize iFirst, strsize nCount) const
{

   return Mid(iFirst, nCount);

}


template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::clear()
{

   Empty();

}


template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::Right(strsize nCount) const
{

   if (nCount < 0)
   {

      nCount = 0;

   }

   strsize nLength = get_length();

   if (nCount >= nLength)
   {

      return *this;

   }

   return(string_base < TYPE_CHAR >(data() + nLength - nCount, nCount));

}


// Return the substring consisting of the leftmost 'nCount' characters
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::Left(strsize nCount) const
{

   // nCount is in XCHARs
   if (nCount < 0)
   {

      nCount = 0;

   }

   strsize nLength = get_length();

   if (nCount >= nLength)
   {

      return *this;

   }

   return(string_base < TYPE_CHAR >(data(), nCount));

}


// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::span_including(const CHAR_TYPE* pszCharSet) const
{

   ASSERT(__is_valid_string(pszCharSet));

   if (pszCharSet == nullptr)
   {

      __throw(error_bad_argument);

   }

   return(Left(::str::string_span_including(data(), pszCharSet)));

}


// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::span_excluding(const CHAR_TYPE* pszCharSet) const
{

   ASSERT(__is_valid_string(pszCharSet));

   if (pszCharSet == nullptr)
   {

      __throw(error_bad_argument);

   }

   return(Left(::str::string_span_excluding(data(), pszCharSet)));

}


template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::append_format_arguments(const CHAR_TYPE* pszFormat, va_list args)
{

   ASSERT(__is_valid_string(pszFormat));

   strsize nCurrentLength = get_length();

   strsize nAppendLength = ::str::get_formatted_length(pszFormat, args);

   CHAR_TYPE* pszBuffer = get_string_buffer(nCurrentLength + nAppendLength);

#if _SECURE_TEMPLATE

   ::str::string_format(pszBuffer + nCurrentLength, nAppendLength + 1, pszFormat, args);

#else

   ::str::string_format(pszBuffer + nCurrentLength, pszFormat, args);

#endif

   release_string_buffer(nCurrentLength + nAppendLength);

}


template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::format_arguments(const CHAR_TYPE* pszFormat, va_list args)
{

   ASSERT(__is_valid_string(pszFormat));

   if (pszFormat == nullptr)
   {

      __throw(error_bad_argument);

   }

   va_list ptr1;

   va_copy(ptr1, args);

   strsize nLength = ::str::get_formatted_length(pszFormat, ptr1);

   va_end(ptr1);

   CHAR_TYPE* pszBuffer = get_string_buffer(nLength);

   va_list ptr2;

   va_copy(ptr2, args);

#if _SECURE_TEMPLATE || defined(LINUX)

   ::str::string_format(pszBuffer, nLength + 1, pszFormat, ptr2);

#else

   ::str::string_format(pszBuffer, pszFormat, ptr2);

#endif

   va_end(ptr2);

   release_string_buffer(nLength);

}


// set the string_base < TYPE_CHAR > to the value of environment ::payload 'pszVar'
// template < typename TYPE_CHAR >
// bool string_base < TYPE_CHAR >::xxxget_environment_variable(const CHAR_TYPE* pszVar)
// {

//    u32 nLength = ::str::xxxget_environment_variable(pszVar, nullptr, 0);

//    bool bRetVal = false;

//    if (nLength == 0)
//    {

//       Empty();

//    }
//    else
//    {

//       CHAR_TYPE* pszBuffer = get_string_buffer(nLength);

//       ::str::xxxget_environment_variable(pszVar, pszBuffer, nLength);

//       release_string_buffer();

//       bRetVal = true;

//    }

//    return(bRetVal);

// }


// template < typename TYPE_CHAR >
// bool string_base < TYPE_CHAR >::xxxgetenv(const CHAR_TYPE* pszVar)
// {

//    return xxxget_environment_variable(pszVar);

// }


#ifndef _CSTRING_BUFFER_SIZE
#define _CSTRING_BUFFER_SIZE(_CStringObj) ((_CStringObj).GetAllocLength() + 1)
#endif


template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::format(const CHAR_TYPE * pszFormat, ...)
{

   ASSERT(__is_valid_string(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   format_arguments(pszFormat, argList);

   va_end(argList);

}


// append formatted data using format string_base < TYPE_CHAR > 'pszFormat'
template < typename TYPE_CHAR >
void __cdecl string_base < TYPE_CHAR >::append_format(const CHAR_TYPE* pszFormat, ...)
{

   ASSERT(__is_valid_string(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   append_format_arguments(pszFormat, argList);

   va_end(argList);

}


template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::reserve(strsize res_arg)
{
   get_string_buffer(res_arg + 1);
}



// Convert the string_base < TYPE_CHAR > to uppercase
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::uppered() const
{

   return string_base < TYPE_CHAR >(*this).make_upper();

}

// Convert the string_base < TYPE_CHAR > to lowercase
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::lowered() const
{

   return string_base < TYPE_CHAR >(*this).make_lower();

}

// Convert the string_base < TYPE_CHAR > to lowercase
template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::reversed() const
{

   return string_base < TYPE_CHAR >(*this).MakeReverse();

}


template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::unichar_substr(strsize iFirst) const
{

   return unichar_substr(iFirst, -1);

}


template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::unichar_substr(strsize iFirst, strsize nCount) const
{

   const CHAR_TYPE* pchStart = *this;

   if (pchStart == nullptr)
      return "";

   ::count iUtf8Len = unichar_count();

   if (iFirst < 0)
      iFirst = iUtf8Len + iFirst;

   if (nCount < 0)
      nCount = iUtf8Len - iFirst + nCount + 1;

   if (iFirst + nCount > iUtf8Len)
      nCount = iUtf8Len - iFirst;

   if (nCount <= 0)
      return "";

   ::count ca = 0;

   while (ca < iFirst && *pchStart != '\0')
   {

      pchStart = ::str::uni_inc(pchStart);

      ca++;

   }

   if (*pchStart == '\0')
      return "";

   const CHAR_TYPE* pchEnd = pchStart;

   ca = 0;

   while (ca < nCount && *pchEnd != '\0')
   {

      pchEnd = ::str::uni_inc(pchEnd);

      ca++;

   }

   return string_base < TYPE_CHAR >(pchStart, pchEnd - pchStart);


}

//template < typename TYPE_CHAR >
//::count string_base < TYPE_CHAR >::unichar_count() const
//{
//
//   const CHAR_TYPE* pch = *this;
//
//   if (pch == nullptr)
//      return 0;
//
//   ::count cCharCount = 0;
//
//   while (pch != nullptr && *pch != '\0')
//   {
//
//      pch = ::str::__utf8_inc(pch);
//
//      cCharCount++;
//
//   }
//
//   return cCharCount;
//
//}


template < typename TYPE_CHAR >
strsize string_base < TYPE_CHAR >::char_type_count(strsize iUnicharCount) const
{

   strsize iFinalLen = 0;

   auto psz = operator const CHAR_TYPE* ();

   strsize cMaxLen = get_length();

   while (iUnicharCount > 0)
   {

      auto iLen = __uni_len(psz);

      psz += iLen;

      iFinalLen += iLen;

      if (iFinalLen >= cMaxLen)
      {

         return cMaxLen;

      }

      iUnicharCount--;

   }

   return iFinalLen;

}



template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::eat_before(string_base < TYPE_CHAR >& strBefore, string_base < TYPE_CHAR > strSeparator, bool bEatEverythingIfNotFound)
{

   return ::str::eat_before(strBefore, strSeparator, *this, bEatEverythingIfNotFound);

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::eat_before_let_separator(string_base < TYPE_CHAR >& strBefore, string_base < TYPE_CHAR > strSeparator, bool bEatEverythingIfNotFound)
{

   return ::str::eat_before_let_separator(strBefore, strSeparator, *this, bEatEverythingIfNotFound);

}


template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::push_back(CHAR_TYPE ch)
{

   operator += (ch);

}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::operator = (const ::string_stream& str)
//{
//
//   return this->operator =(str.operator const string_base < TYPE_CHAR > & ());
//
//}
//















template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins(const string_base& str) const
{

   return ::str::begins(*this, str);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends(const string_base& str) const
{

   return ::str::ends(*this, str);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_ci(const string_base& str) const
{

   return ::str::begins_ci(*this, str);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_ci(const string_base& str) const
{

   return ::str::ends_ci(*this, str);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_eat(const string_base& strPrefix)
{

   return ::str::begins_eat(*this, strPrefix);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_eat(const string_base& strPrefix)
{

   return ::str::ends_eat(*this, strPrefix);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_eat_ci(const string_base& strPrefix)
{

   return ::str::begins_eat_ci(*this, strPrefix);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_eat_ci(const string_base& strPrefix)
{

   return ::str::ends_eat_ci(*this, strPrefix);

}




template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >& string_base < TYPE_CHAR > ::ensure_begins(const string_base& strPrefix)
{

   if (!begins(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >& string_base < TYPE_CHAR > ::ensure_begins_ci(const string_base& strPrefix)
{

   if (!begins_ci(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >& string_base < TYPE_CHAR > ::ensure_ends(const string_base& strPrefix)
{

   if (!ends(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >& string_base < TYPE_CHAR > ::ensure_ends_ci(const string_base& strPrefix)
{

   if (!ends_ci(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}























template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins(const CHAR_TYPE * psz) const
{

   return ::str::begins(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends(const CHAR_TYPE* psz) const
{

   return ::str::ends(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_ci(const CHAR_TYPE* psz) const
{

   return ::str::begins_ci(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_ci(const CHAR_TYPE* psz) const
{

   return ::str::ends_ci(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_eat(const CHAR_TYPE* psz)
{

   return ::str::begins_eat(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_eat(const CHAR_TYPE* psz)
{

   return ::str::ends_eat(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_eat_ci(const CHAR_TYPE* psz)
{

   return ::str::begins_eat_ci(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_eat_ci(const CHAR_TYPE* psz)
{

   return ::str::ends_eat_ci(*this, psz);

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_eaten(string_base & strEaten, const CHAR_TYPE * psz)
{

   if (!::str::begins(*this, psz))
   {

      return false;

   }

   strEaten = c_str() + ::str::length(psz);

   return true;

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_eaten(string_base & strEaten, const CHAR_TYPE * psz)
{

   if (!::str::begins(*this, psz))
   {

      return false;

   }

   strEaten = string(c_str(), length()- ::str::length(psz));

   return true;

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::begins_eaten_ci(string_base & strEaten, const CHAR_TYPE * psz)
{

   if (!::str::begins_ci(*this, psz))
   {

      return false;

   }

   strEaten = c_str() + ::str::length(psz);

   return true;

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR > ::ends_eaten_ci(string_base & strEaten, const CHAR_TYPE * psz)
{

   if (!::str::begins(*this, psz))
   {

      return false;

   }

   strEaten = string(c_str(), length() - ::str::length(psz));

   return true;

}



template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR > ::ensure_begins(const CHAR_TYPE* psz)
{

   if (!begins(psz))
   {

      operator =(string_base(psz) + *this);

   }

   return *this;

}

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR > ::ensure_begins_ci(const CHAR_TYPE* psz)
{

   if (!begins_ci(psz))
   {

      operator =(string_base(psz) + *this);

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR > ::ensure_ends(const CHAR_TYPE* psz)
{

   if (!ends(psz))
   {

      operator =(string_base(psz) + *this);

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR > ::ensure_ends_ci(const CHAR_TYPE* psz)
{

   if (!ends_ci(psz))
   {

      operator =(string(psz) + *this);

   }

   return *this;

}













template < typename CHAR_TYPE >
void CopyCharsOverlapped(CHAR_TYPE * pchDest, const CHAR_TYPE * pchSrc, strsize nChars) noexcept
{
   __memmov(pchDest, pchSrc, nChars * sizeof(CHAR_TYPE));
}

template < typename CHAR_TYPE >
void CopyCharsOverlapped(CHAR_TYPE * pchDest, size_t nDestLen, const CHAR_TYPE * pchSrc, strsize nChars) noexcept
{
   __memmov(pchDest, pchSrc, nChars * sizeof(CHAR_TYPE));
}



template < typename STRING >
inline STRING & string_concatenate(STRING & str, const typename STRING::CHAR_TYPE * psz1, strsize nLength1, const typename STRING::CHAR_TYPE * psz2, strsize nLength2)
{

   strsize nNewLength = nLength1 + nLength2;

   typename STRING::CHAR_TYPE * pszBuffer = str.get_string_buffer(nNewLength);

   ::str::copy_chars(pszBuffer, psz1, nLength1);

   ::str::copy_chars(pszBuffer + nLength1, psz2, nLength2);

   str.release_string_buffer(nNewLength);

   return str;

}


template < typename STRING >
inline bool string_ends_eat(STRING & ansistr, const STRING & strSuffix)
{

   auto lenSuffix = strSuffix.length();

   if (lenSuffix > ansistr.length())
   {

      return false;

   }

   if (STRING::string_n_compare(ansistr.reverse_ptr_at(lenSuffix), strSuffix, lenSuffix) != 0)
   {

      return false;

   }

   ansistr.reverse_truncate(lenSuffix);

   return true;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const ansichar * pansichar)
{

   ::str::assign(*this, pansichar);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const wd16char * pwd16char)
{

   ::str::assign(*this, pwd16char);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const wd32char * pwd32char)
{

   ::str::assign(*this, pwd32char);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const ansichar * pszSrc, strsize nLength)
{

   ::str::assign(*this, pszSrc, nLength);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const wd16char * pwszSrc, strsize nLength)
{

   ::str::assign(*this, pwszSrc, nLength);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const wd32char * pwszSrc, strsize nLength)
{

   ::str::assign(*this, pwszSrc, nLength);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(ansichar ansich, strsize repeat)
{

   assign(ansich, repeat);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(wd16char wd16ch, strsize repeat)
{

   assign(wd16ch, repeat);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(wd32char wd32ch, strsize repeat)
{

   assign(wd32ch, repeat);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR >::unichar_count() const
{

   return ::str::unichar_count(c_str());

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator = (const natural_ansistring & ansistrSrc)
//{
//
//   return ::str::assign(*this, ansistrSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const natural_wd16string & wd16strSrc)
//{
//
//   return ::str::assign(*this, wd16strSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const natural_wd32string & wd32strSrc)
//{
//
//   return ::str::assign(*this, wd32strSrc.m_pdata);
//
//}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator = (const string_base & str)
{

   return assign(str);

   //return *this;

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const wd16string & wd16str)
//{
//
//   return ::str::assign(*this, wd16str.c_str());
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const wd32string & wd32str)
//{
//
//   return ::str::assign(*this, wd32str.c_str());
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const ansichar * pansichar)
//{
//
//   return ::str::assign(*this, pansichar);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const wd16char * pwd16char)
//{
//
//   return ::str::assign(*this, pwd16char);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const wd32char * pwd32char)
//{
//
//   return ::str::assign(*this, pwd32char);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(ansichar ansich)
//{
//
//   return ::str::assign(*this, ansich);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(wd16char wd16ch)
//{
//
//   return ::str::assign(*this, wd16ch);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(wd32char wd32ch)
//{
//
//   return ::str::assign(*this, wd32ch);
//
//}
//
//
//template < typename TYPE_CHAR >
//template < int t_nSize >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator =(const static_string<CHAR_TYPE, t_nSize > & ansistrSrc)
//{
//
//   assign(ansistrSrc);
//
//   return *this;
//
//}

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const string_base & str)
{

   return append(str);

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const ansistring & ansistrSrc)
//{
//
//   return append(ansistrSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const wd16string & wd16strSrc)
//{
//
//   return append(wd16strSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const wd32string & wd32strSrc)
//{
//
//   return append(wd32strSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const ansichar * pszSrc)
//{
//
//   return append(pszSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const wd16char * pszSrc)
//{
//
//   return append(pszSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const wd32char * pszSrc)
//{
//
//   return append(pszSrc);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(ansichar ansich)
//{
//
//   return append(ansich);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(wd16char wd16ch)
//{
//
//   return append(wd16ch);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(wd32char wd32ch)
//{
//
//   return append(wd32ch);
//
//}


//template < typename TYPE_CHAR >
//template < int t_nSize >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const static_string<CHAR_TYPE, t_nSize > & ansistrSrc)
//{
//
//   return append(ansistrSrc);
//
//}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(ansichar ansich) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += ansich;

   //string_concatenate(ansistr, this->c_str(), this->length(), &ch, 1);

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(wd16char wd16ch) const
{

   string_base < TYPE_CHAR > ansistr;

   ansistr.append(wd16ch);

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(wd32char wd32ch) const
{

   string_base < TYPE_CHAR > ansistr;

   ansistr.append(wd32ch);

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const ansichar * psz) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += psz;

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const wd16char * pwsz) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += pwsz;

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const wd32char * pwsz) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += pwsz;

   return ansistr;

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const string_base & strAddUp) const
//{
//
//   string_base < TYPE_CHAR > ansistr(*this);
//
//   ansistr += strAddUp;
//
//   return ansistr;
//
//}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const ansistring & strAddUp) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += strAddUp;

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const wd16string & wstrAddUp) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += wstrAddUp;

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const wd32string & wstrAddUp) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += wstrAddUp;

   return ansistr;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >& string_base < TYPE_CHAR >::assign(const string_base & str)
{

   this->assign_natural_meta_data(str.metadata());

   return *this;

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const ansistring & strSrc)
//{
//
//   return ::str::assign(*this, strSrc.c_str());
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd16string & strSrc)
//{
//
//   return ::str::assign(*this, strSrc.c_str());
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd32string & strSrc)
//{
//
//   return ::str::assign(*this, strSrc.c_str());
//
//}
//

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const ansistring & ansistrSrc, strsize pos, strsize count)
{

   return ::str::assign(*this, ansistrSrc.m_pdata + pos, count);

}

//
template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd16string & widestrSrc, strsize pos, strsize count)
{

   return ::str::assign(*this, widestrSrc.m_pdata + pos, count);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd32string & widestrSrc, strsize pos, strsize count)
{

   return ::str::assign(*this, widestrSrc.m_pdata + pos, count);

}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const ansichar * pszSrc)
//{
//
//   return ::str::assign(*this, pszSrc);
//
//}
//

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const ansichar * pszSrc, strsize len)
{

   return ::str::assign(*this, pszSrc, len);

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd16char * pwd16sz)
//{
//
//   return ::str::assign(*this, pwd16sz);
//
//}
//

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd16char * pwd16sz, strsize len)
{

   return ::str::assign(*this, pwd16sz, len);

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd32char * pwd32sz)
//{
//
//   return ::str::assign(*this, pwd32sz);
//
//}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const wd32char * pwd32sz, strsize len)
{

   return ::str::assign(*this, pwd32sz, len);

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(ansichar ansich)
//{
//
//   return ::str::assign(*this, &ansich, 1);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(wd16char wd16ch)
//{
//
//   return ::str::assign(*this, &wd16ch, 1);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(wd32char wd32ch)
//{
//
//   return ::str::assign(*this, &wd32ch, 1);
//
//}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(ansichar ansich, strsize repeat)
{

   if (repeat > 0)
   {

      auto lenUnit = ::str::utf_to_utf_length(this->m_pdata, &ansich, 1);

      auto len = lenUnit * repeat;

      auto psz = get_string_buffer(len);

      TYPE_CHAR sz[8];

      ::str::utf_to_utf(sz, &ansich, 1);

      for (index i = 0; i < len; i += lenUnit)
      {

         memcpy(psz, sz, lenUnit * sizeof(TYPE_CHAR));

         psz += lenUnit;

      }

      release_string_buffer(len);

   }
   else
   {

      this->natural_release();

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(wd16char wd16ch, strsize repeat)
{

   if (repeat > 0)
   {

      auto lenUnit = ::str::utf_to_utf_length(this->m_pdata, &wd16ch, 1);

      auto len = lenUnit * repeat;

      auto psz = get_string_buffer(len);

      TYPE_CHAR sz[8];

      ::str::utf_to_utf(sz, &wd16ch, 1);

      for (index i = 0; i < len; i += lenUnit)
      {

         memcpy(psz, sz, lenUnit * sizeof(TYPE_CHAR));

         psz += lenUnit;

      }

      release_string_buffer(len);

   }
   else
   {

      this->natural_release();

   }

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(wd32char wd32ch, strsize repeat)
{

   if (repeat > 0)
   {

      auto lenUnit = ::str::utf_to_utf_length(this->m_pdata, &wd32ch, 1);

      auto len = lenUnit * repeat;

      auto psz = get_string_buffer(len);

      TYPE_CHAR sz[8];

      ::str::utf_to_utf(sz, &wd32ch, 1);

      for (index i = 0; i < len; i += lenUnit)
      {

         memcpy(psz, sz, lenUnit * sizeof(TYPE_CHAR));

         psz += lenUnit;

      }

      release_string_buffer(len);

   }
   else
   {

      this->natural_release();

   }

   return *this;

}


//template < typename TYPE_CHAR >
//template < int t_nSize >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::assign(const static_string<CHAR_TYPE, t_nSize > & ansistrSrc)
//{
//
//   return assign(ansistrSrc.c_str(), ansistrSrc.length());
//
//}
//

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const string_base & str)
{

   return append(str.m_pdata, str.get_length());

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const wd16string & wd16strSrc)
//{
//
//   return append(wd16strSrc.m_pdata, wd16strSrc.get_length());
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const wd32string & wd32strSrc)
//{
//
//   return append(wd32strSrc.m_pdata, wd32strSrc.get_length());
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const ansichar * pszSrc)
//{
//
//   return append(pszSrc, ::str::string_safe_length(pszSrc));
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const wd16char * pwszSrc)
//{
//
//   return append(pwszSrc, ::str::string_safe_length(pwszSrc));
//
//}
//

//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const wd32char * pwszSrc)
//{
//
//   return append(pwszSrc, ::str::string_safe_length(pwszSrc));
//
//}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const ansichar * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + ::str::utf_to_utf_length(this->m_pdata, pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   ::str::utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const wd16char * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + ::str::utf_to_utf_length(this->m_pdata, pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   ::str::utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const wd32char * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + ::str::utf_to_utf_length(this->m_pdata, pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   ::str::utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   return *this;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append_character(ansichar ch)
{

   return append(&ch, 1);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append_character(wd16char wch)
{

   return append(&wch, 1);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append_character(wd32char wch)
{

   return append(&wch, 1);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(strsize len, CHAR_TYPE ch)
{

   if (len > 0)
   {

      strsize nOldLength = this->get_length();

      strsize nNewLength = nOldLength + len;

      CHAR_TYPE * pszBuffer = this->get_string_buffer(nNewLength);

      auto pch = pszBuffer + nOldLength;

      auto p = pch + len - 1;

      while (p >= pch)
      {

         *p = ch;

         p--;

      }

      this->release_string_buffer(nNewLength);

   }

   return *this;

}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(strsize len, ansichar ch)
//{
//
//   if (len > 0)
//   {
//
//      strsize nOldLength = this->get_length();
//
//      strsize nNewLength = nOldLength + len;
//
//      CHAR_TYPE * pszBuffer = this->get_string_buffer(nNewLength);
//
//      CHAR_TYPE
//
//         auto pch = pszBuffer + nOldLength;
//
//      auto p = pch + len - 1;
//
//      while (p >= pch)
//      {
//
//         *p = ch;
//
//         p--;
//
//      }
//
//      this->release_string_buffer(nNewLength);
//
//   }
//
//   return *this;
//
//}



//template < typename TYPE_CHAR >
//template < typename STATIC_TYPE_CHAR, int t_nSize >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::append(const static_string<STATIC_TYPE_CHAR, t_nSize > & ansistrSrc)
//{
//
//   return append(ansistrSrc.c_str(), ansistrSrc.length());
//
//}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare(const CHAR_TYPE * psz) const noexcept
{

   return ::str::string_compare(this->m_pdata, psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare_ci(const CHAR_TYPE * psz) const noexcept
{

   return ::str::string_compare_ci(this->m_pdata, psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate(const CHAR_TYPE * psz) const noexcept
{

   return ::str::string_collate(this->m_pdata, psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate_ci(const CHAR_TYPE * psz) const noexcept
{

   return ::str::string_collate_ci(this->m_pdata, psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare(const CHAR_TYPE * psz, strsize len) const noexcept
{

   return ::str::string_n_compare(this->m_pdata, psz, len);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare_ci(const CHAR_TYPE * psz, strsize len) const noexcept
{

   return ::str::string_n_compare_ci(this->m_pdata, psz, len);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate(const CHAR_TYPE * psz, strsize len) const noexcept
{

   return ::str::string_n_collate(this->m_pdata, psz, len);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate_ci(const CHAR_TYPE * psz, strsize len) const noexcept
{

   return ::str::string_n_collate_ci(this->m_pdata, psz, len);

}


// TODO strncmpn(const ansichar * psz1, strsize len1, const ansichar * psz2, strsize len2);
// TODO wcsncmpn(const widechar * psz1, strsize len1, const widechar * psz2, strsize len2);


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).compare(psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).compare_ci(psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).collate(psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).collate_ci(psz);

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).compare(ansistr.Mid(iStart2, iCount2));

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::compare_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).compare_ci(ansistr.Mid(iStart2, iCount2));

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).collate(ansistr.Mid(iStart2, iCount2));

}


template < typename TYPE_CHAR >
inline i32 string_base < TYPE_CHAR > ::collate_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).collate_ci(ansistr.Mid(iStart2, iCount2));

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::operator==(const CHAR_TYPE * psz) const { return compare(psz) == 0; }
template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::operator==(CHAR_TYPE wch) const { return compare(string_base(wch)) == 0; }
template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::operator>(const CHAR_TYPE * psz) const { return compare(psz) > 0; }
template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::operator>(CHAR_TYPE wch) const { return compare(string_base(wch)) > 0; }
template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::operator<(const CHAR_TYPE * psz) const { return compare(psz) < 0; }
template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::operator<(CHAR_TYPE ch) const { return compare(string_base(ch)) < 0; }


template < typename TYPE_CHAR >
template < class InputIterator >
string_base < TYPE_CHAR > & string_base < TYPE_CHAR > ::assign(InputIterator first, InputIterator last)
{

   this->Empty();

   for (auto it = first; it <= last; it++)
   {

      *this += *it;

   }

   return *this;

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_in(const string_base < TYPE_CHAR > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_first_of(ansistr, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_in(const CHAR_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_first_of(s, pos, n);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_in(const CHAR_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_first_of(s, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_in(CHAR_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_first_of(ca, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_not_in(const string_base < TYPE_CHAR > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(ansistr, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_not_in(const CHAR_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_first_not_of(s, pos, n);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_not_in(const CHAR_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(s, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_first_not_in(CHAR_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(ca, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_not_in(const string_base < TYPE_CHAR > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(ansistr, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_not_in(const CHAR_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_last_not_of(s, pos, n);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_not_in(const CHAR_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_last_not_of(s, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_not_in(CHAR_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_last_not_of(ca, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_in(const string_base < TYPE_CHAR > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_last_of(ansistr, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_in(const CHAR_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_last_of(s, pos, n);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_in(const CHAR_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_last_of(s, pos);

}


template < typename TYPE_CHAR >
inline strsize string_base < TYPE_CHAR > ::find_last_in(CHAR_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_last_of(ca, pos);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::unichar_left(strsize nCount) const
{

   return Left(char_type_count(nCount));

}



template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::unichar_mid(strsize iFirst) const
{

   return Mid(char_type_count(iFirst));

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::unichar_mid(strsize iFirst, strsize nCount) const
{

   strsize iBeg = char_type_count(iFirst);

   strsize iEnd = char_type_count(iFirst + nCount);

   return Mid(iFirst, iEnd - iBeg);

}


//template < typename TYPE_CHAR >
//inline strsize string_base < TYPE_CHAR > ::erase(strsize iIndex, strsize nCount)
//{
//
//   return Delete(iIndex, nCount);
//
//}


template < typename TYPE_CHAR >
inline bool operator>(const TYPE_CHAR * psz, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr < psz;

}


template < typename TYPE_CHAR >
inline bool operator > (TYPE_CHAR ch, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr < ch;

}


template < typename TYPE_CHAR >
inline bool operator > (widechar ch, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr < ch;

}


template < typename TYPE_CHAR >
inline bool operator>(i32 i, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr < i;

}


template < typename TYPE_CHAR >
inline bool operator<(const TYPE_CHAR * psz, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr > psz;

}


template < typename TYPE_CHAR >
inline bool operator<(TYPE_CHAR ch, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr > ch;

}


template < typename TYPE_CHAR >
inline bool operator<(i32 i, const string_base < TYPE_CHAR > & ansistr)
{

   return ansistr > i;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::lower() const
{

   return string_base < TYPE_CHAR >(*this).make_lower();

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::upper() const
{

   return string_base < TYPE_CHAR >(*this).make_upper();

}


template < typename TYPE_CHAR >
inline const TYPE_CHAR * FormatArgument(const string_base < TYPE_CHAR > & value) noexcept
{

   return value.c_str();

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const block & block) :
   string_base((const ansichar *)block.get_data(), (strsize)block.get_size())
{


}

template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const ansistring & ansistr)
{

   ::str::assign(*this, ansistr);

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const wd16string & wd16str)
{

   ::str::assign(*this, wd16str.c_str());

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const wd32string & wd32str)
{

   ::str::assign(*this, wd32str.c_str());

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const natural_ansistring& ansistr) :
   string_base(ansistr.m_pdata)
{

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const natural_wd16string& wd16str) :
   string_base(wd16str.m_pdata)
{

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >::string_base(const natural_wd32string& wd32str) :
   string_base(wd32str.m_pdata)
{

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_any(const STRINGA & stra) const
{

   for (auto & str : stra)
   {

      if (contains(str))
      {

         return true;

      }

   }

   return false;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_all(const STRINGA & stra) const
{

   for (auto & str : stra)
   {

      if (!contains(str))
      {

         return false;

      }

   }

   return true;

}




template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_any_ci(const STRINGA & stra) const
{

   for (auto & str : stra)
   {

      if (contains_ci(str))
      {

         return true;

      }

   }

   return false;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_all_ci(const STRINGA & stra) const
{

   for (auto & str : stra)
   {

      if (!contains_ci(str))
      {

         return false;

      }

   }

   return true;

}


template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_any_wci(const STRINGA & stra) const
{

   for (auto & str : stra)
   {

      if (contains_wci(str))
      {

         return true;

      }

   }

   return false;

}

template < typename TYPE_CHAR >
bool string_base < TYPE_CHAR >::contains_all_wci(const STRINGA & stra) const
{

   for (auto & str : stra)
   {

      if (!contains_wci(str))
      {

         return false;

      }

   }

   return true;

}



template < typename TYPE_CHAR >
template < raw_pointer_castable < TYPE_CHAR > PCHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::Tokenize(PCHAR pszTokens, strsize & iStart) const
{
   ASSERT(iStart >= 0);

   if (iStart < 0)
      __throw(error_bad_argument);

   if ((pszTokens == nullptr) || (*pszTokens == (char)0))
   {
      if (iStart < get_length())
      {
         return(string_base < TYPE_CHAR >(data() + iStart));
      }
   }
   else
   {
      const CHAR_TYPE * pszPlace = data() + iStart;
      const CHAR_TYPE * pszEnd = data() + get_length();
      if (pszPlace < pszEnd)
      {
         strsize nIncluding = ::str::string_span_including(pszPlace,
            pszTokens);

         if ((pszPlace + nIncluding) < pszEnd)
         {
            pszPlace += nIncluding;
            strsize nExcluding = ::str::string_span_excluding(pszPlace, pszTokens);

            strsize iFrom = iStart + nIncluding;
            strsize nUntil = nExcluding;
            iStart = iFrom + nUntil + 1;

            return(Mid(iFrom, nUntil));
         }
      }
   }

   // return is_empty string_base < TYPE_CHAR >, done tokenizing
   iStart = -1;

   return(string_base < TYPE_CHAR >());

}




template < typename TYPE_CHAR >
string_base < TYPE_CHAR > string_base < TYPE_CHAR >::intersection(const string_base & find) const
{

   string_base < TYPE_CHAR > str;

   for (strsize i = 0; i < get_length(); i++)
   {

      auto ch = operator[](i);

      if (find.contains(ch))
      {

         str += ch;

      }


   }

   return str;

}



