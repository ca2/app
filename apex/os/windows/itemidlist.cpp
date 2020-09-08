#include "framework.h"
#include "apex/os/windows_common/cotaskptr.h"


itemidlist::itemidlist() :
   m_pidl(nullptr)
{

}


itemidlist::itemidlist(const itemidlist & iidl) :
   m_pidl(nullptr)
{

   if (!iidl.is_empty())
   {

      m_pidl = _copy(iidl);

   }

}


itemidlist::itemidlist(itemidlist && iidl)
{

   m_pidl = iidl.m_pidl;

   iidl.m_pidl = nullptr;

}


itemidlist::itemidlist(const char * pszPath) :
   m_pidl(nullptr)
{

   parse(pszPath);

}


itemidlist::itemidlist(LPCITEMIDLIST pidl, bool bAttach) :
   m_pidl(nullptr)
{

   if (bAttach)
   {

      attach((LPITEMIDLIST) pidl);

   }
   else
   {

      copy(pidl);

   }

}


itemidlist::~itemidlist()
{

   free();

}


void itemidlist::_free(LPITEMIDLIST & pidl)
{

   if (!pidl)
   {

      return;

   }

   LPITEMIDLIST point = pidl;

   pidl = nullptr;

   comptr < IMalloc > pmalloc;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      return;

   }

   pmalloc->Free(point);

}


int itemidlist::count() const
{

   return _count(m_pidl); //Get pidl count.

}


int itemidlist::len() const
{

   return _len(m_pidl);

}


void itemidlist::free()
{

   _free(m_pidl);

}



bool itemidlist::parse(const char * pszPath)
{

   free();

   if(FAILED(_parse(m_pidl, pszPath)))
   {

      return false;

   }

   return true;

}


LPITEMIDLIST itemidlist::_copy(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return nullptr;

   }

   int nSize = _len(pidl);

   comptr < IMalloc > pmalloc;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      throw memory_exception();

      return nullptr;

   }

   LPITEMIDLIST pidlNew = (LPITEMIDLIST)pmalloc->Alloc(nSize);

   if (pidlNew)
   {

      ::memcpy_dup(pidlNew, pidl, nSize);

   }

   return pidlNew;

}


int itemidlist::_count(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return 0;

   }

   LPCITEMIDLIST pidlr = pidl;

   int nCount = 0;

   while (pidlr->mkid.cb)
   {

      nCount++;

      pidlr = _next(pidlr);

   }

   return nCount;

}


int itemidlist::_len(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return 0;

   }

   int nSize = sizeof(pidl->mkid.cb);

   while (pidl->mkid.cb)
   {

      nSize += pidl->mkid.cb;

      pidl = _next(pidl);

   }

   return nSize;

}


itemidlist itemidlist::operator/(const itemidlist & piidl) const
{

   return _cat(m_pidl, piidl);

}


itemidlist & itemidlist::operator=(const char * pszPath)
{

   if (!parse(pszPath))
   {

      throw resource_exception("Failed to parse the path " + string (pszPath));

   }

   return *this;

}


itemidlist & itemidlist::operator=(const itemidlist & piidl)
{

   copy(piidl);

   return *this;

}

LPITEMIDLIST itemidlist::_cat(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
   LPITEMIDLIST pidlNew;

   int cb1;

   int cb2;

   if (pidl1)
   {

      cb1 = _len(pidl1) - sizeof(pidl1->mkid.cb);

   }
   else
   {

      cb1 = 0;

   }

   cb2 = _len(pidl2);

   pidlNew = _create(cb1 + cb2);

   if (pidlNew)
   {

      if (pidl1)
      {

         ::memcpy_dup(pidlNew, pidl1, cb1);

      }

      ::memcpy_dup(((LPSTR)pidlNew) + cb1, pidl2, cb2);

   }

   return pidlNew;

}


LPITEMIDLIST itemidlist::_create(int nSize)
{

   comptr < IMalloc > pmalloc;

   LPITEMIDLIST pidl = nullptr;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      throw memory_exception();

      return nullptr;

   }

   pidl = (LPITEMIDLIST)pmalloc->Alloc(nSize);

   if (pidl == nullptr)
   {

      throw memory_exception();

      return nullptr;

   }

   ::zero(pidl, nSize);

   return pidl;

}


itemidlist & itemidlist::operator=(LPCITEMIDLIST pidl)
{

   copy(pidl);

   return *this;

}

bool itemidlist::copy(LPCITEMIDLIST pidlf)
{

   free();

   m_pidl = _copy(pidlf);

   return true;

}


