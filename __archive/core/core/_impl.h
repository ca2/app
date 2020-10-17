#ifdef _AFX_INLINE
#ifndef AFX_INL_INCLUDE_GUARD
#define AFX_INL_INCLUDE_GUARD


// exceptions
_AFX_INLINE ::exception::exception::~::exception::exception()
{ }
_AFX_INLINE ::exception::exception::exception::exception()
{ m_bInitialized = FALSE; m_bLoaded = FALSE; }
_AFX_INLINE ::exception::exception::exception::exception(int_bool bAutoDelete)
   : ::exception::exception(bAutoDelete) { m_bInitialized = FALSE; m_bLoaded = FALSE; }
_AFX_INLINE ::exception::exception::~::exception::exception()
{ }

_AFX_INLINE memory_exception::memory_exception()
   : ::exception::exception() { }
_AFX_INLINE memory_exception::memory_exception(int_bool bAutoDelete, UINT nResourceID)
   : ::exception::exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE memory_exception::~memory_exception()
{ }
_AFX_INLINE invalid_argument_exception::invalid_argument_exception()
   : ::exception::exception() { }
_AFX_INLINE invalid_argument_exception::invalid_argument_exception(int_bool bAutoDelete, UINT nResourceID)
   : ::exception::exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE invalid_argument_exception::~invalid_argument_exception()
{ }
/*_AFX_INLINE CArchiveException::CArchiveException(i32 cause,
   LPCTSTR pszFileName /* = nullptr *//*)

   { m_cause = cause; m_strFileName = pszFileName; }


_AFX_INLINE CArchiveException::~CArchiveException()
   { }*/
/*_AFX_INLINE ::acme::file_exception_pointer::acme::file_exception_pointer(i32 cause, LONG lOsError,
   LPCTSTR pstrFileName /* = nullptr *///)
