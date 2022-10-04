#include "framework.h"
// #if !BROAD_PRECOMPILED_HEADER
// #include "_graphics.h"
// #endif 
#include "base.h"
#include "tag.h"
#include "value.h"


namespace html
{


   base::base(class tag * ptagParent)
   {

      m_ptagParent = ptagParent;

   }


   base::~base()
   {

   }


   class tag * base::get_parent()
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