itemidlist & itemidlist::operator/=(const itemidlist & pidl)
{

   LPITEMIDLIST pidlp = m_pidl;

   m_pidl = _cat(m_pidl, pidl);

   _free(pidlp);

   return *this;

}


itemidlist & itemidlist::operator-=(int i)
{

   left(count() - i);

   return *this;

}

itemidlist itemidlist::operator-(int i) const
{

   return _copy(m_pidl, count() - i);

}


itemidlist itemidlist::at(int nIndex) const
{

   return _create_one(m_pidl, nIndex);

}


itemidlist itemidlist::operator[](int nIndex) const
{

   return at(nIndex);

}


LPITEMIDLIST itemidlist::_create_one(LPCITEMIDLIST pidlf, int iIndex)
{

   if (iIndex < 0)
   {

      return nullptr;

   }

   int iCount = _count(pidlf);

   if (iCount <= 0 || iIndex > iCount)
   {

      return nullptr;

   }

   while (iIndex)
   {

      iIndex--;

      pidlf = _next(pidlf);

   }

   LPITEMIDLIST pidlRet = nullptr;

   int uSize = pidlf->mkid.cb;

   pidlRet = _create(uSize + sizeof(pidlf->mkid.cb));

   ::zero(pidlRet, uSize + sizeof(pidlf->mkid.cb));

   ::memcpy_dup(pidlRet, pidlf, uSize);

   return pidlRet;

}


bool itemidlist::operator==(const itemidlist & pidl) const
{

   comptr < IShellFolder > psfDesktop;


   if (FAILED(SHGetDesktopFolder(&psfDesktop)))

   {

      return false;

   }

   return psfDesktop->CompareIDs(0, m_pidl, pidl) == 0;


}


itemidlist itemidlist::left(int nCount) const
{

   itemidlist pidl;

   if (nCount == -1)
   {

      nCount = count();

   }

   if (nCount <= 0)
   {

      return pidl;

   }

   int iCount = count();

   if (nCount > iCount)
   {

      nCount = iCount;

   }

   LPITEMIDLIST pidlRes = nullptr;

   size_t nSize = _len(m_pidl, nCount);

   comptr < IMalloc > pmalloc;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      return pidl;

   }

   pidlRes = (LPITEMIDLIST)pmalloc->Alloc(sizeof(m_pidl->mkid.cb) + nSize);

   ::zero(pidlRes, nSize + sizeof(m_pidl->mkid.cb));

   ::memcpy_dup((LPVOID)pidlRes, (LPVOID)m_pidl, nSize);

   return pidlRes;

}


int itemidlist::_len(LPCITEMIDLIST pidl, int nCount)
{

   int iCount = _count(pidl);

   if (nCount >= iCount)
   {

      return _len(pidl);

   }

   int cbTotal = 0;

   if (pidl)
   {

      while (nCount--)
      {

         cbTotal += pidl->mkid.cb;

         pidl = _next(pidl);

      }

   }

   return cbTotal;

}


string itemidlist::display_name(DWORD dwFlags) const
{

   comptr < IShellFolder > psf;


   comptr < IShellFolder > psfDesktop;


   HRESULT hr;

   itemidlist pidl;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))

   {

      return "";

   }

   int nCount = count();

   if (nCount > 1)
   {
      pidl = left(nCount - 1);

      hr = psfDesktop->BindToObject(pidl, 0, IID_IShellFolder, (LPVOID*)&psf);


      if (FAILED(hr))
      {

         return "";

      }

   }
   else
   {

      psf = psfDesktop;


   }

   pidl = at(nCount - 1);

   return _display_name(psf, pidl, dwFlags);


}


string itemidlist::path() const
{

   return _path(m_pidl);

}


int itemidlist::icon_index(int uFlags) const
{

   return _icon_index(m_pidl, uFlags);

}


void itemidlist::attach(LPITEMIDLIST pidl)
{

   free();

   m_pidl = pidl;

}


LPITEMIDLIST itemidlist::detach()
{

   LPITEMIDLIST pidl = m_pidl;

   m_pidl = nullptr;

   return pidl;

}


string itemidlist::tooltip_info() const
{

   comptr < IShellFolder > psfDesktop;

   comptr < IShellFolder > psf;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))
   {

      return "";

   }

   int iCount = count();

   itemidlist item = left(iCount - 1);

   HRESULT hr = psfDesktop->BindToObject(item, 0, IID_IShellFolder, (LPVOID*)&psf);

   if (FAILED(hr))
   {

      return "";

   }

   item = at(iCount - 1);

   return _tooltip_info(psf, item);

}


