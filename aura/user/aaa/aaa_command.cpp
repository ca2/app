#include "framework.h"
//#include "base/user/user/_component.h"


namespace user
{


   command::command(::object * pobject)
   {

      common_construct();
      if (::is_set(pobject))
      {

         initialize(pobject);

      }

   }


   command::command(const ::atom & atom)
   {

      common_construct();
      m_emessage           = ::e_message_system_command;
      m_atom                          = atom;
      m_bRadioChanged               = false;

   }


   void command::common_construct()
   {

      m_pcommandtargetSource = nullptr;
      m_iIndex = -1;
      m_iCount = -1;
      m_bEnable = false;
      m_echeck = ::e_check_undefined;
      m_bRadio = false;
      m_bRadioChanged = false;
      m_pmenu = nullptr;
      m_pmenuChild = nullptr;
      m_pmenuParent = nullptr;
      m_puiOther = nullptr;
      m_bEnableChanged = false;
      m_bHasCommandHandler = false;

   }


   bool command::handle(::channel * pcommandtarget)
   {

      return m_commandtargetptraHandle.add_unique(pcommandtarget);

   }


   bool command::is_handled(::channel * pcommandtarget)
   {

      return m_commandtargetptraHandle.contains(pcommandtarget);

   }



   //command::command()
   //{

   //   m_ecommand = command_default;

   //}

   //command::command(const ::create & command)
   //{

   //   operator       = (command);

   //}


   //command::command(::object * pobject) :
   //   ::object(pobject)
   //{

   //   m_ecommand = command_default;

   //}

   //command::command(::object * pobject, enum_command ecommand) :
   //   ::object(pobject)
   //{

   //   m_ecommand = ecommand;

   //}

   //command::~command()
   //{

   //}


   //::payload command::run()
   //{

   //   return true;

   //}


   //void command::on_request(::create * pcreate)
   //{

   //   __UNREFERENCED_PARAMETER(pcreate);

   //}


   //string command::get_description()
   //{

   //   return "this is a command that was not described";

   //}

   //::create & command::operator = (const ::create & command)
   //{

   //   if (this == &command)
   //   {

   //      return *this;

   //   }

   //   ::object::operator = (command);

   //   m_ecommand = command.m_ecommand;
   //   m_strCommandLine = command.m_strCommandLine;
   //   m_payloadFile = command.m_payloadFile;

   //   return *this;

   //}

   void command::Enable(bool bOn, const ::action_context & context)
   {

      if(m_pmenu != nullptr)
      {

         ENSURE(m_iIndex < m_iCount);

      }

      if(m_puiOther != nullptr)
      {

         m_puiOther->enable_window(bOn);

      }

      m_bEnable = bOn;

      m_bEnableChanged = true;

   }

   void command::_001SetCheck(bool bCheck, const ::action_context & context)
   {

      _001SetCheck((::enum_check) (bCheck ? ::e_check_checked : ::e_check_unchecked),context);

   }


   void command::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if (m_pmenu != nullptr)
      {

         ENSURE(m_iIndex < m_iCount);

      }

      if(m_puiOther != nullptr)
      {

         __pointer(::user::check) pcheck = m_puiOther;

         if(pcheck)
         {

            pcheck->_001SetCheck(echeck, context + ::e_source_sync);

         }

      }

      m_echeck = echeck;

   }


   void ::message::command::SetRadio(bool bOn, const ::action_context & context)
   {

      _001SetCheck(bOn,context);

   }

   void ::message::command::SetText(const ::string & pszText, const ::action_context & context)

   {

      if (m_pmenu != nullptr)
      {

         ENSURE(m_iIndex < m_iCount);

      }

      if (m_puiOther != nullptr)
      {

         m_puiOther->set_window_text(pszText);


      }

      m_strText = pszText;


   }


   void command::do_probe(channel * ptarget)
   {

      if(m_atom.is_empty())
         return;     // ignore invalid IDs

      ENSURE_VALID(ptarget);

      m_bEnableChanged  = false;

      m_bRadioChanged   = false;

      m_echeck          = ::e_check_undefined;

      ptarget->_001SendCommandProbe(this);

   }




} // namespace user


