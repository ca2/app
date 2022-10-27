// Created by camilo on 2022-10-11 00:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/collection/atom_array.h"
#include "acme/primitive/collection/atom_map.h"
#include "acme/parallelization/synchronization_array.h"


namespace interprocess
{


   using task_map = atom_map < ::pointer< task > >;


   class CLASS_DECL_APEX call :
      virtual public ::property_set
   {
   public:


      ::pointer<::interprocess::communication>     m_pinterprocesscommunication;
      string                                       m_strApp;
      atom_array                                     m_iaExclude;
      bool                                         m_bAutoLaunch;

      // idPid - Task
      ::interprocess::task_map                     m_mapTask;


      string                                       m_strObject;
      string                                       m_strMember;


      call(communication * pcommunication, const string & strApp, const string & strObject, const string & strMember);
      ~call() override;

      void set_auto_launch(bool bSet = true);

      bool is_auto_launch() const;

      void exclude_pid(::i32 iPid);

      //virtual void post(const ::atom& idPid);
      virtual void send(const ::atom & idPid);

      ::pointer<synchronization_array>synca();

      ::e_status wait();
      bool _wait(const class ::wait & wait);


      virtual atom_array prepare_call();


      virtual void send_call();


   };


} // namespace interprocess



