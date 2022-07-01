#pragma once


#include "drawing.h"


class CLASS_DECL_AURA image_list :
   virtual public ::object
{
public:


   class CLASS_DECL_AURA info
   {
   public:


      ::rectangle_i32         m_rectangle;
      ::image_pointer         m_pimage;

   };


   size_i32                         m_size;
   i32                              m_iSize;
   i32                              m_iGrow;
   __composite(::image)             m_pimage;


   __composite(::image)             m_pimageWork;
   __composite(::image)             m_pimageWork2;
   __composite(::image)             m_pimageWork3;


   image_list();
   image_list(const image_list & imagelist);
   ~image_list() override;


   virtual bool create(i32 cx, i32 cy);
   virtual bool create(i32 cx, i32 cy, ::u32 nFlags, i32 nInitial, i32 nGrow);
   virtual void realize(::draw2d::graphics * pgraphics) const;


   virtual i32 reserve_image(int iItem = -1);


   //virtual i32 _set(int iItem, ::draw2d::icon * picon);
   virtual i32 set(int iItem, image_drawing imagedrawing);
//   virtual i32 sete(int iItem, ::file::file * pfile);
//   virtual i32 set_icon(int iItem, ::file::file * pfile);

   //template < image_list_source_pointer IMAGE_LIST_SOURCE_POINTER >
   //i32 add(IMAGE_LIST_SOURCE_POINTER psource, const ::rectangle_i32 & rectangleSource = ::rectangle_i32())
   //{

   //   return _add(psource);

   //}

   inline i32 add(image_drawing imagedrawing) { return set(-1, imagedrawing); }
//   inline i32 add_file(::file::file * pfile) { return set_file(-1, pfile); }
//   inline i32 add_icon(::file::file * pfile) { return set_icon(-1, pfile); }
   //inline i32 _add(::draw2d::icon * picon) { return _set(-1, picon); }

   // inline i32 add(::windowing::icon * picon) { return set(iItem, picon, x, y); }

   //i32 add_file(::payload payloadFile, int iItem = -1);
   ///i32 add_matter(const ::string & pcsz, ::object * pobject = nullptr, int iItem = -1);

   //i32 add_std_matter(const ::string & pcsz, int iItem = -1);

   //i32 add_image(image_list * pil, int iImage, int iItem = - 1);

   //template < typename PRED >
   //i32 predicate_add_image(PRED pred, image_list * pil, int iImage, int iItem = -1)
   //{

   //   auto pimage = pil->get_image(iImage);

   //   pred(pimage);

   //   return add_image(pimage, 0, 0, iItem);

   //}


   virtual ::image_pointer get_image(int iImage);


   virtual void color_blend(image_list* pimagelistSource, const ::color::color& color, const ::opacity& opacity);


   virtual void draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag);
   virtual void draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag, const ::opacity& opacity);
   virtual void draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, ::size_f64 sz, const ::point_f64 & pointOffset, i32 iFlag);
   virtual void _draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, ::size_f64 sz, const ::point_f64 & pointOffset, i32 iFlag);
   virtual i32 get_image_count() const;

   virtual void copy_from(const image_list * plist);

   virtual void get_image_info(i32 nImage, info * pinfo) const;

   virtual void erase_all();

   image_list & operator = (const image_list & imagelist);

   virtual bool _grow(int iAddUpHint = -1);
   virtual i32 _get_alloc_count();

};



