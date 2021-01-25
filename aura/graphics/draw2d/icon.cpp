#include "framework.h"

#ifdef WINDOWS_DESKTOP

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-size-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

struct MYICON_INFO
{
   int     nWidth;
   int     nHeight;
   int     nBitsPerPixel;
};

MYICON_INFO MyGetIconInfo(HICON hIcon);

#endif


namespace draw2d
{


   icon::icon()
   {

      m_picon = nullptr;
      m_bAutoDelete = true;

   }


   ::e_status     icon::attach_os_data(void * picon, bool bTakeOwnership)
   {

      m_picon = picon;

      m_bAutoDelete = bTakeOwnership;

      on_update_icon();

      return ::success;

   }


#ifdef WINDOWS

   ::e_status     icon::attach_os_data(HICON hicon, bool bTakeOwnership)
   {

      m_picon = hicon;

      m_bAutoDelete = bTakeOwnership;

      on_update_icon();

      return ::success;

   }

#endif

   icon::~icon()
   {

      if (m_bAutoDelete)
      {

         if (m_picon != nullptr)
         {

#ifdef WINDOWS_DESKTOP

            //for (auto point : m_iconmap)
            //{

            //   ::DestroyIcon((HICON)point.element2());

            //}

            ::DestroyIcon((HICON)m_picon);

#else

            //__throw(todo());

#endif


         }

      }

   }


   ::e_status icon::initialize(::layered * pobjectContext)
   {

      auto estatus = ::matter::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __object(pobjectContext)->__construct(m_pimagemap);

      return estatus;

   }

   icon::operator void *()
   {

      return m_picon;

   }

#ifdef WINDOWS

   icon::operator HICON()
   {

      return (HICON)m_picon;

   }
   
   HICON icon::get_os_data()
   {

      return (HICON)m_picon;

   }

#else

   void * icon::get_os_data()
   {

      return m_picon;

   }

#endif

   string icon::get_tray_icon_name()
   {

      return m_strAppTrayIcon;

   }


   bool icon::load_file(string strPath)
   {

#ifdef WINDOWS_DESKTOP

      strPath = Context.defer_process_matter_path(strPath);

      int_array ia;

      ia.add(16);
      ia.add(24);
      ia.add(32);
      ia.add(48);
      ia.add(256);

      HICON hIcon = nullptr;

      for (auto i : ia)
      {

         hIcon = (HICON) ::LoadImageW(nullptr, wstring(strPath), IMAGE_ICON, i, i, LR_LOADFROMFILE);

         if (hIcon != nullptr)
         {

            m_iconmap[::size(i, i)] = hIcon;

            m_picon = hIcon;

            on_update_icon();

         }

      }

      return m_picon != nullptr;

#else

      m_strAppTrayIcon = strPath;

      return true;

#endif

   }

   bool icon::load_matter(string strMatter)
   {

      string strPath = Context.dir().matter(strMatter);

      if (!load_file(strPath))
      {

         return false;

      }


      on_update_icon();

      return true;

   }

   bool icon::load_app_tray_icon(string strApp)
   {

#ifdef WINDOWS_DESKTOP

      string strMatter = "main/icon.ico";

      if (!load_matter(strMatter))
      {

         return false;

      }

      return true;

#else

      m_strAppTrayIcon = strApp;

      return true;

#endif


   }


   void icon::on_update_icon()
   {

      if (m_picon == nullptr)
      {

         m_size.cx = 0;
         m_size.cy = 0;

         return;

      }

#ifdef WINDOWS_DESKTOP

      auto info = MyGetIconInfo((HICON)m_picon);

      m_size.cx = info.nWidth;
      m_size.cy = info.nHeight;

      get_image(m_size);

#else

      // building icon not supported (size > 512 :-)
      if (m_size.cx <= 0 || m_size.cy <= 0 || m_size.cx >= 512 || m_size.cy >= 512)
      {

         m_size.cx = 22;
         m_size.cy = 22;

      }

#endif

      for (auto & size : m_pimagemap->keys())
      {

         m_sizea.add(size);

      }

      m_sizea.pred_sort([](auto & size1, auto & size2)
         {

            return size1.cx < size2.cx;

         });

   }


   ::size icon::get_size()
   {

      return m_size;

   }


