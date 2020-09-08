#include "framework.h"
#include "_graphics.h"


namespace html
{


   base::base(class tag * ptagParent)
   {

      m_ptagParent = ptagParent;

   }


   base::~base()
   {

   }


   class tag * base::GetParent()
   {

      return m_ptagParent;

   }


   class tag * base::get_tag()
   {

      ASSERT(get_type() == type_tag);

      return dynamic_cast < class tag * > (this);

   }


   class value * base::get_value()
   {

      ASSERT(get_type() == type_value);

      return dynamic_cast < class value * > (this);

   }


} // namespace html




