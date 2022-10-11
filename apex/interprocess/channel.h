// Created by camilo on 2022-10-11 00:31 <3ThomasBorregaardSorensen!!
#pragma once


namespace interprocess
{


   class CLASS_DECL_APEX channel :
      virtual public ::object
   {
   public:


      ::pointer<::interprocess::caller>         m_pcaller;
      ::pointer<::interprocess::target>         m_ptarget;
      string                                    m_strChannel;
      unsigned int                              m_durationTimeout;


      channel();
      ~channel() override;


      virtual bool open_ab(const ::string & strChannel, launcher * plauncher = nullptr);
      virtual bool open_ba(const ::string & strChannel, launcher * plauncher = nullptr);
      virtual bool close();


      virtual void restart_apex_ipc();


      virtual bool ensure_caller(const ::string & strUri, const ::duration & durationTimeout = hour());
      //virtual bool ensure_caller(int message, void * pdata, int len, const ::duration & durationTimeout = hour());


      virtual bool is_channel_ok();


   };


} // namespace interprocess



