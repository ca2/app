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

   // ::pointer < ::particle >               m_pparticle;

namespace graphics
{


   output_purpose::output_purpose(enum_output_purpose eoutputpurpose) :
      m_pparticleGraphicalOutputPurposeOriginator(this),
      m_egraphicsoutputpurpose(eoutputpurpose)
   {


   }


   output_purpose::output_purpose(::particle * pparticleGraphicalOutputPurposeOriginator, enum_output_purpose eoutputpurpose) :
      m_pparticleGraphicalOutputPurposeOriginator(pparticleGraphicalOutputPurposeOriginator),
      m_egraphicsoutputpurpose(eoutputpurpose)
   {

      initialize(pparticleGraphicalOutputPurposeOriginator);

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



