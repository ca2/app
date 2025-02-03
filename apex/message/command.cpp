#include "framework.h"
#include "command.h"
#include "channel.h"
#include "acme/user/user/activation_token.h"
#include "acme/user/user/interaction.h"


namespace message
{


   command::command(::particle * pparticle)
   {

      common_construct();
      if (::is_set(pparticle))
      {

         initialize(pparticle);

      }

   }


   command::command(const ::atom & atom, ::user::activation_token * puseractivationtoken)
   {

      common_construct();

      set_command_id(atom);

      m_actioncontext.m_puseractivationtoken = puseractivationtoken;

      //id().set_compounded_type(::atom::e_type_command);
      m_bRadioChanged = false;

   }


   void command::common_construct()
   {

      m_pcommandtargetSource = nullptr;
      m_iIndex = -1;
      m_iCount = -1;
      m_bEnable = false;
      //m_echeck = ::e_check_undefined;
      m_bRadio = false;
      m_bRadioChanged = false;
      //m_pmenu = nullptr;
      //m_pmenuChild = nullptr;
      //m_pmenuParent = nullptr;
      m_puiOther = nullptr;
      m_bEnableChanged = false;
      m_bHasCommandHandler = false;

   }


   void command::destroy()
   {

      ::message::message::destroy();
      ::user::check::destroy();
      ::user::text::destroy();


   }


   void command::set_command_id(const ::atom & atom)
   {

      m_atomCommand2 = atom;

   }


   ::atom command::command_id() const
   {

      return m_atomCommand2;

   }


   void command::handle(::channel * pcommandtarget)
   {

      if (!m_commandtargetptraHandle.add_unique(pcommandtarget))
      {

         throw ::exception(error_already_added);

      }

      //return success;

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


   //command::command(::particle * pparticle) :
   //   ::object(pparticle)
   //{

   //   m_ecommand = command_default;

   //}

   //command::command(::particle * pparticle, enum_command ecommand) :
   //   ::object(pparticle)
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


   //void command::on_request(::request * prequest)
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

   //void command::set_check(bool bCheck, const ::action_context & context)
   //{

   //   set_check((::enum_check)(bCheck ? ::e_check_checked : ::e_check_unchecked), context);

   //}


   //void command::set_check(const ::e_check & echeck, const ::action_context & context)
   //{

   //   //if (m_pmenu != nullptr)
   //   //{

   //   //   ENSURE(m_iIndex < m_iCount);

   //   //}

   //   if (m_puiOther != nullptr)
   //   {

   //      ::pointer<::user::element>pelement = m_puiOther;

   //      if (pelement)
   //      {

   //         pelement->check().set_check(echeck, context + ::e_source_sync);

   //      }

   //   }

   //   m_echeck = echeck;

   //}

   
   void command::on_property_changed(::data::property_change & change)
   {

      if (m_checkproperty && change)
      {

         ::pointer<::acme::user::interaction> pelement = m_puiOther;

         if (pelement)
         {

            pelement->m_checkproperty.set(change.m_payload.as_echeck(), change.m_actioncontext + ::e_source_sync);

         }

      }
      else if (m_textproperty && change)
      {

         ::pointer<::acme::user::interaction> pelement = m_puiOther;

         if (pelement)
         {

            pelement->m_textproperty.set_text(change.m_payload.as_string(), change.m_actioncontext + ::e_source_sync);

         }

      }

   }


   void command::SetRadio(bool bOn, const ::action_context & context)
   {

      m_checkproperty.set(bOn, context);

   }


   void command::SetText(const ::scoped_string & scopedstrText, const ::action_context & actioncontext)
   {

      //if (m_pmenu != nullptr)
      //{

      //   ENSURE(m_iIndex < m_iCount);

      //}

      if (m_puiOther != nullptr)
      {

         ::pointer<::acme::user::interaction>pelement = m_puiOther;

         if (pelement)
         {

            pelement->m_textproperty.set_text(scopedstrText, actioncontext + ::e_source_sync);

         }


         //m_puiOther->set_text(scopedstrText, ::e_source_sync);

      }

      m_textproperty.set_text(scopedstrText, actioncontext);

   }


   void command::do_probe(channel * ptarget)
   {

      if (command_id().is_empty())
      {

         return;     // ignore invalid IDs

      }

      ENSURE_VALID(ptarget);

      m_bEnableChanged = false;

      m_bRadioChanged = false;

      //m_echeck = ::e_check_undefined;

      ptarget->_001SendCommandProbe(this);

   }


} // namespace


 
