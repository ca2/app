#include "framework.h"
#include "cursor.h"
#include "image.h"


//#include "acme/operating_system.h"


namespace image
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



   void cursor_alloc(::particle * pparticle,cursor_pointer & pcursor,int xHotspot,int yHotspot)
   {

      pparticle->__construct(pcursor);

      pcursor->m_szHotspotOffset.cx() = xHotspot;

      pcursor->m_szHotspotOffset.cy() = yHotspot;

   }


   ::image::image_pointer cursor_get_image(cursor * pcursor)
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


   ::image::image_pointer cursor::image_source_image(const ::size_i32 & size)
   {
      
      return m_pimage->get_image(size); 
   
   }


   ::size_i32 cursor::image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const
   { 
      
      return m_pimage->image_source_size(sizeDst, eimageselection); 
   
   }


   ::size_i32 cursor::image_source_size() const
   {
      
      return m_pimage->size(); 
   
   }


} // namespace image



