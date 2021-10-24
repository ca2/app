#include "framework.h"


namespace message
{


   command::command(::object * pobject)
   {

      common_construct();
      if (::is_set(pobject))
      {

         initialize(pobject);

      }

   }


   command::command(const ::id & id) :
      material_object(id)
   {

      common_construct();

      m_id.set_compounded_type(::id::e_type_command);
      m_bRadioChanged = false;

   }


   void command::common_construct()
   {

      m_pcommandtargetSource = nullptr;
      m_iIndex = -1;
      m_iCount = -1;
      m_bEnable = false;
      m_echeck = ::check_undefined;
      m_bRadio = false;
      m_bRadioChanged = false;
      //m_pmenu = nullptr;
      //m_pmenuChild = nullptr;
      //m_pmenuParent = nullptr;
      m_puiOther = nullptr;
      m_bEnableChanged = false;
      m_bHasCommandHandler = false;

   }


   ::e_status command::handle(::channel * pcommandtarget)
   {

      if (!m_commandtargetptraHandle.add_unique(pcommandtarget))
      {

         return error_already_added;

      }

      return success;

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
   //   m_varFile = command.m_varFile;

   //   return *this;

   //}

   void command::enable(bool bOn, const ::action_context & context)
   {

      //if (m_pmenu != nullptr)
      //{

      //   ENSURE(m_iIndex < m_iCount);

      //}

      if (m_puiOther != nullptr)
      {

         m_puiOther->enable_window(bOn);

      }

      m_bEnable = bOn;

      m_bEnableChanged = true;

   }

   void command::_001SetCheck(bool bCheck, const ::action_context & context)
   {

      _001SetCheck((::enum_check)(bCheck ? ::check_checked : ::check_unchecked), context);

   }


   void command::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      //if (m_pmenu != nullptr)
      //{

      //   ENSURE(m_iIndex < m_iCount);

      //}

      if (m_puiOther != nullptr)
      {

         __pointer(command_update_target) pcheck = m_puiOther;

         if (pcheck)
         {

            pcheck->_001SetCheck(echeck, context + ::e_source_sync);

         }

      }

      m_echeck = echeck;

   }


   void command::SetRadio(bool bOn, const ::action_context & context)
   {

      _001SetCheck(bOn, context);

   }


   void command::SetText(const char * pszText, const ::action_context & context)
   {

      //if (m_pmenu != nullptr)
      //{

      //   ENSURE(m_iIndex < m_iCount);

      //}

      if (m_puiOther != nullptr)
      {

         m_puiOther->_001SetText(pszText, ::e_source_sync);

      }

      m_strText = pszText;


   }


   void command::do_probe(channel * ptarget)
   {

      if (m_id.is_empty())
         return;     // ignore invalid IDs

      ENSURE_VALID(ptarget);

      m_bEnableChanged = false;

      m_bRadioChanged = false;

      m_echeck = ::check_undefined;

      ptarget->_001SendCommandProbe(this);

   }


} // namespace


 