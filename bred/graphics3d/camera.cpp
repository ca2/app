// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "camera.h"


namespace graphics3d
{


   camera::camera()
   {



   }



   camera::~camera()
   {


   }


   floating_sequence3 camera::position()
   {

      return m_vec3Position;

   }


   floating_sequence3 camera::rotation()
   {

      return m_vec3Rotation;

   }


   ::block camera::as_block()
   {

      return {};

   }

}  // namespace graphics3d


