#pragma once


#include "aura/graphics/image/source.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/geometry2d/_collection.h"


using hicon = void *;


class size_image;


namespace image
{


   /// <summary>
   /// icon * -> ::image::image_source_pointer concept
   /// </summary>
   class CLASS_DECL_AURA icon :
      virtual public ::image::image_source_interface
   {
   protected:


      friend class ::windowing::icon;


      ::pointer<::windowing::icon>              m_pwindowingicon;
      ::pointer<size_image>                     m_pimagemap;
      ::int_size_array                          m_sizea;
      // Sizes of Readily Available Icons in Increasing Sorting Order
      bool                                      m_bAutoDelete;
      string                                    m_strAppTrayIcon;


   public:
      

      icon();
      ~icon() override;


      void initialize(::particle * pparticle) override;


      virtual void initialize_with_windowing_icon(::windowing::icon * picon);


      virtual windowing::icon * get_windowing_icon();


      string get_tray_icon_name();


      ::int_size get_size();


      ::int_size get_smaller_size(const ::int_size & size);


      virtual void on_update_icon();


      inline ::double_size origin() const { return ::double_size(); }


//      ::image::image_pointer get_image(const concrete < ::int_size > & size);


      ::image::image_pointer image_source_image(const ::int_size& size) override;


      // inline concrete < ::int_size > int_size(const ::double_size & sizeDst, const ::double_size & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->int_size(sizeDst, sizeSrc, eimageselection); }

      ::int_size image_source_size(const ::double_size & sizeDst, enum_image_selection eimageselection) const override;

      
      ::int_size image_source_size() const override;

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public int_map < icon * >
   {
   public:

   };


} // namespace image



