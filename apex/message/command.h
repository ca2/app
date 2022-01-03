// Created by camilo on 2021-02-08 <3TBS_!!
#pragma once



#include "acme/user/check.h"
#include "acme/user/text.h"


namespace message
{


   class command_update_target :
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      virtual bool enable_window(bool bEnable) = 0;


   };


   class CLASS_DECL_APEX command :
      virtual public ::message::message
   {
   public:


      __pointer(::channel)                        m_pcommandtargetSource;
      id                                           m_idControl;     // menu item or other index
      index                                        m_iIndex;
      ::count                                      m_iCount;        // last + 1 for iterating m_iIndex
      __pointer_array(::channel)                   m_commandtargetptraHandle;

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
      __pointer(command_update_target)             m_puiOther;         // nullptr if a menu or not a interaction_impl

      bool                                         m_bEnableChanged;
      bool                                         m_bHasCommandHandler;


      command(::object * pobject = nullptr);
      command(const ::id & id);


      void common_construct();

      bool is_command()const { return m_id.is_command(); }
      bool is_command_probe() const { return m_id.is_command_probe(); }

      ::e_status handle(::channel * pcommandtarget);
      bool is_handled(::channel * pcommandtarget);


      void reset(class ::channel * psignal);


      virtual void enable(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      virtual void _001SetCheck(bool bCheck = true, const ::action_context & action_context = ::e_source_system);   // true or false
      virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
      virtual void SetRadio(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      virtual void SetText(const char * pszText, const ::action_context & action_context = ::e_source_system);


      void do_probe(channel * ptarget);


      //virtual void send_to(channel * pchannel);
      //virtual void send_probe_to(channel * pchannel);



   };


} // namespace message



