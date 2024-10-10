//
//  string_iterator.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 08/06/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


template < primitive_character CHARACTER >
class unicode_iterator
{
public:



   const CHARACTER *         m_p;

   const CHARACTER * m_psz;


   unicode_iterator(const CHARACTER * psz) : m_psz(psz) { }
   unicode_iterator(const CHARACTER * psz, strsize size) : m_psz(psz + size) { }

   ::wd32_character operator *();
   unicode_iterator & operator ++();
   unicode_iterator operator ++(int);

   template < primitive_integral INTEGRAL >
   unicode_iterator operator +(INTEGRAL i) const
   {

      auto iterator = *this;

      while (i > 0)
      {

         iterator++;

         i--;

      }

      return iterator;

   }

   bool operator == (const unicode_iterator & it) const { return m_psz == it.m_psz;}

   bool operator != (const unicode_iterator & it) const { return !operator==(it);}


   const CHARACTER * c_str() const { return m_psz; }


};
