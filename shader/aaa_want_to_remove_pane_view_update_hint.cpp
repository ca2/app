#include "framework.h"


namespace simple_shader
{


   ::update::update()
   {
      m_eview = impact_none;
      m_etype = TypeNone;

   }


   ::update::~::update()
   {

   }


   bool ::update::is_type_of(enum_type enum_type)
   {

      return m_etype == enum_type;

   }


   void ::update::set_type(enum_type enum_type)
   {

      m_etype = enum_type;

   }


} // namespace simple_shader



