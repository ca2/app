// Created by camilo on 2021-03-24 15:03 BRT <3ThomasBS_!!
#pragma once


namespace parallelization
{


   class CLASS_DECL_ACME cleanup_task :
      virtual public ::task
   {
   protected:

      matter_array         m_mattera;
      void erase(matter* pmatter);

   public:

      void add(matter* pmatter);

      virtual ::e_status run();

   };


} // namespace parallelization



