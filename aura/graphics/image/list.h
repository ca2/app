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


         ::int_rectangle         m_rectangle;
         ::image::image_pointer         m_pimage;

      };


      int_size                         m_size;
      int                              m_iSize;
      int                              m_iGrow;
      ::pointer<::image::image>               m_pimage;


      ::pointer<::image::image>               m_pimageWork;
      ::pointer<::image::image>               m_pimageWork2;
      ::pointer<::image::image>               m_pimageWork3;


      image_list();
      image_list(const image_list & imagelist);
      ~image_list() override;


      virtual bool create(int cx, int cy);
      virtual bool create(int cx, int cy, unsigned int nFlags, int nInitial, int nGrow);
      virtual void realize(::draw2d::graphics * pgraphics) const;


      virtual int reserve_image(int iItem = -1);


      //virtual int _set(int iItem, ::image::icon * picon);
      virtual int set(int iItem, const ::image::image_drawing & imagedrawing);
      //   virtual int sete(int iItem, ::file::file * pfile);
      //   virtual int set_icon(int iItem, ::file::file * pfile);

      //template < image_list_source_pointer IMAGE_LIST_SOURCE_POINTER >
      //int add(IMAGE_LIST_SOURCE_POINTER psource, const ::int_rectangle & rectangleSource = ::int_rectangle())
      //{

      //   return _add(psource);

      //}

      inline int add(const ::image::image_drawing & imagedrawing) { return set(-1, imagedrawing); }
      //   inline int add_file(::file::file * pfile) { return set_file(-1, pfile); }
      //   inline int add_icon(::file::file * pfile) { return set_icon(-1, pfile); }
      //inline int _add(::image::icon * picon) { return _set(-1, picon); }

      // inline int add(::windowing::icon * picon) { return set(iItem, picon, x, y); }

      //int add_file(::payload payloadFile, int iItem = -1);
      ///int add_matter(const ::string & pcsz, ::particle * pparticle = nullptr, int iItem = -1);

      //int add_std_matter(const ::string & pcsz, int iItem = -1);

      //int add_image(image_list * pil, int iImage, int iItem = - 1);

      //template < typename PRED >
      //int predicate_add_image(PRED pred, image_list * pil, int iImage, int iItem = -1)
      //{

      //   auto pimage = pil->get_image(iImage);

      //   pred(pimage);

      //   return add_image(pimage, 0, 0, iItem);

      //}


      virtual ::image::image_pointer get_image(int iImage);


      virtual void color_blend(image_list* pimagelistSource, const ::color::color& color, const class ::opacity& opacity);


      virtual void draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, int iFlag);
      virtual void draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, int iFlag, const class ::opacity& opacity);
      virtual void draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, ::double_size sz, const ::double_point & pointOffset, int iFlag);
      virtual void _draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, ::double_size sz, const ::double_point & pointOffset, int iFlag);
      virtual int get_image_count() const;

      virtual void copy_from(const image_list * plist);

      virtual void get_image_info(int nImage, info * pinfo) const;

      virtual void erase_all();

      image_list & operator = (const image_list & imagelist);

      virtual bool _grow(int iAddUpHint = -1);
      virtual int _get_alloc_count();

   };


} // namespace image



