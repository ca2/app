#pragma once


#include "image_source.h"


using hicon = void *;

class size_image;

namespace draw2d
{


   /// <summary>
   /// icon * -> image_source_pointer concept
   /// </summary>
   class CLASS_DECL_AURA icon :
      virtual public ::image_source_interface
   {
   protected:


      friend class ::windowing::icon;


      __pointer(::windowing::icon)              m_pwindowingicon;
      __pointer(size_image)                     m_pimagemap;
      array < concrete < ::size_i32 > >         m_sizea;
      // Sizes of Readily Available Icons in Increasing Sorting Order
      bool                                      m_bAutoDelete;
      string                                    m_strAppTrayIcon;


   public:
      

      icon();
      ~icon() override;


      void initialize(::object * pobject) override;


      virtual void initialize_with_windowing_icon(::windowing::icon * picon);


      virtual windowing::icon * get_windowing_icon();


      string get_tray_icon_name();


      ::size_i32 get_size();


      ::size_i32 get_smaller_size(const ::size_i32 & size);


      virtual void on_update_icon();


      inline ::size_f64 origin() const { return ::size_f64(); }


//      image_pointer get_image(const concrete < ::size_i32 > & size);


      image_pointer image_source_image(const concrete < ::size_i32 > & size) override;


      // inline concrete < ::size_i32 > size_i32(const ::size_f64 & sizeDst, const ::size_f64 & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->size_i32(sizeDst, sizeSrc, eimageselection); }

      concrete < ::size_i32 > image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const override;

      
      concrete < ::size_i32 > image_source_size() const override;

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public i32_map < icon * >
   {
   public:

   };


} // namespace draw2d




