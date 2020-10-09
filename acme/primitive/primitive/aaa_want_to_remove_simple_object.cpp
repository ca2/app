#include "framework.h"


element::~element()
{

}








stream & element::do_property_exchange(stream & stream) const
{

   ASSERT(stream.is_storing());

   property_set set;

   set += object_storing;

   ((element *)this)->exchange(set);

   stream << set;

   return stream;

}



void element::exchange(::stream & stream)
{

}


stream & element::do_property_exchange(stream & stream)
{

   ASSERT(stream.is_loading());

   property_set set;

   stream >> set;

   set -= object_storing;

   exchange(set);

   return stream;

}

stream & element::write(::stream & stream) const
{

   element::write(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}


stream & element::read(::stream & stream)
{

   element::read(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}
