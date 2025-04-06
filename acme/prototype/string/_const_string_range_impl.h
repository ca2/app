//
//  _const_string_range_impl.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-03-24.
//  Copyright © 2025 ca2 Software Development. All rights reserved.
//
#pragma once


template < typename ITERATOR_TYPE >
inline ::collection::count const_string_range < ITERATOR_TYPE > ::_count_parts_from_beginning(::collection::count  cPathPartCountToConsume, CHARACTER chSeparator)
{
   
   ::collection::index i = 0;
   
   for(; i < cPathPartCountToConsume; i++)
   {
      
      auto p = string_find_character(this->m_begin, chSeparator);
      
      if(::is_null(p))
      {
         
         break;
         
      }
      
      this->m_begin = p + 1;
      
   }
   
   return i;

}


template < typename ITERATOR_TYPE >
inline ::collection::count const_string_range < ITERATOR_TYPE > ::count_parts_from_beginning(::collection::count  cPathPartCountToConsume, CHARACTER chSeparator)
{
   
   if(cPathPartCountToConsume <= 0)
   {
      
      return cPathPartCountToConsume;
      
   }
 
   return this->_count_parts_from_beginning(cPathPartCountToConsume, chSeparator);
   
}
