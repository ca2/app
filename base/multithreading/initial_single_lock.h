#pragma once


class CLASS_DECL_AURA initial_single_lock :
   public single_lock
{
public:


   explicit initial_single_lock(sync * pobject) :
      single_lock(pobject,true)
   {

   }


};
