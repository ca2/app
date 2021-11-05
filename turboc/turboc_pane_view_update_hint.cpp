#include "framework.h"


namespace turboc
{


   ::impact_update::impact_update()
   {

   }


   ::impact_update::~::impact_update()
   {

   }


   bool ::impact_update::is_type_of(enum_type enum_type)
   {

      return m_etype == enum_type;

   }


   void ::impact_update::set_type(enum_type enum_type)
   {

      m_etype = enum_type;

   }


} // namespace turboc



