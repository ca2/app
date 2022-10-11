#include "framework.h"
#include "acme/operating_system.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
#include "cursor.h"
#include "image.h"


namespace draw2d
{


   cursor::cursor()
   {

      m_bDefaultCursor = false;

   }


   cursor::~cursor()
   {


   }


   void cursor::destroy()
   {

      m_pimage.release();

      m_pimageCursor.release();

      //auto estatus =
      
      ::matter::destroy();

      //return estatus;

   }


   ::windowing::cursor * cursor::get_cursor()
   {

      return m_pcursor;

   }


//
//   bool cursor::initialize_system_default()
//   {
//
//      return true;
//
//   }
//
//
//#endif



   void cursor_alloc(::object * pobject,cursor_pointer & pcursor,int xHotspot,int yHotspot)
   {

      pobject->__construct(pcursor);

      pcursor->m_szHotspotOffset.cx = xHotspot;

      pcursor->m_szHotspotOffset.cy = yHotspot;

   }


   image_pointer cursor_get_image(cursor * pcursor)
   {

      return pcursor->m_pimage;

   }


   ::draw2d::graphics *cursor::g() const
   {

      return m_pimage->g();

   }


   ::draw2d::graphics *cursor::g(const ::size_f64 & sizeHint)
   {

      return m_pimage->g(sizeHint);

   }


   ::image_pointer cursor::image_source_image(const concrete < ::size_i32 > & concreteSize)
   {
      
      return m_pimage->get_image(concreteSize); 
   
   }


   concrete < ::size_i32 > cursor::image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const
   { 
      
      return m_pimage->image_source_size(sizeDst, eimageselection); 
   
   }


   concrete < ::size_i32 > cursor::image_source_size() const
   {
      
      return m_pimage->size(); 
   
   }


} // namespace draw2d



