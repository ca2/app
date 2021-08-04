#include "framework.h"


//namespace user
//{
//
//
//   command::command(::object * pobject)
//   {
//
//         common_construct();
//         if (::is_set(pobject))
//         {
//
//            initialize(pobject);
//
//         }
//
//      }
//
//
//      command::command(const ::id & id) :
//         object(id)
//      {
//
//         common_construct();
//
//         m_id.set_compounded_type(::id::e_type_command);
//         m_bRadioChanged = false;
//
//      }
//
//
//      void command::common_construct()
//      {
//
//         m_pcommandtargetSource = nullptr;
//         m_iIndex = -1;
//         m_iCount = -1;
//         m_bEnable = false;
//         m_echeck = ::check_undefined;
//         m_bRadio = false;
//         m_bRadioChanged = false;
//         m_pmenu = nullptr;
//         m_pmenuChild = nullptr;
//         m_pmenuParent = nullptr;
//         m_puiOther = nullptr;
//         m_bEnableChanged = false;
//         m_bHasCommandHandler = false;
//
//      }
//
//
//      bool command::handle(::channel * pcommandtarget)
//      {
//
//         return m_commandtargetptraHandle.add_unique(pcommandtarget);
//
//      }
//
//
//      bool command::is_handled(::channel * pcommandtarget)
//      {
//
//         return m_commandtargetptraHandle.contains(pcommandtarget);
//
//      }
//
//
//
//      //command::command()
//      //{
//
//      //   m_ecommand = command_default;
//
//      //}
//
//      //command::command(const ::create & command)
//      //{
//
//      //   operator       = (command);
//
//      //}
//
//
//      //command::command(::object * pobject) :
//      //   ::object(pobject)
//      //{
//
//      //   m_ecommand = command_default;
//
//      //}
//
//      //command::command(::object * pobject, enum_command ecommand) :
//      //   ::object(pobject)
//      //{
//
//      //   m_ecommand = ecommand;
//
//      //}
//
//      //command::~command()
//      //{
//
//      //}
//
//
//      //::payload command::run()
//      //{
//
//      //   return true;
//
//      //}
//
//
//      //void command::on_request(::create * pcreate)
//      //{
//
//      //   UNREFERENCED_PARAMETER(pcreate);
//
//      //}
//
//
//      //string command::get_description()
//      //{
//
//      //   return "this is a command that was not described";
//
//      //}
//
//      //::create & command::operator = (const ::create & command)
//      //{
//
//      //   if (this == &command)
//      //   {
//
//      //      return *this;
//
//      //   }
//
//      //   ::object::operator = (command);
//
//      //   m_ecommand = command.m_ecommand;
//      //   m_strCommandLine = command.m_strCommandLine;
//      //   m_varFile = command.m_varFile;
//
//      //   return *this;
//
//      //}
//
//      void command::enable(bool bOn, const ::action_context & context)
//      {
//
//         if (m_pmenu != nullptr)
//         {
//
//            ENSURE(m_iIndex < m_iCount);
//
//         }
//
//         if (m_puiOther != nullptr)
//         {
//
//            m_puiOther->enable_window(bOn);
//
//         }
//
//         m_bEnable = bOn;
//
//         m_bEnableChanged = true;
//
//      }
//
//      void command::_001SetCheck(bool bCheck, const ::action_context & context)
//      {
//
//         _001SetCheck((::enum_check)(bCheck ? ::check_checked : ::check_unchecked), context);
//
//      }
//
//
//      void command::_001SetCheck(::enum_check echeck, const ::action_context & context)
//      {
//
//         if (m_pmenu != nullptr)
//         {
//
//            ENSURE(m_iIndex < m_iCount);
//
//         }
//
//         if (m_puiOther != nullptr)
//         {
//
//            __pointer(command_update_target) pcheck = m_puiOther;
//
//            if (pcheck)
//            {
//
//               pcheck->_001SetCheck(echeck, context + ::e_source_sync);
//
//            }
//
//         }
//
//         m_echeck = echeck;
//
//      }
//
//
//      void ::message::command::SetRadio(bool bOn, const ::action_context & context)
//      {
//
//         _001SetCheck(bOn, context);
//
//      }
//
//      void ::message::command::SetText(const ::string & pszText, const ::action_context & context)
//      {
//
//         if (m_pmenu != nullptr)
//         {
//
//            ENSURE(m_iIndex < m_iCount);
//
//         }
//
//         if (m_puiOther != nullptr)
//         {
//
//            m_puiOther->_001SetText(pszText, ::e_source_sync);
//
//         }
//
//         m_strText = pszText;
//
//
//      }
//
//
//      void command::do_probe(channel * ptarget)
//      {
//
//         if (m_id.is_empty())
//            return;     // ignore invalid IDs
//
//         ENSURE_VALID(ptarget);
//
//         m_bEnableChanged = false;
//
//         m_bRadioChanged = false;
//
//         m_echeck = ::check_undefined;
//
//         ptarget->_001SendCommandProbe(this);
//
//      }
//
//
//
//
//   void channel::_001SendCommand(::message::command * pcommand)
//   {
//
//      pcommand->m_pchannel = this;
//
//      {
//
//         __restore(pcommand->m_id.m_etype);
//
//         pcommand->m_id.set_compounded_type(::id::e_type_command);
//
//         route_command_message(pcommand);
//
//      }
//
//   }
//
//
//   void channel::_001SendCommandProbe(::message::command * pcommand)
//   {
//
//      pcommand->m_pcommandtargetSource = this;
//
//      {
//
//         __restore(pcommand->m_id.m_etype);
//
//         pcommand->m_id.set_compounded_type(::id::e_type_command_probe);
//
//         route_command_message(pcommand);
//
//      }
//
//   }
//
//
//   void channel::route_command_message(::message::command * pcommand)
//   {
//
//      on_command_message(pcommand);
//
//   }
//
//
//   void channel::on_command_message(::message::command * pcommand)
//   {
//
//      if (pcommand->is_command())
//      {
//
//         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);
//
//         on_command_probe(pcommand);
//
//         if (!pcommand->m_bEnableChanged
//            && !pcommand->m_bRadioChanged
//            && pcommand->m_echeck == check_undefined
//            && !pcommand->m_bHasCommandHandler)
//         {
//
//            return;
//
//         }
//
//         on_command(pcommand);
//
//      }
//      else if (pcommand->m_id.is_compounded(::id::e_type_command_probe))
//      {
//
//         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);
//
//         on_command_probe(pcommand);
//
//      }
//      else if (pcommand->m_id.is_compounded(::id::e_type_command))
//      {
//
//         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);
//
//      }
//      else
//      {
//
//         __throw(error_not_implemented);
//
//      }
//
//   }
//
//
//   void channel::on_command(::message::command * pcommand)
//   {
//
//      {
//
//         __restore(pcommand->m_id.m_etype);
//
//         pcommand->m_id.set_compounded_type(::id::e_type_command);
//
//         route_message(pcommand);
//
//      }
//
//   }
//
//
//   bool channel::has_command_handler(::message::command * pcommand)
//   {
//
//      synchronous_lock synchronouslock(channel_mutex());
//
//      __restore(pcommand->m_id.m_etype);
//
//      pcommand->m_id.set_compounded_type(::id::e_type_command);
//
//      if (m_idaHandledCommands.contains(pcommand->m_id))
//      {
//
//         return true;
//
//      }
//
//      auto passoc = m_idroute.plookup(pcommand->m_id);
//
//      if (::is_null(passoc))
//      {
//
//         return false;
//
//      }
//
//      if (passoc->m_element2.is_null())
//      {
//
//         return false;
//
//      }
//
//      if (passoc->element2()->is_empty())
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }
//
//
//   void channel::on_command_probe(::message::command * pcommand)
//   {
//
//      {
//
//         __restore(pcommand->m_id.m_etype);
//
//         pcommand->m_id.set_compounded_type(::id::e_type_command_probe);
//
//         route_message(pcommand);
//
//         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);
//
//         pcommand->m_bRet =
//            pcommand->m_bEnableChanged
//            || pcommand->m_bRadioChanged
//            || pcommand->m_echeck != check_undefined;
//
//      }
//
//   }
//
//
//
//} // namespace user
//
//
//
