#include "framework.h"


namespace browser
{


   ::update::update()
   {

      m_eview = impact_none;

      m_etype = type_none;

   }


   ::update::~::update()
   {

   }


   bool ::update::is_type_of(e_type e_type)
   {

      return m_etype == e_type;

   }


   void ::update::set_type(e_type e_type)
   {

      m_etype = e_type;

   }


} // namespace browser



