// From filestream.h by camilo on 2022-10-08 01:04 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE, class T, class T_to_T = map < T, T, T, T > >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & ostream, const biunique< T, T_to_T > & b)
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


template < typename FILE, class T, class T_to_T = map < T, T, T, T > >
binary_stream < FILE > & operator >> (binary_stream < FILE > & istream, biunique< T, T_to_T > & b)
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
   catch (const ::scoped_string & scopedstr)
   {
      m_ab.erase_all();
      m_ba.erase_all();
      m_bBiunivoca = true;
      m_iEmptyA = -1;
      m_iEmptyB = -1;
      m_iMaxA = -1;
      m_iMaxB = -1;
      throw ::exception(psz);
   }
   return istream;
}



