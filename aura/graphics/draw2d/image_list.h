#pragma once


class CLASS_DECL_AURA image_list :
   virtual public ::object
{
public:


   class CLASS_DECL_AURA info
   {
   public:


      ::rectangle_i32               m_rectangle;
      ::image_pointer      m_pimage;

   };


   size_i32                          m_size;
   i32                           m_iSize;
   i32                           m_iGrow;
   __composite(::image)             m_pimage;


   __composite(::image)             m_pimageWork;
   __composite(::image)             m_pimageWork2;
   __composite(::image)             m_pimageWork3;


   image_list();
   image_list(const image_list & imagelist);
   virtual ~image_list();


   bool create(i32 cx, i32 cy);
   bool create(i32 cx, i32 cy, ::u32 nFlags, i32 nInitial, i32 nGrow);
   bool realize(::draw2d::graphics * pgraphics) const;
   //bool create(const char * pszBitmapID, i32 cx, i32 nGrow, ::color::color crMask);


   i32 reserve_image(int iItem = -1);

   i32 add(::draw2d::icon * picon, int iItem = -1);
   i32 add(::windowing::icon * picon, int iItem = -1);
   i32 add_icon(::payload varFile, int iItem = -1);
   i32 add_image(::image * pimage, int x = 0, int y = 0, int iItem = -1);
   ///i32 add_icon_os_data(void * p, int iItem = -1);
   i32 add_matter_icon(const char * pcszMatter, int iItem = -1);

   i32 add_file(::payload varFile, int iItem = -1);
   ///i32 add_matter(const char * pcsz, ::object * pobject = nullptr, int iItem = -1);

   i32 add_std_matter(const char * pcsz, int iItem = -1);

   //i32 add_image(image_list * pil, int iImage, int iItem = - 1);

   //template < typename PRED >
   //i32 predicate_add_image(PRED pred, image_list * pil, int iImage, int iItem = -1)
   //{

   //   auto pimage = pil->get_image(iImage);

   //   pred(pimage);

   //   return add_image(pimage, 0, 0, iItem);

   //}


   ::image_pointer get_image(int iImage);


   virtual bool color_blend(image_list* pimagelistSource, const ::color::color& color, const ::opacity& opacity);


   bool draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag);
   bool draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag, const ::opacity& opacity);
   bool draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, ::size_f64 sz, const ::point_f64 & pointOffset, i32 iFlag);
   i32 get_image_count() const;

   void copy_from(const image_list * plist);

   ::e_status get_image_info(i32 nImage, info * pinfo) const;

   void erase_all();

   image_list & operator = (const image_list & imagelist);

   bool _grow(int iAddUpHint = -1);
   i32 _get_alloc_count();

};





