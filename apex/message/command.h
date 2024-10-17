// Created by camilo on 2021-02-08 <3TBS_!!
#pragma once



#include "acme/user/user/check.h"
#include "acme/user/user/control.h"
#include "acme/user/user/text.h"
#include "acme/user/user/command_update_target.h"
#include "message.h"


namespace message
{


   class CLASS_DECL_APEX command :
      virtual public ::message::message,
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      ::pointer<::channel>                         m_pcommandtargetSource;
      ::atom                                         m_atomControl;     // menu item or other index
      ::collection::index                                        m_iIndex;
      ::collection::count                                      m_iCount;
      // last + 1 for iterating m_iIndex
      pointer_array < ::channel >                  m_commandtargetptraHandle;

      bool                                         m_bEnable;
      //enum_check                                   m_echeck; // m_bCheckChanged is similar to m_echeck != undefined
      //string                                       m_strText;
      //::user::check                                m_check;
      //::user::text                                 m_text;
      bool                                         m_bRadio;
      bool                                         m_bRadioChanged;

      // if a menu item
      ::user::menu *                               m_pmenu;         // nullptr if not a menu
      ::user::menu *                               m_pmenuChild;      // sub containing menu item
      ::user::menu *                               m_pmenuParent;   // nullptr if parent menu not easily determined
      // if a popup sub menu - ID is for first in popup

      // if from some other interaction_impl
      ::pointer<::user::command_update_target>    m_puiOther;         // nullptr if a menu or not a interaction_impl

      bool                                         m_bEnableChanged;
      bool                                         m_bHasCommandHandler;


      command(::particle * pparticle = nullptr);
      command(const ::atom & atom);


      void common_construct();

      void destroy() override;

      bool is_command()const { return m_atom.is_command(); }
      bool is_command_probe() const { return m_bProbing; }

      void handle(::channel * pcommandtarget);
      bool is_handled(::channel * pcommandtarget);


      //::user::check & check() { return m_check; }
      //::user::text & text() { return m_text; }


      void reset(class ::channel * psignal);


      virtual void enable(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      //virtual void set_check(bool bCheck = true, const ::action_context & action_context = ::e_source_system);   // true or false
      ///virtual void set_check(const ::e_check & echeck, const ::action_context & action_context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
      virtual void SetRadio(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      virtual void SetText(const ::scoped_string & scopedstrText, const ::action_context & action_context = ::e_source_system);


      void do_probe(channel * ptarget);


      //virtual void send_to(channel * pchannel);
      //virtual void send_probe_to(channel * pchannel);


      //void on_check_changed(::data::check & check, const ::payload & payload, const ::action_context & actioncontext) override;
      //void on_text_changed(::data::text & text, const ::payload & payload, const ::action_context & actioncontext) override;


      //virtual bool on_property_will_change(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      void on_property_changed(::data::property_change & change) override;


   };


} // namespace message



