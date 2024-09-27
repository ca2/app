// Created by camilo on 2022-10-11 00:06 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/collection/atom_map.h"
#include "acme/prototype/collection/atom_array.h"
////#include "acme/prototype/prototype/object.h"


namespace interprocess
{


   using task_map = atom_map < ::pointer< task > >;


   class CLASS_DECL_APEX communication :
      virtual public object
   {
   public:


      interlocked_count                                        m_iTaskSeed;
      string                                                   m_strApp;
      ::atom                                                   m_atomApp;
      string_map < ::pointer<::interprocess::caller > >        m_callermap;
      string_map < ::pointer< ::mutex > >                      m_mapAppMutex;
      ::pointer<::interprocess::target>                        m_ptarget;
      string_array                                             m_straModule;
      ::pointer<::interprocess::handler>                       m_phandler;

      // strTask - Task
      ::interprocess::task_map                                 m_mapTask;

   protected:

      using object::initialize;

   public:


      communication();
      ~communication() override;


      virtual void initialize_interprocess_communication(::particle * pparticle, const ::string & strApp);


      void destroy() override;


      virtual void defer_add_module(const ::string & strModule, const ::atom & atomPid);

      virtual ::pointer<::interprocess::task>create_task(::interprocess::call * pcall, const ::atom & atomPid);

      virtual ::pointer<::interprocess::task>get_task(i64 iTask);

      virtual ::pointer<::interprocess::call>create_call(const ::string & strApp, const ::string & strObject, const ::string & strMember);

      virtual ::pointer<::interprocess::call>create_call(const ::string & strObject, const ::string & strMember);

      virtual ::interprocess::caller & caller(const ::string & strApp, const ::atom & atomPid);

      virtual ::atom_array get_pid(const ::string & strApp);

      virtual string key(const string & strApp, const ::atom & atomPid);

      virtual string str_from_va(const payload_array & va);

      bool _handle_uri(const ::string & strUri) override;

      //using ::interprocess::handler::receiver::on_interprocess_receive;

      bool _handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;

      virtual void start(const ::string & strApp);

      virtual void connect(const ::string & strApp, const ::atom & atomPid);

      virtual void on_new_instance(const ::string & strModule, const ::atom & atomPid);

      void interprocess_communication_open(const ::file::path & path);

   };


} // namespace interprocess



