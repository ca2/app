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
      __throw(psz);
   }
}


template < class T, class T_to_T = map < T, T, T, T > >
stream & operator <<(stream & ostream, const biunique< T, T_to_T > & b)
{
   ostream << m_bBiunivoca;
   ostream << m_iMaxA;
   ostream << m_iMaxB;
   ostream << m_iEmptyA;
   ostream << m_iEmptyB;
   if (m_bBiunivoca)
   {
      ostream << m_ab;
   }
   else
   {
      ostream << m_ab;
      ostream << m_ba;
   }

   return ostream;

}

stream & operator >> (stream & istream, biunique< T, T_to_T > & b)
{
   try
   {
      istream >> m_bBiunivoca;
      istream >> m_iMaxA;
      istream >> m_iMaxB;
      istream >> m_iEmptyA;
      istream >> m_iEmptyB;
      if (m_bBiunivoca)
      {
         T_to_T ab;
         istream >> ab;
         typename T_to_T::pair * ppair = ab.get_start();
         while (ppair != nullptr)
         {
            set(ppair->element1(), ppair->element2());
            ppair = ab.get_next(ppair);
         }
      }
      else
      {
         istream >> m_ab;
         istream >> m_ba;
      }
   }
   catch (const char * psz)
   {
      m_ab.erase_all();
      m_ba.erase_all();
      m_bBiunivoca = true;
      m_iEmptyA = -1;
      m_iEmptyB = -1;
      m_iMaxA = -1;
      m_iMaxB = -1;
      __throw(psz);
   }
   return istream;
}



