#include "framework.h"
#include "image_extension.h"
#include "image_frame_array.h"
#include "image_map.h"


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



