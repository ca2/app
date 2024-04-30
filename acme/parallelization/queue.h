// Created on 2024-04-28 by camilo <3ThomasBorregaardSorensen!!
#pragma once


namespace parallelization
{


   class CLASS_DECL_ACME queue :
      virtual public ::particle
   {
   public:


      ::procedure_array                      m_procedurea;

      ::task_pointer                         m_ptask;

      ::pointer <::object >                  m_pobjectFork;


      queue();
      ~queue() override;


      virtual void async(const ::procedure& procedure);
      virtual void sync(const ::procedure& procedure, const class ::time& timeTimeout);


      virtual void defer_run();


   };


}// namespace parallelization