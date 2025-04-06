// Created by camilo on 2025-04-05 20:33 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_APP_PROGRAMMING heating_up_exception :
   virtual public ::exception
{
public:


   heating_up_exception(const ::scoped_string& scopedstrMessage) :
      ::exception(error_time_bag, scopedstrMessage)
   {

   }



   ~heating_up_exception()
   {


   }

};



