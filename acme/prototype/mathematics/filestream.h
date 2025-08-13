#pragma once


template < class t1, class t2, class t3, class t4 >
void serialize_write(stream & ostream, map_base < t1, t2, t3, t4 > & m)
{
   ::collection::count count = m.get_count();
   typename map_base < t1, t2, t3, t4 >::pair * iterator = m.get_start();
   ostream << count;
   while (iterator != nullptr)
   {
      ostream << iterator->element1();
      ostream << iterator->element2();
      iterator = m.get_next(iterator);
   }
}

template < class t1, class t2, class t3, class t4 >
void serialize_read(stream & istream, map_base < t1, t2, t3, t4 > & m)
{
   try
   {
      t1 iCount;
      //      class map_base < t1, t2, t3, t4 >::pair * iterator =
      //       m.get_start();
      istream >> iCount;
      t1 key;
      t3 value;
      m.erase_all();
      for (int i = 0; i < iCount; i++)
      {
         istream >> key;
         istream >> value;
         m.set_at(key, value);
      }
   }
   catch (const ::scoped_string & scopedstr)
   {
      m.erase_all();
      throw ::exception(scopedstr);
   }
}


