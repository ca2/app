// Created by camilo on 2023-02-02 02:41 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_container CONTAINER >
inline void from_string(CONTAINER& container, const ::scoped_string& scopedstr)
{
   
   container.clear();
   
   ::tokenizer tokenizer(scopedstr);
   
   ::string strToken;

   while (tokenizer.get_next_token(strToken, "|"))
   {
      
      typename CONTAINER::BASE_TYPE item;
      
      ::from_string(item, strToken);
   
      container.add(item);
 
   }

}



