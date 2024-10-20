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
      ::size_i32_array                          m_sizea;
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


      ::size_i32 get_size();


      ::size_i32 get_smaller_size(const ::size_i32 & size);


      virtual void on_update_icon();


      inline ::size_f64 origin() const { return ::size_f64(); }


//      ::image::image_pointer get_image(const concrete < ::size_i32 > & size);


      ::image::image_pointer image_source_image(const ::size_i32& size) override;


      // inline concrete < ::size_i32 > size_i32(const ::size_f64 & sizeDst, const ::size_f64 & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->size_i32(sizeDst, sizeSrc, eimageselection); }

      ::size_i32 image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const override;

      
      ::size_i32 image_source_size() const override;

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public i32_map < icon * >
   {
   public:

   };


} // namespace image



