#include "framework.h"


generic::~generic()
{

}








stream & generic::do_property_exchange(stream & stream) const
{

   ASSERT(stream.is_storing());

   property_set set;

   set += object_storing;

   ((generic *)this)->exchange(set);

   stream << set;

   return stream;

}



void generic::exchange(::stream & stream)
{

}


stream & generic::do_property_exchange(stream & stream)
{

   ASSERT(stream.is_loading());

   property_set set;

   stream >> set;

   set -= object_storing;

   exchange(set);

   return stream;

}

stream & generic::write(::stream & stream) const
{

   generic::write(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}


stream & generic::read(::stream & stream)
{

   generic::read(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}
