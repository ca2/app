// Created by camilo on 2021-02-08 <3TBS_!!
#pragma once



#include "acme/user/user/check.h"
#include "acme/user/user/text.h"
#include "acme/user/user/command_update_target.h"
#include "message.h"


namespace message
{


   class CLASS_DECL_APEX command :
      virtual public ::message::message
   {
   public:


      ::pointer<::channel>                         m_pcommandtargetSource;
      atom                                         m_atomControl;     // menu item or other index
      index                                        m_iIndex;
      ::count                                      m_iCount;        // last + 1 for iterating m_iIndex
      pointer_array < ::channel >                  m_commandtargetptraHandle;

      bool                                         m_bEnable;
      enum_check                                   m_echeck; // m_bCheckChanged is similar to m_echeck != undefined
      string                                       m_strText;
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

      bool is_command()const { return m_atom.is_command(); }
      bool is_command_probe() const { return m_atom.is_command_probe(); }

      void handle(::channel * pcommandtarget);
      bool is_handled(::channel * pcommandtarget);


      void reset(class ::channel * psignal);


      virtual void enable(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      //virtual void _001SetCheck(bool bCheck = true, const ::action_context & action_context = ::e_source_system);   // true or false
      virtual void _001SetCheck(const ::e_check & echeck, const ::action_context & action_context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
      virtual void SetRadio(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      virtual void SetText(const ::scoped_string & scopedstrText, const ::action_context & action_context = ::e_source_system);


      void do_probe(channel * ptarget);


      //virtual void send_to(channel * pchannel);
      //virtual void send_probe_to(channel * pchannel);



   };


} // namespace message



