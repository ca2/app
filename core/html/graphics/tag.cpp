#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_graphics.h"
#endif



namespace html
{


   tag::tag(tag * pparent) :
      base(pparent)
   {
   }

   tag::~tag()
   {
      for(i32 i = 0; i < m_baseptra.get_size(); i++)
      {
         delete m_baseptra[i];
      }
   }

   attribute_array & tag::attra()
   {
      return m_attra;
   }


   void tag::set_name(id idName)
   {

      m_idName = idName;

   }


   id tag::get_name()
   {

      return m_idName;

   }


   attribute * tag::get_attr(id idName)
   {

      return m_attra.get(idName);

   }


   string tag::get_attr_value(id idName)
   {

      return attra().get_value(idName);

   }

   base::type tag::get_type()
   {

      return type_tag;

   }

   base_ptr_array & tag::baseptra()
   {

      return m_baseptra;

   }


} // namespace html




