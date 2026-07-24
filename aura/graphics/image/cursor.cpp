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



   void cursor_alloc(::particle * pparticle,cursor_pointer & pcursor,::i32 xHotspot,::i32 yHotspot)
   {

      pparticle->constructø(pcursor);

      pcursor->m_szHotspotOffset.cx = xHotspot;

      pcursor->m_szHotspotOffset.cy = yHotspot;

   }


   ::image::image_pointer cursor_get_image(cursor * pcursor)
   {

      return pcursor->m_pimage;

   }


   ::draw2d::graphics_lease cursor::acquire_graphics() const
   {

      return m_pimage->acquire_graphics();

   }


   ::draw2d::graphics_lease cursor::acquire_graphics(const ::f64_size & sizeHint)
   {

      return m_pimage->acquire_graphics(sizeHint);

   }


   ::image::image_pointer cursor::image_source_image(const ::i32_size & size)
   {
      
      return m_pimage->get_image(size); 
   
   }


   ::i32_size cursor::image_source_size(const ::f64_size & sizeDst, enum_image_selection eimageselection) const
   { 
      
      return m_pimage->image_source_size(sizeDst, eimageselection); 
   
   }


   ::i32_size cursor::image_source_size() const
   {
      
      return m_pimage->size(); 
   
   }


} // namespace image



