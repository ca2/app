#pragma once


template < class t1, class t2, class t3, class t4 >
void serialize_write(stream & ostream, map < t1, t2, t3, t4 > & m)
{
   ::count count = m.get_count();
   typename map < t1, t2, t3, t4 >::pair * ppair = m.get_start();
   ostream << count;
   while (ppair != nullptr)
   {
      ostream << ppair->element1();
      ostream << ppair->element2();
      ppair = m.get_next(ppair);
   }
}

template < class t1, class t2, class t3, class t4 >
void serialize_read(stream & istream, map < t1, t2, t3, t4 > & m)
{
   try
   {
      t1 iCount;
      //      class map < t1, t2, t3, t4 >::pair * ppair =
      //       m.get_start();
      istream >> iCount;
      t1 key;
      t3 value;
      m.erase_all();
      for (i32 i = 0; i < iCount; i++)
      {
         istream >> key;
         istream >> value;
         m.set_at(key, value);
      }
   }
   catch (const char * psz)
   {
      m.erase_all();
      throw ::exception(psz);
   }
}


