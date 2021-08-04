#pragma once


namespace user
{


   class CLASS_DECL_AURA command :
      virtual public ::user::message
   {
   public:


      __pointer(::channel)                         m_pcommandtargetSource;
      id                                           m_idControl;     // menu item or other index
      index                                        m_iIndex;
      ::count                                      m_iCount;        // last + 1 for iterating m_iIndex
      __pointer_array(::channel)                        m_commandtargetptraHandle;

      bool                                         m_bEnable;
      enum_check                                   m_echeck; // m_bCheckChanged is similar to m_echeck != undefined
      string                                       m_strText;
      bool                                         m_bRadio;
      bool                                         m_bRadioChanged;

      // if a menu item
      __pointer(::user::interaction)               m_pmenu;         // nullptr if not a menu
      __pointer(::user::interaction)               m_pmenuChild;      // sub containing menu item
      __pointer(::user::interaction)               m_pmenuParent;   // nullptr if parent menu not easily determined
      // if a popup sub menu - ID is for first in popup

      // if from some other interaction_impl
      __pointer(::user::primitive)                 m_puiOther;         // nullptr if a menu or not a interaction_impl

      bool                                         m_bEnableChanged;
      bool                                         m_bHasCommandHandler;


      command(::object * pobject = nullptr);
      command(const ::id & id);


      void common_construct();


      bool handle(::channel * pcommandtarget);
      bool is_handled(::channel * pcommandtarget);


      void reset(class ::channel * psignal);


      virtual void enable(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      virtual void _001SetCheck(bool bCheck = true, const ::action_context & action_context = ::e_source_system);   // true or false
      virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
      virtual void SetRadio(bool bOn = true, const ::action_context & action_context = ::e_source_system);
      virtual void SetText(const ::string & pszText, const ::action_context & action_context = ::e_source_system);


      void do_probe(channel * ptarget);


   };


} // namespace aura



