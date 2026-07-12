#pragma once


#include "aura/graphics/image/source.h"
#include "acme/prototype/collection/integer_map.h"
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
      ::i32_size_array                          m_sizea;
      // Sizes of Readily Available Icons in Increasing Sorting Order
      bool                                      m_bAutoDelete;
      string                                    m_strAppTrayIcon;


   public:
      

      icon();
      ~icon() override;

      bool _is_ok() const override;

      void initialize(::particle * pparticle) override;


      virtual void initialize_with_windowing_icon(::windowing::icon * picon);


      virtual windowing::icon * get_windowing_icon();


      string get_tray_icon_name();


      ::i32_size get_size();


      ::i32_size get_smaller_size(const ::i32_size & size);


      virtual void on_update_icon();


      inline ::f64_size origin() const { return ::f64_size(); }


//      ::image::image_pointer get_image(const concrete < ::i32_size > & size);


      ::image::image_pointer image_source_image(const ::i32_size& size) override;


      // inline concrete < ::i32_size > i32_size(const ::f64_size & sizeDst, const ::f64_size & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->i32_size(sizeDst, sizeSrc, eimageselection); }

      ::i32_size image_source_size(const ::f64_size & sizeDst, enum_image_selection eimageselection) const override;

      
      ::i32_size image_source_size() const override;

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public i32_map < icon * >
   {
   public:

   };


} // namespace image



