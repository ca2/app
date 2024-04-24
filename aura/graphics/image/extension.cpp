#include "framework.h"
#include "extension.h"
#include "frame_array.h"
#include "map.h"


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



