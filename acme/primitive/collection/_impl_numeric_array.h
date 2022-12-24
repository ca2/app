//
// Created by camilo on 23/12/2022 16:24 <3ThomasBorregaardSorensen!!
//
#pragma once


template < typename TYPE, ::enum_type m_etypeContainer >
string numeric_array < TYPE, m_etypeContainer >::surround_and_implode(const ::scoped_string & scopedstrSeparator, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix, ::index iStart, ::count iCount)
{
   string str;
   string strSeparator(strSeparator);
   string strPrefix(strPrefix);
   string strSuffix(strSuffix);
   ::index iEnd;
   if(iStart < 0)
      iStart = this->get_size() + iStart;
   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;
   if(iStart <= iEnd)
   {
      ::index i = iStart;
      str = strPrefix + as_string(this->element_at(i)) + strSuffix;
      i++;
      for(; i <= iEnd; i++)
      {
         str += strSeparator + strPrefix + as_string(this->element_at(i)) + strSuffix;
      }
   }
   return str;
}



