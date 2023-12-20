//
// Created by camilo on 2023-12-19 04:12 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#pragma once


namespace operating_system
{


   class message_box :
      virtual public ::particle
   {
   public:


      //virtual void do_modal(const char * pszMsg, bool bError);

      virtual ::atom do_modal(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails);

   };

} // operating_system




