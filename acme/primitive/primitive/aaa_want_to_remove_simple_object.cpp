#include "framework.h"


elemental::~elemental()
{

}








stream & elemental::do_property_exchange(stream & stream) const
{

   ASSERT(stream.is_storing());

   property_set set;

   set += object_storing;

   ((elemental *)this)->exchange(set);

   stream << set;

   return stream;

}



void elemental::exchange(::stream & stream)
{

}


stream & elemental::do_property_exchange(stream & stream)
{

   ASSERT(stream.is_loading());

   property_set set;

   stream >> set;

   set -= object_storing;

   exchange(set);

   return stream;

}

stream & elemental::write(::stream & stream) const
{

   elemental::write(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}


stream & elemental::read(::stream & stream)
{

   elemental::read(stream);

   if (has_flag(object_default_property_exchange))
   {

      do_property_exchange(stream);

   }

   return stream;

}