string itemidlist::_tooltip_info(IShellFolder * psf, LPCITEMIDLIST pidl)

{

   if (!psf)

   {

      return "";

   }

   comptr < IQueryInfo > pinfo;

   psf->GetUIObjectOf(nullptr, 1, (LPCITEMIDLIST*)&(pidl), IID_IQueryInfo, 0, (LPVOID*)&pinfo);


   if (pinfo.is_null())
   {

      return "";

   }

   cotaskptr < LPWSTR > pwsz;


   pinfo->GetInfoTip(0, &pwsz);


   return utf8(pwsz);


}


LPITEMIDLIST itemidlist::_full(IShellFolder * psf, LPCITEMIDLIST lpi)

{

   //   OLECHAR szOleChar[MAX_PATH + 1];

   comptr < IShellFolder > psfDeskTop;

   LPITEMIDLIST pifq;

   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   string str = _display_name(psf, lpi, SHGDN_FORPARSING);


   if (str.is_empty())
   {

      return nullptr;

   }

   hr = SHGetDesktopFolder(&psfDeskTop);


   if (FAILED(hr))
   {

      return nullptr;

   }

   wstring wstr(str);

   auto pwsz = wstr.get_string_buffer();

   hr = psfDeskTop->ParseDisplayName(nullptr, nullptr, pwsz, &ulEaten, &pifq, &ulAttribs);


   if (FAILED(hr))
   {

      return nullptr;

   }

   return pifq;


}


HRESULT itemidlist::_GetUIObjectOf(REFIID riid, LPVOID* ppOut, LPITEMIDLIST pidlf, HWND hWnd)
{

   comptr < IShellFolder > psf;


   HRESULT hr = S_OK;

   itemidlist ciidf(pidlf), pidl;

   ciidf.split(&psf, pidl);


   if (psf.is_null())

   {

      return E_FAIL;

   }

   hr = psf->GetUIObjectOf(hWnd, 1, pidl, riid, nullptr, ppOut);


   return hr;

}


HRESULT itemidlist::GetUIObjectOf(REFIID riid, LPVOID* ppOut, HWND hWnd)
{

   return _GetUIObjectOf(riid, ppOut, m_pidl, hWnd);

}


//Get relative pidl and the corresponding ShellFolder interface.
void itemidlist::split(IShellFolder ** psf, itemidlist & pidl)

{

   _split(psf, pidl.m_pidl, m_pidl);


}


itemidlist itemidlist::last() const
{

   int nCount = count();

   itemidlist pidl;

   if (nCount > 1)
   {

      pidl = at(nCount - 1);

   }

   return pidl;

}


void itemidlist::_split(IShellFolder ** psf, LPITEMIDLIST &pidl, LPITEMIDLIST pidlf)

{

   pidl = nullptr;

   *psf = nullptr;


   if (!pidlf)
   {
      SHGetDesktopFolder(psf);

      return;
   }

   comptr < IShellFolder > psfDesktop ;


   if (FAILED(SHGetDesktopFolder(&psfDesktop)))

   {

      return;

   }

   int nCount = _count(pidlf);

   itemidlist pidlFolder = _copy(pidlf, nCount - 1);

   if (pidlFolder.m_pidl)
   {

      psfDesktop->BindToObject(pidlFolder, nullptr, IID_IShellFolder, (LPVOID*)psf);


      pidl = _create_one(pidlf, nCount - 1);

   }
   else
   {

      *psf = psfDesktop;


      (*psf)->AddRef();


   }

}


LPITEMIDLIST itemidlist::_copy(LPCITEMIDLIST pidlOrg, int nCount)
{

   if (nCount < 1)
   {

      return nullptr;

   }

   LPITEMIDLIST pidlRes = nullptr;

   comptr < IMalloc > pmalloc;

   size_t nSize = _len(pidlOrg, nCount);

   HRESULT hr;

   int nPidlCount = _count(pidlOrg);

   if (nPidlCount < nCount)
   {

      nCount = nPidlCount;

   }

   hr = SHGetMalloc(&pmalloc);

   if (FAILED(hr))
   {

      return nullptr;

   }

   pidlRes = (LPITEMIDLIST)pmalloc->Alloc(sizeof(pidlOrg->mkid.cb) + nSize);

   ::zero(pidlRes, nSize + sizeof(pidlOrg->mkid.cb));

   ::memcpy_dup((LPVOID)pidlRes, (LPVOID)pidlOrg, nSize);

   return pidlRes;

}