/*{ m_cause = cause; m_lOsError = lOsError; m_strFileName = pstrFileName; }
_AFX_INLINE ::acme::file_exception_pointer::~::acme::file_exception_pointer()
{ }

// file_pointer
_AFX_INLINE file_pointer::operator HANDLE() const
{ return m_hFile; }
_AFX_INLINE ULONGLONG file_pointer::SeekToEnd()
{ return seek(0, file_pointer::end); }
_AFX_INLINE void file_pointer::seek_to_begin()
{ seek(0, file_pointer::begin); }
_AFX_INLINE void file_pointer::SetFilePath(LPCTSTR pszNewName)

{
ASSERT_VALID(this);
ASSERT(AfxIsValidString(pszNewName));

if(pszNewName != nullptr)

   m_strFileName = pszNewName;

else
   __throw(invalid_argument_exception());

}
/*
// CFileFind
_AFX_INLINE int_bool CFileFind::IsReadOnly() const
{ return MatchesMask(FILE_ATTRIBUTE_READONLY); }
_AFX_INLINE int_bool CFileFind::IsDirectory() const
{ return MatchesMask(FILE_ATTRIBUTE_DIRECTORY); }
_AFX_INLINE int_bool CFileFind::IsCompressed() const
{ return MatchesMask(FILE_ATTRIBUTE_COMPRESSED); }
_AFX_INLINE int_bool CFileFind::IsSystem() const
{ return MatchesMask(FILE_ATTRIBUTE_SYSTEM); }
_AFX_INLINE int_bool CFileFind::IsHidden() const
{ return MatchesMask(FILE_ATTRIBUTE_HIDDEN); }
_AFX_INLINE int_bool CFileFind::IsTemporary() const
{ return MatchesMask(FILE_ATTRIBUTE_TEMPORARY); }
_AFX_INLINE int_bool CFileFind::IsNormal() const
{ return MatchesMask(FILE_ATTRIBUTE_NORMAL); }
_AFX_INLINE int_bool CFileFind::IsArchived() const
{ return MatchesMask(FILE_ATTRIBUTE_ARCHIVE); }

// CArchive
/*
_AFX_INLINE int_bool CArchive::IsLoading() const
{ return (m_nMode & CArchive::load) != 0; }
_AFX_INLINE int_bool CArchive::IsStoring() const
{ return (m_nMode & CArchive::load) == 0; }
_AFX_INLINE int_bool CArchive::IsByteSwapping() const
{ return FALSE; }
_AFX_INLINE int_bool CArchive::IsBufferEmpty() const
{ return m_lpBufCur == m_lpBufMax; }
_AFX_INLINE file_pointer  CArchive::GetFile() const
{ return m_pFile; }
_AFX_INLINE void CArchive::SetObjectSchema(UINT nSchema)
{ m_nObjectSchema = nSchema; }
_AFX_INLINE void CArchive::SetStoreParams(UINT nHashSize, UINT nBlockSize)
{
ASSERT(IsStoring());
ASSERT(m_pStoreMap == nullptr);    // must be before first matter written
m_nHashSize = nHashSize;
m_nGrowSize = nBlockSize;
}
_AFX_INLINE void CArchive::SetLoadParams(UINT nGrowBy)
{
ASSERT(IsLoading());
ASSERT(m_pLoadArray == nullptr);   // must be before first matter read
m_nGrowSize = nGrowBy;
}
_AFX_INLINE CArchive& CArchive::operator<<(i32 i)
{ return CArchive::operator<<((LONG)i); }
_AFX_INLINE CArchive& CArchive::operator<<(unsigned u)
{ return CArchive::operator<<((LONG)u); }
_AFX_INLINE CArchive& CArchive::operator<<(short w)
{ return CArchive::operator<<((WORD)w); }
_AFX_INLINE CArchive& CArchive::operator<<(char ch)
{ return CArchive::operator<<((BYTE)ch); }
#ifdef _NATIVE_WCHAR_T_DEFINED
_AFX_INLINE CArchive& CArchive::operator<<(unichar ch)
{ return CArchive::operator<<((WORD)ch); }
#endif
_AFX_INLINE CArchive& CArchive::operator<<(bool b)
{ return CArchive::operator <<((BYTE)(b ? 1 : 0)); }
_AFX_INLINE CArchive& CArchive::operator<<(BYTE by)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(BYTE) > m_lpBufMax) Flush();
   *(UNALIGNED BYTE*)m_lpBufCur = by; m_lpBufCur += sizeof(BYTE); return *this;
}

_AFX_INLINE CArchive& CArchive::operator<<(LONGLONG dwdw)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(LONGLONG) > m_lpBufMax) Flush();
   *(UNALIGNED LONGLONG*)m_lpBufCur = dwdw; m_lpBufCur += sizeof(LONGLONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(ULONGLONG dwdw)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(ULONGLONG) > m_lpBufMax) Flush();
   *(UNALIGNED ULONGLONG*)m_lpBufCur = dwdw; m_lpBufCur += sizeof(ULONGLONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(WORD w)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(WORD) > m_lpBufMax) Flush();
      *(UNALIGNED WORD*)m_lpBufCur = w; m_lpBufCur += sizeof(WORD); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(LONG l)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(LONG) > m_lpBufMax) Flush();
   *(UNALIGNED LONG*)m_lpBufCur = l; m_lpBufCur += sizeof(LONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(DWORD dw)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(DWORD) > m_lpBufMax) Flush();
   *(UNALIGNED DWORD*)m_lpBufCur = dw; m_lpBufCur += sizeof(DWORD); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(float f)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(float) > m_lpBufMax) Flush();
   *(UNALIGNED float*)m_lpBufCur = f; m_lpBufCur += sizeof(float); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(double d)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(double) > m_lpBufMax) Flush();
   *(UNALIGNED double*)m_lpBufCur = d; m_lpBufCur += sizeof(double); return *this;
}

_AFX_INLINE CArchive& CArchive::operator>>(i32& i)
{ return CArchive::operator>>((LONG&)i); }
_AFX_INLINE CArchive& CArchive::operator>>(unsigned& u)
{ return CArchive::operator>>((LONG&)u); }
_AFX_INLINE CArchive& CArchive::operator>>(short& w)
{ return CArchive::operator>>((WORD&)w); }
_AFX_INLINE CArchive& CArchive::operator>>(char& ch)
{ return CArchive::operator>>((BYTE&)ch); }
#ifdef _NATIVE_WCHAR_T_DEFINED
_AFX_INLINE CArchive& CArchive::operator>>(unichar& ch)
{ return CArchive::operator>>((WORD&)ch); }
#endif
_AFX_INLINE CArchive& CArchive::operator>>(bool& b)
{ BYTE by; CArchive& ar = CArchive::operator>>(by); b = (by ? true : false); return ar; }
_AFX_INLINE CArchive& CArchive::operator>>(BYTE& by)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(BYTE) > m_lpBufMax)
   FillBuffer(UINT(sizeof(BYTE) - (m_lpBufMax - m_lpBufCur)));
by = *(UNALIGNED BYTE*)m_lpBufCur; m_lpBufCur += sizeof(BYTE); return *this;
}

_AFX_INLINE CArchive& CArchive::operator>>(LONGLONG& dwdw)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(LONGLONG) > m_lpBufMax)
   FillBuffer(sizeof(LONGLONG) - (UINT)(m_lpBufMax - m_lpBufCur));
dwdw = *(UNALIGNED LONGLONG*)m_lpBufCur; m_lpBufCur += sizeof(LONGLONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(ULONGLONG& dwdw)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(ULONGLONG) > m_lpBufMax)
   FillBuffer(sizeof(ULONGLONG) - (UINT)(m_lpBufMax - m_lpBufCur));
dwdw = *(UNALIGNED ULONGLONG*)m_lpBufCur; m_lpBufCur += sizeof(ULONGLONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(WORD& w)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(WORD) > m_lpBufMax)
   FillBuffer(UINT(sizeof(WORD) - (m_lpBufMax - m_lpBufCur)));
w = *(UNALIGNED WORD*)m_lpBufCur; m_lpBufCur += sizeof(WORD); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(DWORD& dw)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(DWORD) > m_lpBufMax)
   FillBuffer(UINT(sizeof(DWORD) - (m_lpBufMax - m_lpBufCur)));
dw = *(UNALIGNED DWORD*)m_lpBufCur; m_lpBufCur += sizeof(DWORD); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(float& f)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(float) > m_lpBufMax)
   FillBuffer(UINT(sizeof(float) - (m_lpBufMax - m_lpBufCur)));
f = *(UNALIGNED float*)m_lpBufCur; m_lpBufCur += sizeof(float); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(double& d)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(double) > m_lpBufMax)
   FillBuffer(UINT(sizeof(double) - (m_lpBufMax - m_lpBufCur)));
d = *(UNALIGNED double*)m_lpBufCur; m_lpBufCur += sizeof(double); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(LONG& l)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(LONG) > m_lpBufMax)
   FillBuffer(UINT(sizeof(LONG) - (m_lpBufMax - m_lpBufCur)));
l = *(UNALIGNED LONG*)m_lpBufCur; m_lpBufCur += sizeof(LONG); return *this;
}
*/
//_AFX_INLINE CArchive::CArchive(const CArchive& /* arSrc */)
//   { }
//_AFX_INLINE void CArchive::operator=(const CArchive& /* arSrc */)
/*   { }
CLASS_DECL_COREapi00000001 CArchive& operator<<(CArchive& ar, const matter* pOb);
_AFX_INLINE CArchive& operator>>(CArchive& ar, matter*& pOb)
   { pOb = ar.ReadObject(nullptr); return ar; }
_AFX_INLINE CArchive& operator>>(CArchive& ar, const matter*& pOb)
   { pOb = ar.ReadObject(nullptr); return ar; }

_AFX_INLINE void CArchive::EnsureRead(void *pdata, UINT nCount)

{
   UINT nRead=read(pdata, nCount);

   if(nRead!=nCount)
   {
      AfxThrowArchiveException(CArchiveException::endOfFile);
   }
}
*/
// dump_context
_AFX_INLINE i32 dump_context::GetDepth() const
{ return m_nDepth; }
_AFX_INLINE void dump_context::SetDepth(i32 nNewDepth)
{ m_nDepth = nNewDepth; }
_AFX_INLINE dump_context::dump_context(const dump_context& /* dcSrc */)
{ }
_AFX_INLINE void dump_context::operator=(const dump_context& /* dcSrc */)
{ }

/////////////////////////////////////////////////////////////////////////////
#endif //AFX_INL_INCLUDE_GUARD
#endif //_AFX_INLINE