   image * icon::get_image(const concrete < ::size > & size)
   {

      bool bExists;

      __defer_construct_new(m_pimagemap);

      auto pimage = m_pimagemap->get(size, bExists);

      if (bExists)
      {

         return pimage;

      }

#ifdef WINDOWS_DESKTOP

      bool bOk = false;

      HBITMAP hbitmap = nullptr;

      HDC hdc = nullptr;

      HBITMAP hbitmapOld = nullptr;

      try
      {

         BITMAPINFO info;

         ZeroMemory(&info, sizeof(BITMAPINFO));

         auto iScan = size.cx * 4;

         info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         info.bmiHeader.biWidth = size.cx;
         info.bmiHeader.biHeight = -size.cy;
         info.bmiHeader.biPlanes = 1;
         info.bmiHeader.biBitCount = 32;
         info.bmiHeader.biCompression = BI_RGB;
         info.bmiHeader.biSizeImage = size.cy * iScan;

         color32_t* pcolorref = nullptr;

         hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pcolorref, nullptr, 0);

         ::pixmap pixmap;

         pixmap.init(size, pcolorref, iScan);

         hdc = ::CreateCompatibleDC(nullptr);

         hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if (!::DrawIconEx(hdc, 0, 0, (HICON)m_picon, size.cx, size.cy, 0, nullptr, DI_IMAGE | DI_MASK))
         {

            output_debug_string("nok");

         }
         else
         {

            bool bAllZeroAlpha = true;
            bool bTheresUint32 = false;

            pixmap.map();

            int area = size.area();

            auto pc = pixmap.colorref();
            byte * pA = &((byte *)pc)[3];

            for (int i = 0; i < area; i++)
            {
               if (*pc != 0)
               {
                  bTheresUint32 = true;
               }
               if (*pA != 0)
               {
                  bAllZeroAlpha = false;
                  break;
               }
               pc++;
               pA += 4;
            }

            if (bAllZeroAlpha && bTheresUint32)
            {

               pc = pixmap.colorref();
               pA = &((byte *)pc)[3];

               for (int i = 0; i < area; i++)
               {
                  if (*pc != 0)
                  {
                     *pA = 255;
                  }
                  pc++;
                  pA += 4;
               }
            }

            ::SelectObject(hdc, hbitmapOld);

            pimage->map();

            ::copy_colorref(pimage, pixmap);

         }

      }
      catch (...)
      {

         output_debug_string("!");

      }

      if (hdc != nullptr)
      {

         if (hbitmapOld != nullptr)
         {

            ::SelectObject(hdc, hbitmapOld);

         }

         ::DeleteDC(hdc);

      }

      if (hbitmap != nullptr)
      {

         ::DeleteObject(hbitmap);

      }

#endif

      return pimage;


   }


   ::size icon::get_smaller_size(const ::size & size)
   {

      if (m_sizea.isEmpty())
      {

         return nullptr;

      }


      ::index iFound = -1;

      for (::index i = 0; i < m_sizea.get_size(); i++)
      {

         if (size.cx < m_sizea[i].cx)
         {

            iFound = i;

         }
         else
         {

            break;

         }

      }

      if (iFound < 0)
      {

         return nullptr;

      }

      return m_sizea[iFound];

   }


} // namespace draw2d


#ifdef WINDOWS_DESKTOP

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-size-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

MYICON_INFO MyGetIconInfo(HICON hIcon)
{
   MYICON_INFO myinfo;
   ZeroMemory(&myinfo, sizeof(myinfo));

   ICONINFO info;
   ZeroMemory(&info, sizeof(info));

   BOOL bRes = FALSE;

   bRes = GetIconInfo(hIcon, &info);
   if (!bRes)
      return myinfo;

   BITMAP bmp;
   ZeroMemory(&bmp, sizeof(bmp));

   if (info.hbmColor)
   {
      const int nWrittenBytes = GetObject(info.hbmColor, sizeof(bmp), &bmp);
      if (nWrittenBytes > 0)
      {
         myinfo.nWidth = bmp.bmWidth;
         myinfo.nHeight = bmp.bmHeight;
         myinfo.nBitsPerPixel = bmp.bmBitsPixel;
      }
   }
   else if (info.hbmMask)
   {
      // Icon has no color plane, image data stored in mask
      const int nWrittenBytes = GetObject(info.hbmMask, sizeof(bmp), &bmp);
      if (nWrittenBytes > 0)
      {
         myinfo.nWidth = bmp.bmWidth;
         myinfo.nHeight = bmp.bmHeight / 2;
         myinfo.nBitsPerPixel = 1;
      }
   }

   if (info.hbmColor)
      DeleteObject(info.hbmColor);
   if (info.hbmMask)
      DeleteObject(info.hbmMask);

   return myinfo;
}



#endif