int itemidlist::_compare(LPCITEMIDLIST pidlf1, LPCITEMIDLIST pidlf2,
                         IShellFolder * psfFolder, LPARAM lParam)
{

   comptr < IShellFolder > psfDesktop = psfFolder;

   if (psfDesktop.is_null())
   {

      SHGetDesktopFolder(&psfDesktop);

      if (psfDesktop.is_null())
      {

         return 0;

      }

   }
   else
   {

      psfDesktop->AddRef();

   }

   HRESULT hr = psfDesktop->CompareIDs(lParam, pidlf1, pidlf2);

   return int(HRESULT_CODE(hr));

}


HRESULT itemidlist::_parse(LPITEMIDLIST & pidl, const char * pcszPath, IShellFolder * psfFolder)
{

   if (!psfFolder)
   {

      return E_FAIL;

   }

   wstring wstr(pcszPath);

   ULONG chEaten = 0;

   HRESULT hr = psfFolder->ParseDisplayName(nullptr, nullptr, wstr.get_string_buffer(MAX_PATH *8), &chEaten, &pidl, nullptr);

   wstr.release_string_buffer();

   return hr;

}


HRESULT itemidlist::_parse(LPITEMIDLIST &pidlf, const char * pcszPath)
{

   comptr < IShellFolder > psfDesktop;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))
   {

      return E_FAIL;

   }

   return _parse(pidlf, pcszPath, psfDesktop);

}


int itemidlist::_icon_index(LPCITEMIDLIST pidlf, int uFlags)
{

   SHFILEINFO sfi;

   SHGetFileInfo((LPCTSTR)pidlf, 0, &sfi, sizeof(SHFILEINFO), uFlags);

   return sfi.iIcon;

}


int itemidlist::_overlay_icon_index(IShellFolder * psfFolder, LPCITEMIDLIST pidl)

{

   if (!psfFolder || !pidl)

   {

      return -1;

   }

   comptr < IShellIcon > psiIcon;


   comptr < IShellIconOverlay >  psiIconOl;


   int index = -1;

   psfFolder->QueryInterface(IID_IShellIcon, (LPVOID*)&psiIcon);


   if (psiIcon.is_null())

   {

      return -1;

   }

   psiIcon->QueryInterface(IID_IShellIconOverlay, (LPVOID*)&psiIconOl);


   if (psiIconOl.is_null())

   {

      return -1;

   }

   if (psiIconOl->GetOverlayIndex(pidl, &index) != S_OK)

   {

      index = -1;

   }

   return index;

}

string itemidlist::_display_name(STRRET & strret, LPCITEMIDLIST pidl)
{

   string str;

   switch (strret.uType)
   {
   case STRRET_WSTR:
   {
      str = (WCHAR *)strret.pOleStr;
   }
   break;
   case STRRET_OFFSET:
   {
      str = (LPSTR)pidl + strret.uOffset;
   }
   break;
   case STRRET_CSTR:
   {
      str = (LPSTR)strret.cStr;
      break;
   }
   default:
      break;
   }

   return str;

}


string itemidlist::_display_name(IShellFolder * psf, LPCITEMIDLIST pi, DWORD dwFlags)

{

   string str;

   STRRET strret;

   if (NOERROR == psf->GetDisplayNameOf(pi, dwFlags, &strret))

   {

      str = _display_name(strret, pi);


   }

   return str;

}


string itemidlist::_path(LPCITEMIDLIST pidl)
{

   wstring wstr;

   SHGetPathFromIDListEx(pidl, wstr.get_string_buffer(2048), 2048, 0);

   return wstr;

}



// left member (with -2? or "count-1" argument)
//comptr < IShellFolder> itemidlist::_017GetShellParentFolder(LPITEMIDLIST piidlChild)

//{
//
//   LPITEMIDLIST piidlParent = _017ItemIDListGetFolderParent(lpiidlChild);

//
//   comptr < IShellFolder> pfolderRet = _017GetShellFolder(piidlParent);

//
//   _017ItemIDListFree(piidlParent);

//
//   return pfolderRet;
//
//}




comptr < IShellFolder > itemidlist::get_shell_folder() const
{

   HRESULT hr = S_OK;

   if (SUCCEEDED(hr))
   {

      comptr < IShellFolder > pfolderDesktop;

      SHGetDesktopFolder(&pfolderDesktop);

      comptr < IShellFolder > pfolder;

      hr = pfolderDesktop->BindToObject(
           m_pidl,
           nullptr,
           IID_IShellFolder,
           (void**) &pfolder);

      if (SUCCEEDED(hr))
      {

         return pfolder;

      }

   }
   else
   {
      ASSERT(FALSE);
   }

   return nullptr;

}


