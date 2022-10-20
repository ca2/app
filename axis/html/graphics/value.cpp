#include "framework.h"

#include "value.h"


namespace html
{


   value::value(class tag * ptagParent) :
      base(ptagParent)
   {
   }

   value::~value()
   {
   }

   base::type value::get_type()
   {
      return type_value;
   }

   void value::set_value(const ::string & pszValue)
   {
      m_strValue = pszValue;
   }

   string value::get_value()
   {
      return m_strValue;
   }


} // namespace html

