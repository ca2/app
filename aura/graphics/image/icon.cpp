#include "framework.h"
#include "icon.h"
#include "map.h"
#include "image.h"
#include "acme/platform/system.h"
#include "aura/windowing/icon.h"


namespace image
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


   void icon::initialize(::particle * pparticle)
   {

      ::matter::initialize(pparticle);

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
  //    if (m_size.cx() <= 0 || m_size.cy() <= 0 || m_size.cx() >= 512 || m_size.cy() >= 512)
  //    {

  //       m_size.cx() = 22;
  //       m_size.cy() = 22;

  //    }

//#endif

      m_sizea.predicate_sort([](auto & size1, auto & size2)
         {

            return size1.cx() < size2.cx();

         });

   }


   ::int_size icon::get_size()
   {

      if (m_sizea.is_empty())
      {

         return {};

      }

      return m_sizea[0];

   }


   ::image::image_pointer icon::image_source_image(const ::int_size & size)
   {

      bool bExists;

      if(::is_null(m_pimagemap))
      {

         m_pimagemap = system()->__create_new < size_image >();

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


   ::int_size icon::get_smaller_size(const ::int_size & size)
   {

      if (m_sizea.is_empty())
      {

         return {};

      }

      ::collection::index iFound = -1;

      for (::collection::index i = 0; i < m_sizea.get_size(); i++)
      {

         if (size.cx() < m_sizea[i].cx())
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

         return {};

      }

      return m_sizea[iFound];

   }


   /*::image::image_pointer icon::image::image_source_image(const concrete < ::int_size > & size) const
   {

      return ((icon *)this)->get_image(size);

   }*/


   // inline concrete < ::int_size > int_size(const ::double_size & sizeDst, const ::double_size & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->int_size(sizeDst, sizeSrc, eimageselection); }

   ::int_size icon::image_source_size(const ::double_size & sizeDst, enum_image_selection eimageselection) const
   {

      if (m_sizea.is_empty())
      {

         return ::int_size();

      }

      for (::collection::index i = 0; i < m_sizea.get_size(); i++)
      {

         if (sizeDst.cy() == m_sizea[i].cy())
         {

            return m_sizea[i];

         }

      }

      ::collection::index iFound = -1;

      if (eimageselection == e_image_selection_prefer_largest)
      {

         iFound = m_sizea.last_index();

      }
      else if (eimageselection >= e_image_selection_prefer_smaller)
      {

         iFound = m_sizea.first_index();

         double dRateSmaller = 1.0 / pow(2.0, (double)(int)(eimageselection - e_image_selection_prefer_smaller));

         for (::collection::index i = m_sizea.get_upper_bound(); i >= 0; i--)
         {

            if (m_sizea[i].cy() < dRateSmaller * sizeDst.cy())
            {

               iFound = i;

               break;

            }

         }

      }
      else
      {

         iFound = m_sizea.first_index();

         for (::collection::index i = 0; i < m_sizea.get_size(); i++)
         {

            if (m_sizea[i].cy() > sizeDst.cy())
            {

               iFound = i;

               break;

            }

         }

      }

      if (iFound < 0)
      {

         return int_size();

      }

      return m_sizea[iFound];

   }


   ::int_size icon::image_source_size() const
   { 
      
      return image_source_size(::double_size(), e_image_selection_default);
   
   }



} // namespace image


