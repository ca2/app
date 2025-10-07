// Created by camilo on 2022-05-06 03:49 <3ThomasBorregaardSorensen!!
#pragma once


namespace acme
{

   

   class asset :
      virtual public ::particle

   {
   public:


      asset();
      ~asset() override;


      virtual void get_pointers(const_char_pointer &pstart, const_char_pointer &pend);


   };


} // namespace acme




