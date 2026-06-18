#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/geometry2d/rectangle.h"

namespace image
{


   class CLASS_DECL_AURA image_list :
      virtual public ::object
   {
   public:


      class CLASS_DECL_AURA info
      {
      public:


         ::i32_rectangle         m_rectangle;
         ::image::image_pointer         m_pimage;

      };


      i32_size                         m_size;
      ::i32                              m_iSize;
      ::i32                              m_iGrow;
      ::pointer<::image::image>               m_pimage;


      ::pointer<::image::image>               m_pimageWork;
      ::pointer<::image::image>               m_pimageWork2;
      ::pointer<::image::image>               m_pimageWork3;


      image_list();
      image_list(const image_list & imagelist);
      ~image_list() override;


      virtual bool create(::i32 cx, ::i32 cy);
      virtual bool create(::i32 cx, ::i32 cy, ::u32 nFlags, ::i32 nInitial, ::i32 nGrow);
      virtual void realize(::draw2d::graphics * pgraphics) const;


      virtual ::i32 reserve_image(::i32 iItem = -1);


      bool _is_ok() const override;


      //virtual ::i32 _set(::i32 iItem, ::image::icon * picon);
      virtual ::i32 set(::i32 iItem, const ::image::image_drawing & imagedrawing);
      //   virtual ::i32 sete(::i32 iItem, ::file::file * pfile);
      //   virtual ::i32 set_icon(::i32 iItem, ::file::file * pfile);

      //template < image_list_source_pointer IMAGE_LIST_SOURCE_POINTER >
      //::i32 add(IMAGE_LIST_SOURCE_POINTER psource, const ::i32_rectangle & rectangleSource = ::i32_rectangle())
      //{

      //   return _add(psource);

      //}

      inline ::i32 add(const ::image::image_drawing & imagedrawing) { return set(-1, imagedrawing); }
      //   inline ::i32 add_file(::file::file * pfile) { return set_file(-1, pfile); }
      //   inline ::i32 add_icon(::file::file * pfile) { return set_icon(-1, pfile); }
      //inline ::i32 _add(::image::icon * picon) { return _set(-1, picon); }

      // inline ::i32 add(::windowing::icon * picon) { return set(iItem, picon, x, y); }

      //::i32 add_file(::payload payloadFile, ::i32 iItem = -1);
      ///::i32 add_matter(const ::scoped_string & scopedstr, ::particle * pparticle = nullptr, ::i32 iItem = -1);

      //::i32 add_std_matter(const ::scoped_string & scopedstr, ::i32 iItem = -1);

      //::i32 add_image(image_list * pil, ::i32 iImage, ::i32 iItem = - 1);

      //template < typename PRED >
      //::i32 predicate_add_image(PRED pred, image_list * pil, ::i32 iImage, ::i32 iItem = -1)
      //{

      //   auto pimage = pil->get_image(iImage);

      //   pred(pimage);

      //   return add_image(pimage, 0, 0, iItem);

      //}


      virtual ::image::image_pointer get_image(::i32 iImage);


      virtual void color_blend(image_list* pimagelistSource, const ::color::color& color, const class ::opacity& opacity);


      virtual void draw(::draw2d::graphics * pgraphics, ::i32 iImage, const ::f64_point & point, ::i32 iFlag);
      virtual void draw(::draw2d::graphics * pgraphics, ::i32 iImage, const ::f64_point & point, ::i32 iFlag, const class ::opacity& opacity);
      virtual void draw(::draw2d::graphics * pgraphics, ::i32 iImage, const ::f64_point & point, ::f64_size sz, const ::f64_point & pointOffset, ::i32 iFlag);
      virtual void _draw(::draw2d::graphics * pgraphics, ::i32 iImage, const ::f64_point & point, ::f64_size sz, const ::f64_point & pointOffset, ::i32 iFlag);
      virtual ::i32 get_image_count() const;

      virtual void copy_from(const image_list * plist);

      virtual void get_image_info(::i32 nImage, info * pinfo) const;

      virtual void erase_all();

      image_list & operator = (const image_list & imagelist);

      virtual bool _grow(::i32 iAddUpHint = -1);
      virtual ::i32 _get_alloc_count();

   };


} // namespace image



