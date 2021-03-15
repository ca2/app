#include "framework.h"


namespace apex
{


   savings::savings()
   {

   }

   savings::~savings()
   {

   }


   ::e_status savings::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::object::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

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

      m_eresourceflagsShouldSave.remove(eresource);

   }


   void savings::may_use(enum_resource eresource)
   {

      m_eresourceflagsShouldSave.remove(eresource);

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

      m_eresourceflagsWarning.remove(eresource);

   }


   bool savings::is_warning(enum_resource eresource)
   {

      return m_eresourceflagsWarning.has(eresource);

   }


} // namespace apex



