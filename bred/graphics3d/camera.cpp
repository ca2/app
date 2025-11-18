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


   void camera::update_vectors() 
   {

      m_sequence3Front = m_quaternionRotation.front();

      m_sequence3Right = m_sequence3Front.front_right(m_sequence3WorldUp);

      m_sequence3Up = m_sequence3Right.right_up(m_sequence3Front);
      
   }
   
   
   
   void camera::update()
   {



   }


}  // namespace graphics3d


