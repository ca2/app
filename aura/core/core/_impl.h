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
_AFX_INLINE memory_exception::memory_exception(int_bool bAutoDelete, ::u32 nResourceID)
   : ::exception::exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE memory_exception::~memory_exception()
{ }
_AFX_INLINE invalid_argument_exception::invalid_argument_exception()
   : ::exception::exception() { }
_AFX_INLINE invalid_argument_exception::invalid_argument_exception(int_bool bAutoDelete, ::u32 nResourceID)
   : ::exception::exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE invalid_argument_exception::~invalid_argument_exception()
{ }
/*_AFX_INLINE CArchiveException::CArchiveException(i32 cause,
   LPCTSTR pszFileName /* = nullptr *//*)

   { m_cause = cause; m_strFileName = pszFileName; }


_AFX_INLINE CArchiveException::~CArchiveException()
   { }*/
/*_AFX_INLINE ::aura::file_exception_pointer::aura::file_exception_pointer(i32 cause, ::i32 lOsError,
   LPCTSTR pstrFileName /* = nullptr *///)
/*{ m_cause = cause; m_lOsError = lOsError; m_strFileName = pstrFileName; }
_AFX_INLINE ::aura::file_exception_pointer::~::aura::file_exception_pointer()
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
_AFX_INLINE void CArchive::SetObjectSchema(::u32 nSchema)
{ m_nObjectSchema = nSchema; }
_AFX_INLINE void CArchive::SetStoreParams(::u32 nHashSize, ::u32 nBlockSize)
{
ASSERT(IsStoring());
ASSERT(m_pStoreMap == nullptr);    // must be before first object written
m_nHashSize = nHashSize;
m_nGrowSize = nBlockSize;
}
_AFX_INLINE void CArchive::SetLoadParams(::u32 nGrowBy)
{
ASSERT(IsLoading());
ASSERT(m_pLoadArray == nullptr);   // must be before first object read
m_nGrowSize = nGrowBy;
}
_AFX_INLINE CArchive& CArchive::operator<<(i32 i)
{ return CArchive::operator<<((::i32)i); }
_AFX_INLINE CArchive& CArchive::operator<<(unsigned u)
{ return CArchive::operator<<((::i32)u); }
_AFX_INLINE CArchive& CArchive::operator<<(short w)
{ return CArchive::operator<<((::u16)w); }
_AFX_INLINE CArchive& CArchive::operator<<(char ch)
{ return CArchive::operator<<((byte)ch); }
#ifdef _NATIVE_WCHAR_T_DEFINED
_AFX_INLINE CArchive& CArchive::operator<<(unichar ch)
{ return CArchive::operator<<((::u16)ch); }
#endif
_AFX_INLINE CArchive& CArchive::operator<<(bool b)
{ return CArchive::operator <<((byte)(b ? 1 : 0)); }
_AFX_INLINE CArchive& CArchive::operator<<(byte by)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(byte) > m_lpBufMax) Flush();
   *(UNALIGNED byte*)m_lpBufCur = by; m_lpBufCur += sizeof(byte); return *this;
}

_AFX_INLINE CArchive& CArchive::operator<<(::i64 dwdw)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(::i64) > m_lpBufMax) Flush();
   *(UNALIGNED ::i64*)m_lpBufCur = dwdw; m_lpBufCur += sizeof(::i64); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(ULONGLONG dwdw)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(ULONGLONG) > m_lpBufMax) Flush();
   *(UNALIGNED ULONGLONG*)m_lpBufCur = dwdw; m_lpBufCur += sizeof(ULONGLONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(::u16 w)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(::u16) > m_lpBufMax) Flush();
      *(UNALIGNED ::u16*)m_lpBufCur = w; m_lpBufCur += sizeof(::u16); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(::i32 l)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(::i32) > m_lpBufMax) Flush();
   *(UNALIGNED ::i32*)m_lpBufCur = l; m_lpBufCur += sizeof(::i32); return *this;
}
_AFX_INLINE CArchive& CArchive::operator<<(::u32 dw)
{
if(!IsStoring())
   AfxThrowArchiveException(CArchiveException::readOnly,m_strFileName);
if (m_lpBufCur + sizeof(::u32) > m_lpBufMax) Flush();
   *(UNALIGNED ::u32*)m_lpBufCur = dw; m_lpBufCur += sizeof(::u32); return *this;
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
{ return CArchive::operator>>((::i32&)i); }
_AFX_INLINE CArchive& CArchive::operator>>(unsigned& u)
{ return CArchive::operator>>((::i32&)u); }
_AFX_INLINE CArchive& CArchive::operator>>(short& w)
{ return CArchive::operator>>((::u16&)w); }
_AFX_INLINE CArchive& CArchive::operator>>(char& ch)
{ return CArchive::operator>>((byte&)ch); }
#ifdef _NATIVE_WCHAR_T_DEFINED
_AFX_INLINE CArchive& CArchive::operator>>(unichar& ch)
{ return CArchive::operator>>((::u16&)ch); }
#endif
_AFX_INLINE CArchive& CArchive::operator>>(bool& b)
{ byte by; CArchive& ar = CArchive::operator>>(by); b = (by ? true : false); return ar; }
_AFX_INLINE CArchive& CArchive::operator>>(byte& by)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(byte) > m_lpBufMax)
   FillBuffer(::u32(sizeof(byte) - (m_lpBufMax - m_lpBufCur)));
by = *(UNALIGNED byte*)m_lpBufCur; m_lpBufCur += sizeof(byte); return *this;
}

_AFX_INLINE CArchive& CArchive::operator>>(::i64& dwdw)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(::i64) > m_lpBufMax)
   FillBuffer(sizeof(::i64) - (::u32)(m_lpBufMax - m_lpBufCur));
dwdw = *(UNALIGNED ::i64*)m_lpBufCur; m_lpBufCur += sizeof(::i64); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(ULONGLONG& dwdw)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(ULONGLONG) > m_lpBufMax)
   FillBuffer(sizeof(ULONGLONG) - (::u32)(m_lpBufMax - m_lpBufCur));
dwdw = *(UNALIGNED ULONGLONG*)m_lpBufCur; m_lpBufCur += sizeof(ULONGLONG); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(::u16& w)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(::u16) > m_lpBufMax)
   FillBuffer(::u32(sizeof(::u16) - (m_lpBufMax - m_lpBufCur)));
w = *(UNALIGNED ::u16*)m_lpBufCur; m_lpBufCur += sizeof(::u16); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(::u32& dw)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(::u32) > m_lpBufMax)
   FillBuffer(::u32(sizeof(::u32) - (m_lpBufMax - m_lpBufCur)));
dw = *(UNALIGNED ::u32*)m_lpBufCur; m_lpBufCur += sizeof(::u32); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(float& f)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(float) > m_lpBufMax)
   FillBuffer(::u32(sizeof(float) - (m_lpBufMax - m_lpBufCur)));
f = *(UNALIGNED float*)m_lpBufCur; m_lpBufCur += sizeof(float); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(double& d)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(double) > m_lpBufMax)
   FillBuffer(::u32(sizeof(double) - (m_lpBufMax - m_lpBufCur)));
d = *(UNALIGNED double*)m_lpBufCur; m_lpBufCur += sizeof(double); return *this;
}
_AFX_INLINE CArchive& CArchive::operator>>(::i32& l)
{
if(!IsLoading())
   AfxThrowArchiveException(CArchiveException::writeOnly,m_strFileName);
if (m_lpBufCur + sizeof(::i32) > m_lpBufMax)
   FillBuffer(::u32(sizeof(::i32) - (m_lpBufMax - m_lpBufCur)));
l = *(UNALIGNED ::i32*)m_lpBufCur; m_lpBufCur += sizeof(::i32); return *this;
}
*/
//_AFX_INLINE CArchive::CArchive(const CArchive& /* arSrc */)
//   { }
//_AFX_INLINE void CArchive::operator=(const CArchive& /* arSrc */)
/*   { }
CLASS_DECL_COREapi00000001 CArchive& operator<<(CArchive& ar, const object* pOb);
_AFX_INLINE CArchive& operator>>(CArchive& ar, object*& pOb)
   { pOb = ar.ReadObject(nullptr); return ar; }
_AFX_INLINE CArchive& operator>>(CArchive& ar, const object*& pOb)
   { pOb = ar.ReadObject(nullptr); return ar; }

_AFX_INLINE void CArchive::EnsureRead(void *pdata, ::u32 nCount)

{
   ::u32 nRead=read(pdata, nCount);

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


