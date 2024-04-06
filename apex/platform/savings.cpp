#include "framework.h"
#include "savings.h"


namespace apex
{


   savings::savings()
   {

   }

   savings::~savings()
   {

   }


   void savings::initialize(::particle * pparticle)
   {

      //auto estatus =
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   
   void savings::save(enum_resource eresource)
   {

      m_eresourceflagsShouldSave.add(eresource);

   }


   void savings::try_to_save(enum_resource eresource)
   {

      m_eresourceflagsShouldSave.add(eresource);

   }


   void savings::use(enum_resource eresource)
   {

      m_eresourceflagsShouldSave.erase(eresource);

   }


   void savings::may_use(enum_resource eresource)
   {

      m_eresourceflagsShouldSave.erase(eresource);

   }


   bool savings::should_save(enum_resource eresource)
   {

      return m_eresourceflagsShouldSave.has(eresource);

   }


   bool savings::is_trying_to_save(enum_resource eresource)
   {

      return m_eresourceflagsShouldSave.has(eresource);

   }


   void savings::warn(enum_resource eresource)
   {

      m_eresourceflagsWarning.add(eresource);

   }


   void savings::clear_warning(enum_resource eresource)
   {

      m_eresourceflagsWarning.erase(eresource);

   }


   bool savings::is_warning(enum_resource eresource)
   {

      return m_eresourceflagsWarning.has(eresource);

   }


} // namespace apex



