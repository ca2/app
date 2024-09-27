// Created by camilo on 2022-10-11 00:08 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/prototype/element.h"
//#include "acme/prototype/prototype/payload.h"


namespace interprocess
{


   class CLASS_DECL_APEX task :
      virtual public ::particle
   {
   public:


      ::atom                                    m_atomPid;
      ::i64                                     m_iTask;
      ::pointer<::interprocess::call>           m_pcall;
      ::payload                                 m_payload;
      ::pointer<manual_reset_event>             m_pevReady;
      ::logic::boolean                          m_tristateContinue;
      ::logic::boolean                          m_tristateHandled;


      task(::interprocess::call * pcall, const ::atom & idPid, i64 iTask);
      ~task() override;


      virtual void do_task(const string & strObject, const string & strMember, const property_set & propertyset);


   };


} // namespace interprocess



