#include "platform.h"
#include "extension.h"
#include "map.h"
#include "acme/graphics/image/frame_array.h"


namespace image
{


   image_extension::image_extension()
   {

      m_dSpeed = 1.0;
      m_pmap = nullptr;
      m_pframea = nullptr;

   }


   image_extension::~image_extension()
   {

      ::release(m_pframea);
      ::release(m_pmap);

   }


} // namespace image



