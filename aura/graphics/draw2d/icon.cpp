#include "framework.h"

#ifdef WINDOWS_DESKTOP

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-size_i32-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

struct MYICON_INFO
{
   int     nWidth;
   int     nHeight;
   int     nBitsPerPixel;
};

MYICON_INFO MyGetIconInfo(hicon hIcon);

#endif


namespace draw2d
{


   icon::icon()
   {

      m_picon = nullptr;
      m_bAutoDelete = true;

   }


  






   icon::~icon()
   {

      if (m_bAutoDelete)
      {

         if (m_picon != nullptr)
         {

#ifdef WINDOWS_DESKTOP

            //for (auto point_i32 : m_iconmap)
            //{

            //   ::DestroyIcon((hicon)point.element2());

            //}


            m_picon.release();
            //::DestroyIcon((hicon)m_picon);

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


   windowing::icon * icon::get_windowing_icon()
   {

      return m_picon;

   }
   

   string icon::get_tray_icon_name()
   {

      return m_strAppTrayIcon;

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

      auto info = MyGetIconInfo((hicon)m_picon);

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


   ::size_i32 icon::get_size()
   {

      return m_size;

   }


   ::size_i32 icon::get_smaller_size(const ::size_i32 & size)
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


