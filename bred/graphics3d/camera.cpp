// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "camera.h"
#include "bred/gpu/context.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/engine_instance.h"


namespace graphics3d
{


   camera::camera()
   {

      m_sequence3WorldUp = {0.f, 1.f, 0.f};

   }



   camera::~camera()
   {


   }


      void camera::initialize_camera(const ::floating_sequence3 &position,
                                                const ::graphics3d::floating_rotation &rotation,
                                                const floating_angle &zoom)
   {

      m_sequence3Position = position;

      m_rotation = rotation;

      m_angleFovY = zoom;
   }




   void camera::update_vectors() 
   {

      auto pgpucontext = m_pgraphics3dengineinstance->gpu_context();

      //m_sequence3WorldUp = {0.f, m_pgraphics3dengineinstance->m_fYScale, 0.f};

      m_sequence3Front = pgpucontext->front(m_rotation);

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

      m_pgraphics3dengineinstance->calculate_impact(matrixImpact, *this);

   }


   void camera::calculate_projection(::floating_matrix4 & matrixProjection)
   {

      auto size = m_pgraphics3dengineinstance->gpu_context()->size();

      m_fAspectRatio = size.aspect_ratio<::f32>();

      m_pgraphics3dengineinstance->calculate_projection(matrixProjection, *this);

   }


}  // namespace graphics3d


