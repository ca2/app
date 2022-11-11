#include "framework.h"


namespace aura
{


   savings::savings()
   {

   }

   savings::~savings()
   {

   }


   void savings::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   void savings::save(e_resource eresource)
   {
      m_eresourceflagsShouldSave.add(eresource);
   }

   void savings::try_to_save(e_resource eresource)
   {
      m_eresourceflagsShouldSave.add(eresource);
   }

   void savings::use(e_resource eresource)
   {
      m_eresourceflagsShouldSave.erase(eresource);
   }

   void savings::may_use(e_resource eresource)
   {
      m_eresourceflagsShouldSave.erase(eresource);
   }

   bool savings::should_save(e_resource eresource)
   {
      return m_eresourceflagsShouldSave.has(eresource);
   }

   bool savings::is_trying_to_save(e_resource eresource)
   {
      return m_eresourceflagsShouldSave.has(eresource);
   }

   void savings::warn(e_resource eresource)
   {
      m_eresourceflagsWarning.add(eresource);
   }

   void savings::clear_warning(e_resource eresource)
   {
      m_eresourceflagsWarning.erase(eresource);
   }

   bool savings::is_warning(e_resource eresource)
   {
      return m_eresourceflagsWarning.has(eresource);
   }

} // namespace aura
