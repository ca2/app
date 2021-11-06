#include "framework.h"


matter::~matter()
{

}








stream & matter::do_property_exchange(stream & stream) const
{

   ASSERT(stream.is_storing());

   property_set set;

   set += object_storing;

   ((matter *)this)->exchange(set);

   stream << set;

   return stream;

}



void matter::exchange(::stream & stream)
{

}


stream & matter::do_property_exchange(stream & stream)
{

   ASSERT(stream.is_loading());

   property_set set;

   stream >> set;

   set -= object_storing;

   exchange(set);

   return stream;

}

stream & matter::write(::stream & stream) const
{

   matter::write(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}


stream & matter::read(::stream & stream)
{

   matter::read(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}
