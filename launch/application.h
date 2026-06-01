// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/platform/application.h"


namespace launch
{


   class CLASS_DECL_LAUNCH application :
      virtual public ::platform::application
   {
   public:

      ::string m_strLaunchAppId;

      ::pointer < launch > m_plaunch;

      bool m_bRunAsLaunch = true;

     
      application();
      ~application() override;


      virtual void do_launch();

      void run() override;


      virtual void on_launch_status(const ::scoped_string& scopedstr);
      virtual void on_going_to_launch();
      virtual void on_launched();


   };



} // namespace launch



