#include "framework.h"
#include "icon.h"
#include "map.h"
#include "image.h"


namespace draw2d
{


   icon::icon()
   {

      m_bAutoDelete = true;

   }


   icon::~icon()
   {

      if (m_bAutoDelete)
      {

         if (::is_set(m_pwindowingicon))
         {

#ifdef WINDOWS_DESKTOP

            //for (auto point : m_iconmap)
            //{

            //   ::DestroyIcon((hicon)point.element2());

            //}


            m_pwindowingicon.release();
            //::DestroyIcon((hicon)m_picon);

#else

            //throw ::exception(todo);

#endif


         }

      }

   }


   void icon::initialize(::object * pobject)
   {

      ::matter::initialize(pobject);

   }


   void icon::initialize_with_windowing_icon(::windowing::icon * pwindowingicon)
   {

      m_pwindowingicon = pwindowingicon;

      on_update_icon();

      //return ::success;

   }


   windowing::icon * icon::get_windowing_icon()
   {

      return m_pwindowingicon;

   }



   string icon::get_tray_icon_name()
   {

      return m_strAppTrayIcon;

   }


   void icon::on_update_icon()
   {

      if (!m_pwindowingicon)
      {

         return;

      }

//#ifdef WINDOWS_DESKTOP

      m_pwindowingicon->get_sizes(m_sizea);

//#else

      // building icon not supported (size > 512 :-)
  //    if (m_size.cx <= 0 || m_size.cy <= 0 || m_size.cx >= 512 || m_size.cy >= 512)
  //    {

  //       m_size.cx = 22;
  //       m_size.cy = 22;

  //    }

//#endif

      m_sizea.predicate_sort([](auto & size1, auto & size2)
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


   image_pointer icon::image_source_image(const concrete < ::size_i32 > & size)
   {

      bool bExists;

      if(::is_null(m_pimagemap))
      {

         m_pimagemap = m_psystem->__create_new < size_image >();

      }

      auto & pimage = m_pimagemap->get(size, bExists);

      if (bExists)
      {

         return pimage;

      }

      if (!m_pwindowingicon)
      {

         return nullptr;

      }

      pimage = m_pwindowingicon->get_image(size);

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


   /*image_pointer icon::image_source_image(const concrete < ::size_i32 > & size) const
   {

      return ((icon *)this)->get_image(size);

   }*/


   // inline concrete < ::size_i32 > size_i32(const ::size_f64 & sizeDst, const ::size_f64 & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->size_i32(sizeDst, sizeSrc, eimageselection); }

   concrete < ::size_i32 > icon::image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const
   {

      if (m_sizea.is_empty())
      {

         return ::size_i32();

      }

      for (::index i = 0; i < m_sizea.get_size(); i++)
      {

         if (sizeDst.cy == m_sizea[i].cy)
         {

            return m_sizea[i];

         }

      }

      ::index iFound = -1;

      if (eimageselection == e_image_selection_prefer_largest)
      {

         iFound = m_sizea.last_index();

      }
      else if (eimageselection >= e_image_selection_prefer_smaller)
      {

         iFound = m_sizea.first_index();

         double dRateSmaller = 1.0 / pow(2.0, (double)(int)(eimageselection - e_image_selection_prefer_smaller));

         for (::index i = m_sizea.get_upper_bound(); i >= 0; i--)
         {

            if (m_sizea[i].cy < dRateSmaller * sizeDst.cy)
            {

               iFound = i;

               break;

            }

         }

      }
      else
      {

         iFound = m_sizea.first_index();

         for (::index i = 0; i < m_sizea.get_size(); i++)
         {

            if (m_sizea[i].cy > sizeDst.cy)
            {

               iFound = i;

               break;

            }

         }

      }

      if (iFound < 0)
      {

         return size_i32();

      }

      return m_sizea[iFound];

   }


   concrete < ::size_i32 > icon::image_source_size() const
   { 
      
      return image_source_size(::size_f64(), e_image_selection_default);
   
   }



} // namespace draw2d


