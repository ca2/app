// Created by camilo on 2022-10-11 00:31 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/object.h"


namespace interprocess
{


   class CLASS_DECL_APEX channel :
      virtual public ::object
   {
   public:


      ::pointer<::interprocess::caller>         m_pcaller;
      ::pointer<::interprocess::target>         m_ptarget;
      string                                    m_strChannel;
      unsigned int                              m_timeTimeout;


      channel();
      ~channel() override;


      virtual bool open_ab(const ::string & strChannel, launcher * plauncher = nullptr);
      virtual bool open_ba(const ::string & strChannel, launcher * plauncher = nullptr);
      virtual bool close();


      virtual void restart_apex_ipc();


      virtual bool ensure_caller(const ::string & strUri, const class time & timeTimeout = 1_hour);
      //virtual bool ensure_caller(int message, void * pdata, int len, const class time & timeTimeout = hour());


      virtual bool is_channel_ok();


   };


} // namespace interprocess



