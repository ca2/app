//
// Created by camilo on 2025-03-30 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace user
{


   class CLASS_DECL_ACME item :
      virtual public ::particle
   {
   public:


      bool m_bSelected : 1;


      item()
      {

         m_bSelected = false;

      }


   };


} /// namespace user



