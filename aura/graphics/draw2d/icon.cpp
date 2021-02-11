#include "framework.h"




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

            //for (auto point : m_iconmap)
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

      return estatus;

   }


   void icon::initialize_with_windowing_icon(::windowing::icon * picon)
   {

      m_picon = picon;

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

         return;

      }

#ifdef WINDOWS_DESKTOP

      m_picon->get_sizes(m_sizea);

#else

      // building icon not supported (size > 512 :-)
      if (m_size.cx <= 0 || m_size.cy <= 0 || m_size.cx >= 512 || m_size.cy >= 512)
      {

         m_size.cx = 22;
         m_size.cy = 22;

      }

#endif

      m_sizea.pred_sort([](auto & size1, auto & size2)
         {

            return size1.cx < size2.cx;

         });

   }


   ::size_i32 icon::get_size()
   {

      if (m_sizea.is_empty())
      {

         return nullptr;

      }

      return m_sizea[0];

   }


   image * icon::get_image(const concrete < ::size_i32 > & size)
   {

      bool bExists;

      __defer_construct_new(m_pimagemap);

      auto & pimage = m_pimagemap->get(size, bExists);

      if (bExists)
      {

         return pimage;

      }

      if (!m_picon)
      {

         return nullptr;

      }

      pimage = m_picon->get_image(size);

      if (!pimage)
      {

         return nullptr;

      }

      return pimage;

   }


   ::size_i32 icon::get_smaller_size(const ::size_i32 & size)
   {

      if (m_sizea.is_empty())
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


