#include "framework.h"


context_object::~context_object()
{

}








stream & context_object::do_property_exchange(stream & stream) const
{

   ASSERT(stream.is_storing());

   property_set set;

   set += object_storing;

   ((context_object *)this)->exchange(set);

   stream << set;

   return stream;

}



void context_object::exchange(::stream & stream)
{

}


stream & context_object::do_property_exchange(stream & stream)
{

   ASSERT(stream.is_loading());

   property_set set;

   stream >> set;

   set -= object_storing;

   exchange(set);

   return stream;

}

stream & context_object::write(::stream & stream) const
{

   object::write(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}


stream & context_object::read(::stream & stream)
{

   object::read(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}
