// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 07:16 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "key_map.h"
#include "aura/platform/application.h"
#include "bred/user/user/graphics3d.h"


namespace graphics3d
{



   ::user::enum_key_state key_map::key(::graphics3d::enum_key ekey)
   {

      return m_pimpact->get_key_state(m_ekeya[ekey]);

   }


} // namespace graphics3d


