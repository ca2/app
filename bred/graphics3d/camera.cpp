// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "camera.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/engine.h"


namespace graphics3d
{


   camera::camera()
   {

      m_sequence3WorldUp = {0.f, 1.f, 0.f};

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

      calculate_impact(m_matrixImpact);

      m_matrixInversedImpact = m_matrixImpact.inversed();

      calculate_projection(m_matrixProjection);

   }


   void camera::calculate_impact(::floating_matrix4 & matrixImpact)
   {

      matrixImpact = ::graphics3d::lookAt(this->position(), this->position() + this->front(), this->world_up());

   }


   void camera::calculate_projection(::floating_matrix4 & matrixProjection)
   {

      m_pengine->calculate_projection(matrixProjection, *this);

   }


}  // namespace graphics3d


