// From _impl.h by camilo on 2022-08-27 13:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "output_purpose.h"
//#include "interaction.h"


// fps_interest::fps_interest(::user::interaction * pinteraction) :
//    m_pinteraction(pinteraction)
// {

//    m_pinteraction->add_fps_interest(this);

// }


// fps_interest::~fps_interest()
// {

//    m_pinteraction->erase_fps_interest(this);

// }






   // ::graphics::enum_output_purpose          m_epurpose = e_graphical_output_purpose_demand;

   // ::particle_pointer               m_pparticle;

namespace graphics
{


   output_purpose::output_purpose(enum_output_purpose eoutputpurpose) :
      m_egraphicsoutputpurpose(eoutputpurpose)
   {

      set_graphical_output_purpose_originator(this);

   }


   output_purpose::output_purpose(::particle * pparticleGraphicalOutputPurposeOriginator, enum_output_purpose eoutputpurpose) :
      m_egraphicsoutputpurpose(eoutputpurpose)
   {

      set_graphical_output_purpose_originator(pparticleGraphicalOutputPurposeOriginator);
      initialize(pparticleGraphicalOutputPurposeOriginator);

   }


   output_purpose::~output_purpose()
   {
      
      release_graphical_output_purpose_originator();

   }


   void output_purpose::destroy()
   {
      
      release_graphical_output_purpose_originator();

      ::particle::destroy();

   }


   void output_purpose::set_graphical_output_purpose_originator(::particle * pparticle)
   {

      release_graphical_output_purpose_originator();

      if (pparticle != this && ::is_set(pparticle))
      {

#if REFERENCING_DEBUGGING

         m_preferer = __refdbg_add_referer(pparticle);

#endif

         pparticle->increment_reference_count();

      }
      
      m_pparticleGraphicalOutputPurposeOriginator2 = pparticle;

   }


   void output_purpose::release_graphical_output_purpose_originator()
   {

      if (::is_set(m_pparticleGraphicalOutputPurposeOriginator2))
      {

         if (m_pparticleGraphicalOutputPurposeOriginator2 != this)
         {

            __refdbg_add_releaser(m_preferer)

            m_pparticleGraphicalOutputPurposeOriginator2->release();

         }

         m_pparticleGraphicalOutputPurposeOriginator2 = nullptr;

      }

   }


   ::particle * output_purpose::get_graphical_output_purpose_originator()
   {

      return m_pparticleGraphicalOutputPurposeOriginator2;

   }


//   enum_output_purpose output_purpose::_graphical_output_purpose()
//   {
//
//      return m_epurpose2;
//
//   }
//
//
//   ::particle * output_purpose_particle::graphical_output_purpose_particle()
//   {
//
//      return m_pparticle;
//
//   }


} // namespace graphics



