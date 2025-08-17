#include "framework.h"
#include "control.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"
#include "acme/include/_c_swap.h"
#include "acme/platform/keep.h"
#include "acme/handler/request.h"
#include "acme/platform/timer.h"
#include "acme/prototype/collection/_array_binary_stream.h"
#include "apex/database/_binary_stream.h"
#include "apex/database/selection.h"
#include "aura/user/user/form_callback.h"
#include "aura/message/user.h"
#include "aura/user/user/system.h"
#include "axis/platform/application.h"
#include "axis/platform/session.h"
#include "axis/platform/system.h"
#include "axis/user/user/user.h"
#include "axis/user/user/validate.h"


namespace user
{


   form_control::form_control()
   {

      m_bDefaultDataUpdateHandling = true;

      m_bOnEditUpdate         = false;
      m_bOnLanguageChange     = false;
      m_bInitialized          = false;

   }


   form_control::~form_control()
   {

   }



   //::form_property_set * form_control::get_form_property_set()
   //{
   //
   //   if(::is_set(m_pcallback))
   //   {
   //
   //      auto pset = m_pcallback->get_form_property_set();
   //
   //      if(pset)
   //      {
   //
   //         return pset;
   //
   //      }
   //
   //   }
   //
   //   return ::user::interaction::get_form_property_set();
   //
   //}


   //::pointer<class control_descriptor> form_control::new_form_control()
   //{

   //   auto pdescriptor = __allocate ::user::control_descriptor();

   //   m_controldescriptorset.add(pdescriptor);

   //   pdescriptor->m_iControl = m_controldescriptorset.find_first(pdescriptor);

   //   pdescriptor->m_puserinteractionParent = this;

   //   if(pdescriptor->m_bTransparent)
   //   {

   //      switch(pdescriptor->m_econtroltype)
   //      {
   //      case e_control_type_static:
   //      {
   //         /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pinteraction->id())->GetSafeoswindow_());
   //         if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
   //         {
   //         pstatic = ___new CTransparentStatic();
   //         VERIFY(pstatic->subclass_window(pform->get_child_by_id(pinteraction->id())->GetSafeoswindow_()));
   //         }
   //         pinteraction->m_unionwndptr.m_pstatic = pstatic;*/
   //      }
   //      break;
   //      default:
   //         break;

   //      }

   //   }

   //   return pdescriptor;

   //}


   bool form_control::OnCommand(wparam wparam,lparam lparam)
   {

      unsigned int uNotificationCode = upper_unsigned_short(wparam);

      ::atom atom(lower_unsigned_short(wparam));

      ::pointer<::user::interaction>pinteraction = get_child_by_id(atom);

      if (!pinteraction)
      {

         return false;

      }

      switch(pinteraction->get_control_type())
      {
      case e_control_type_button:
         OnCommandButton(pinteraction,uNotificationCode,lparam);

         break;
      case e_control_type_check_box:
         OnCommandCheckBox(pinteraction,uNotificationCode,lparam);

         break;
      case e_control_type_combo_box:
         OnCommandComboBox(pinteraction,uNotificationCode,lparam);

         break;
      case e_control_type_edit:
         OnCommandEdit(pinteraction,uNotificationCode,lparam);

         break;
      default:
         break;
      }

      return false;

   }


   bool form_control::OnCommandButton(::user::interaction * pinteraction,unsigned int uNotificationCode,lparam lparam)

   {

      __UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_button);

#ifdef WINDOWS

      //switch(uNotificationCode)
      //{
      //case BN_CLICKED:
      //{
      //   if(pinteraction->has_function(e_control_function_action))
      //   {
      //      _001OnButtonAction(pinteraction);
      //      return true;
      //   }
      //}
      //break;
      //default:
      //   break;
      //}

#endif

      return false;
   }


   bool form_control::OnCommandCheckBox(::user::interaction * pinteraction,unsigned int uNotificationCode,lparam lparam)

   {

      __UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_check_box);

#ifdef WINDOWS

      //switch(uNotificationCode)
      //{
      //case BN_CLICKED:
      //{
      //   /*      linux   ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->id());
      //   int i = pbutton->get_check() != 0;
      //   VmsDataSet(pinteraction->m_dataid, 0, 0, i);*/
      //}
      //break;
      //default:
      //   break;
      //}

#endif

      return false;

   }


   bool form_control::OnCommandComboBox(::user::interaction * pinteraction,unsigned int uNotificationCode,lparam lparam)

   {

      __UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_combo_box);

#ifdef WINDOWS

      //switch(uNotificationCode)
      //{
      //case CBN_SELCHANGE:
      //{
      //   /* linux         ::pointer<::user::combo_box>pcombo = (::pointer<::user::combo_box>get_child_by_id(pinteraction->id());
      //   int iSel = pcombo->current_item();
      //   if(iSel != CB_ERR)
      //   {
      //   unsigned int dwData = pinteraction->GetComboBox()->m_dwaData[iSel];
      //   VmsDataSet(pinteraction->m_dataid, 0, 0, (int) dwData);
      //   }*/
      //}
      //break;
      //case EN_KILLFOCUS:
      //{
      //   //_001SaveEdit(control);
      //}
      //default:
      //   break;
      //}

#endif

      return false;

   }


   bool form_control::OnCommandEdit(::user::interaction * pinteraction,unsigned int uNotificationCode,lparam lparam)

   {

      __UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_edit);

#ifdef WINDOWS

      //switch(uNotificationCode)
      //{
      //case EN_CHANGE:
      //{
      //   if(pinteraction->has_function(e_control_function_save_on_change))
      //   {
      //      _001SaveEdit(pinteraction);
      //   }
      //}
      //break;
      //case EN_KILLFOCUS:
      //{
      //   _001SaveEdit(pinteraction);
      //}
      //default:
      //   break;
      //}

#endif

      return false;

   }


   bool form_control::_001SaveEdit(::user::interaction * pinteraction)
   {

      if (::is_null(pinteraction))
      {

         return false;

      }

      ASSERT(pinteraction->get_control_type() == e_control_type_edit || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      string str;

      str = pinteraction->as_text();

      ::user::validate validate;

      try
      {

         validate.Validate(str, pinteraction);

         //if (!validate.Validate(str, pinteraction))
         //{
         //   // que tal um balao para indicar o erro
         //   return false;
         //}

      }
      catch (const ::exception& exception)
      {

         if (exception.m_estatus.failed())
         {

            return false;

         }

      }

      ::payload payload;

      if(!pinteraction->get_data(pinteraction, payload))
      {

         return false;

      }

      if(!_001Validate(pinteraction, payload))
      {
         return false;
      }

      if(pinteraction->has_function(e_control_function_vms_data_edit))
      {

//         ::database::selection selection;
//
//         get_selection(pinteraction->m_strDataKey, selection);

         throw_todo();

         //_data_set(selection, payload);

      }

      return true;

   }


   void form_control::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      //for(auto pinteraction : proper_children())
      //{

      //   _001Update(pinteraction);

      //}

      if (ptopic->id() == ::id_create)
      {

         if (is_child(ptopic->user_interaction()))
         {

            ptopic->user_interaction()->m_pform = this;

         }

      }
      else if (ptopic->id() == ::id_set_focus)
      {

         if (!_001OnControlSetFocus(ptopic->user_interaction()))
         {

            ptopic->Nok();

            return;

         }

      }
      else if (ptopic->id() == ::id_kill_focus)
      {

         if (!_001OnControlKillFocus(ptopic->user_interaction()))
         {

            ptopic->Nok();

            return;

         }

      }

      //if(m_pcallback != nullptr)
      //{

      //   m_pcallback->handle(ptopic, phandlercontext);

      //   if(ptopic->m_bRet)
      //   {

      //      return;

      //   }

      //}

      ::user::interaction::handle(ptopic, phandlercontext);

      if (ptopic->m_bRet)
      {

         return;

      }

      if (ptopic->id() == ::id_tab_key)
      {

         ::pointer<::user::interaction_base>pfocus = ptopic->user_interaction()->keyboard_get_next_focusable();

         if (pfocus != nullptr)
         {

            pfocus->set_keyboard_focus();

         }

      }
      else if (ptopic->id() == ::id_click)
      {

         ::pointer<interaction>pinteraction = ptopic->user_interaction();

         if (::is_null(pinteraction))
         {

            return;

         }

         if (pinteraction->has_function(e_control_function_action))
         {

            if (pinteraction != nullptr)
            {

               _001OnButtonAction(pinteraction);

               ptopic->m_bRet = true;

               return;

            }
            else
            {

               return;

            }

         }

      }
      else if (ptopic->id() == ::id_set_check && ptopic->m_actioncontext.is_user_source())
      {

         ::pointer<interaction>pinteraction = ptopic->user_interaction();

         if (!pinteraction)
         {

            return;

         }

         if (pinteraction->m_eddx == e_control_ddx_dbflags)
         {

            throw_todo();

//            ::int_array_base ia;
//
//            ::pointer<::database::client>pclient = pinteraction;
//
//            if (pclient.is_null())
//            {
//
//               informationf("control doesn't implement database::client");
//
//               return;
//
//            }
//
//            pclient->datastream()->get(pinteraction->m_strDataKey, ia);
//
//            ::pointer<check>pcheck = ptopic->user_interaction();
//
//            if (pcheck->echeck() == ::e_check_checked)
//            {
//
//               ia.add_unique(pinteraction->m_iDataValue);
//
//            }
//            else
//            {
//
//               ia.erase(pinteraction->m_iDataValue);
//
//            }
//
//            pclient->datastream()->set(pinteraction->m_strDataKey, ia);

         }

      }

      if (::is_set(m_pcallback))
      {

         m_pcallback->handle(ptopic, phandlercontext);

         if (ptopic->m_bRet)
         {

            return;

         }

      }

   }


   void form_control::_001Update(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      switch(pinteraction->get_control_type())
      {
      case e_control_type_check_box:
         _001UpdateCheckBox(pinteraction);
         break;
      case e_control_type_combo_box:
         _001UpdateComboBox(pinteraction);
         break;
      case e_control_type_edit:
      case e_control_type_edit_plain_text:
         _001UpdateEdit(pinteraction);
         break;
      case e_control_type_simple_list:
         _001UpdateSimpleList(pinteraction);
         break;
      default:
         break;
      }
   }

   void form_control::_001UpdateDbFlags(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      switch(pinteraction->get_control_type())
      {
      case e_control_type_check_box:
         //_001UpdateDbFlagsCheckBox(pinteraction);
         break;
      /*   case e_control_type_combo_box:
      _001UpdateComboBox(control);
      break;
      case e_control_type_edit:
      case e_control_type_edit_plain_text:
      _001UpdateEdit(control);
      break;
      case e_control_type_simple_list:
      _001UpdateSimpleList(control);
      break;*/
      default:
         break;
      }
   }

   void form_control::_001UpdateDbFlagsCheckBox(::user::interaction * pinteraction)
   {

      ASSERT(pinteraction != nullptr);

      if (pinteraction == nullptr)
      {

         return;

      }

      ASSERT(pinteraction->get_control_type() == e_control_type_check_box);

      ASSERT(pinteraction->m_eddx == e_control_ddx_dbflags);

      ::int_array_base ia;

      try
      {

         throw_todo();

         //pinteraction->datastream()->get(pinteraction->m_strDataKey,ia);

      }
      catch(...)
      {

      }

   }


   void form_control::_001UpdateCheckBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      ASSERT(pinteraction->get_control_type() == e_control_type_check_box);

      ::payload payload;

      //if(datastream()->get(pinteraction->m_strDataKey, payload))
      //{
         /* linux      ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->id());
         pbutton->SetCheck((i != 0) ? 1 : 0); */
      //}

   }


   void form_control::_001UpdateComboBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      /* linux   ASSERT(pinteraction->get_type() == e_control_type_combo_box);
      int i;
      if(VmsDataGet(pinteraction->m_dataid, 0, 0, i))
      {
      iptr iSel = pinteraction->GetComboBox()->m_dwaData.find_first((unsigned int) i);
      if(iSel >= 0)
      {
      ::pointer<::user::combo_box>pcombo = (::pointer<::user::combo_box>get_child_by_id(pinteraction->id());
      pcombo->set_current_item(iSel);
      }
      }*/
   }

   void form_control::_001UpdateEdit(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;

      if(m_bOnEditUpdate)
         return;

      KEEP(m_bOnEditUpdate);

      ASSERT(pinteraction->get_control_type() == e_control_type_edit
             || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      if(pinteraction->has_function(e_control_function_vms_data_edit))
      {
         throw_todo();
//         ::payload payload;
//         ::database::selection selection;
//         get_selection(pinteraction->m_strDataKey,selection);
//         if(selection.get_item_count() > 0)
//         {
//
//            //::database::selection_item & item = selection.get_item(0);
//
//            if (!pinteraction)
//            {
//
//               return;
//
//            }
//
//            //if(datastream()->get(pinteraction->m_strDataKey.m_strDataKey + "." + item.m_strDataKey.m_strDataKey,::payload))
//            //{
//            //   switch(payload.get_type())
//            //   {
//            //   case ::e_type_string:
//            //   {
//
//            //      string str;
//
//            //      str = payload.m_str;
//
//            //      pinteraction->set_text(str,::e_source_database);
//
//            //   }
//            //   break;
//            //   case ::e_type_int:
//            //   {
//
//            //      string str;
//
//            //      str.formatf("%d",payload.as_int());
//
//            //      pinteraction->set_text(str,::e_source_database);
//
//            //   }
//            //   break;
//            //   default:
//            //      ASSERT(false);
//            //      break;
//            //   }
//            //}
         //}
      }
   }

   void form_control::_001UpdateSimpleList(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;

      ASSERT(pinteraction->get_control_type() == e_control_type_simple_list);

      /*      ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pinteraction->id()));

      if(typeid(plist->GetDataInterface()) == ::type < ::user::simple_mesh_data >())
      {
      ::user::simple_mesh_data * pdata = dynamic_cast < ::user::simple_mesh_data * > (plist->GetDataInterface());
      string_array_base stra;
      datastream()->get(pinteraction->m_dataid, stra);
      ASSERT(plist != nullptr);
      pdata->set_data(plist, stra);
      }*/
   }

   void form_control::_000OnPosCreate(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //      ::pointer<::user::message>pusermessage(pmessage);
   }

   void form_control::_001InitializeFormPreData()
   {
      if(m_pcallback != nullptr)
      {
         m_pcallback->_001InitializeFormPreData(this);
      }

      /*
      if(get_owner() != nullptr)
      {
      get_owner()->SendMessage(
      WM_USER + 723,
      GetDlgCtrlId(),
      (LPARAM) this);
      }
      */

   }


   bool form_control::_001GetData(atom uId,bool &bData)
   {

      ::pointer<::user::interaction>pinteraction = get_child_by_id(uId);

      if(pinteraction == nullptr)
      {

         return false;

      }

      ::payload payload;

      //if(!datastream()->get(pinteraction->m_strDataKey, payload))
      //{

      //   return false;

      //}

      bData = (payload.as_int() != 0) ? 1 : 0;

      return true;

   }


   bool form_control::_001SetData(atom uId,bool bData)
   {

      ::pointer<::user::interaction>pinteraction = get_child_by_id(uId);

      if(pinteraction == nullptr)
      {

         return false;

      }

      //int i = bData ? 1 : 0;

      //datastream()->set(pinteraction->m_strDataKey,i);

      return true;

   }


   void form_control::Update(bool bSave)
   {
      if(bSave)
      {

      }
      else
      {

         for(auto pinteraction : proper_children())
         {

            _001Update(pinteraction);

         }

      }

   }


   void form_control::install_message_routing(::channel *pchannel)
   {

      form::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel,this,&form_control::on_message_create);
      MESSAGE_LINK(e_message_after_create, pchannel,this,&form_control::_000OnPosCreate);
      MESSAGE_LINK(e_message_language, pchannel,this,&form_control::_001OnAppLanguage);
      //MESSAGE_LINK(e_message_key_down                     , pchannel,this,&form_control::on_message_key_down);
      //MESSAGE_LINK(e_message_key_up                       , pchannel,this,&form_control::on_message_key_up);
      MESSAGE_LINK(WM_USER + 123, pchannel,this,&form_control::_001OnUser123);

      //install_update_data_message_routing(pchannel);

   }


   void form_control::get_selection(const ::scoped_string & scopedstrDataKey,::string_array_base &selection)
   {

      selection.add_item(scopedstrDataKey);

   }


   void form_control::on_command(::message::command * pcommand)
   {

      ::user::form::on_command(pcommand);

   }


   void form_control::_001OnNotify(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      ::pointer<::message::notify>pnotify(pmessage);

      pnotify->m_bRet = false;

#else

      throw ::exception(todo);

#endif

   }


   void form_control::_001OnMessageNotify(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      // revamp pusermessage->set_lresult(user::NotifyRetContinue);

      pusermessage->m_bRet = false;

   }


   bool form_control::_001Validate(::user::interaction * pinteraction,::payload & payload)
   {

      __UNREFERENCED_PARAMETER(pinteraction);
      __UNREFERENCED_PARAMETER(payload);

      return true;

   }


   //void form_control::_001RemoveControls()
   //{

   //   m_controldescriptorset.erase_all();

   //}


   bool form_control::_001OnBeforeSave(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return true;

   }


   void form_control::update_data(bool bSaveAndValidate)
   {

      ::user::interaction::update_data(bSaveAndValidate);

      ::topic_pointer ptopic;

      if (bSaveAndValidate)
      {

         ptopic = create_topic(::id_save_form_data);

         m_bNeedSaveFormData = false;

      }
      else
      {

         ptopic = create_topic(::id_load_form_data);

         m_bNeedLoadFormData = false;

      }

      ptopic->m_bOk = true;

      ptopic->m_puserelement = this;

      route(ptopic);

   }


   void form_control::data_on_after_change(::database::client* pclient, const ::scoped_string & strDataKey, const ::payload & payload, ::topic * ptopic)
   {

      for(auto pinteraction : proper_children())
      {

         if(pinteraction->m_eddx == e_control_ddx_dbflags)
         {

            _001UpdateDbFlags(pinteraction);

         }
         else
         {

            throw_todo();

//         else if(pinteraction->m_strDataKey == key)
//         {
//
//            _001Update(pinteraction);
//
//         }

         }

      }

   }


   void form_control::_001UpdateFunctionStatic()
   {

      auto papp = get_app();

      for(auto pinteraction : proper_children())
      {

         if(pinteraction->has_function(e_control_function_static))
         {

            string str;

            str = papp->load_string(pinteraction->id());

            pinteraction->set_window_text(str);

         }
         else if(pinteraction->has_function(e_control_function_static2))
         {

            string str;

            str = papp->load_string(pinteraction->m_uiText);

            pinteraction->set_window_text(str);

         }

      }

   }




   void form_control::WfiOnClose()
   {

      post_message(e_message_close);

   }


   void form_control::_001OnInitializeForm(::user::interaction * pinteraction)
   {

      auto pextendedtopic = create_extended_topic(::id_initialize_control);

      pextendedtopic->m_puserelement        = pinteraction;
      pextendedtopic->m_actioncontext       = ::e_source_database;
      pextendedtopic->m_uiEvent             = 0;

      route(pextendedtopic);

   }


   void form_control::_001OnButtonAction(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

   }


   void form_control::_001OnAppLanguage(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      KEEP(m_bOnLanguageChange);

      _017OnAppLanguage();

      pusermessage->m_bRet = false;

   }


   void form_control::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pmessagecreate(pmessage);

      auto prequest = m_pusersystem->m_prequest;

      if(::is_set(prequest))
      {

         set_form_callback(prequest->m_payloadArguments["form_callback"].cast < ::user::form_callback >());

      }

      if (pmessagecreate->previous())
      {

         return;

      }

   }


   bool form_control::_001AddControl(::user::interaction * pinteraction)
   {

      return ::user::form::_001AddControl(pinteraction);

   }


   void form_control::_001FillCombo(::user::interaction * pinteraction)
   {

      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      /* linux  if(pinteraction->GetComboBox() != nullptr)
      {
      if(!pinteraction->GetComboBox()->m_strDataKeyFill.IsNull())
      {
      pinteraction->GetComboBox()->m_wstra.erase_all();
      pinteraction->GetComboBox()->m_dwaData.erase_all();
      ::payload payload;
      payload.m_etype = ::e_type_element;
      payload.m_pca2 = pinteraction->GetComboBox();
      VmsDataGet(
      pinteraction->GetComboBox()->m_strDataKeyFill,
      0, 0,
      ::payload);
      ::pointer<::user::combo_box>pcombo = (::pointer<::user::combo_box>pinteraction->m_puserinteraction;
      pcombo->reset_content();
      string str;
      for(int i = 0; i < pinteraction->GetComboBox()->m_wstra.get_size(); i++)
      {
      str = pinteraction->GetComboBox()->m_wstra[i];
      pcombo->AddString(str);
      }

      }
      } */
   }


   void form_control::_017OnAppLanguage()
   {

      //for(int i = 0; i < m_controldescriptorset.get_size() ; i++)
      //{
      //   class control_descriptor & descriptor = m_controldescriptorset(i);
      //   if(descriptor.m_type)
      //   {
      //      if(descriptor.m_bCreated && descriptor.m_pcontrol != nullptr)
      //      {
      //      }
      //      else if(descriptor.m_bSubclassed && descriptor.m_pcontrol != nullptr)
      //      {
      //         //            if(::IsWindow(pinteraction->m_puserinteraction->GetSafeoswindow_()))
      //         {
      //            //xxx pinteraction->m_puserinteraction->unsubclass_window();
      //         }
      //         //            ASSERT(pinteraction->m_type->IsDerivedFrom(::type < window >()));
      //         if(descriptor.m_pcontrol.is_set())
      //         {
      //            //window_id wndidTemp = get_child_by_id(pinteraction->id())->GetSafeoswindow_();
      //            //if(wndidTemp != nullptr)
      //            {
      //               //xxx        VERIFY(pinteraction->m_puserinteraction->subclass_window(wndidTemp));
      //            }
      //         }
      //      }
      //      if(descriptor.m_pcontrol != nullptr)
      //      {
      //         //               ::type ti = typeid(descriptor.m_pcontrol);
      //         /*               if(ti == ::type < ::user::list >())
      //         {
      //         if(descriptor.m_etype == e_control_type_simple_list)
      //         {
      //         ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
      //         plist->m_dataid = descriptor.m_atomPrivateDataSection;
      //         plist->_001SetSingleColumnMode(false);
      //         }
      //         }*/
      //         /*            else if(pinteraction->m_type->IsDerivedFrom(::type < simple_still >()))
      //         {
      //         simple_still * pstatic = (simple_still *) pinteraction->m_puserinteraction;
      //         pstatic->m_bTransparent = pinteraction->m_bTransparent;
      //         }*/
      //         _001OnInitializeForm(descriptor.m_pcontrol);
      //      }
      //   }
      //}

   }


   //bool form_control::create_interaction(::user::interaction * pinteractionParent, const ::atom & atom)
   //{

   //   //if(!normalize_control_descriptor_typeinfo(pdescriptor))
   //   //{
   //   //   informationf("form_control::create_interaction: failed to create control, could not find proper type for allocation");
   //   //   return false;
   //   //}

   ///*   ::pointer<object>pparticle;

   //   øid_construct(pparticle, pdescriptor->m_type);

   //   if(!pparticle)
   //   {

   //      informationf("form_control::create_interaction: failed to create control, allocation error");

   //      return false;

   //   }

   //   ::pointer<interaction>pinteraction = pparticle;

   //   if(!pinteraction)
   //   {

   //      pparticle.release();

   //      informationf("form_control::create_interaction: failed to create control, object is not derived from user::control_descriptor");

   //      return false;

   //   }

   //   pdescriptor->m_iItem = iIndex;*/

   //   if(!create_interaction(pinteractionParent, atom))
   //   {

   //      return false;

   //   }

   //   return true;

//   }


   void form_control::_001SetControlFactory()
   {

   }


   void form_control::soft_reload()
   {

   }


   // ::axis::application * form_control::get_app()
   // {
   //
   //    return ::is_set(m_papplication) ? m_papplication->m_papplication : nullptr;
   //
   // }
   //
   //
   // ::axis::session * form_control::get_session()
   // {
   //
   //    return ::is_set(m_papplication) ? m_papplication->m_psession : nullptr;
   //
   // }
   //
   //
   // ::axis::system * form_control::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::axis::user * form_control::axisuser()
   // {
   //
   //    return user() ? user()->m_paxisuser : nullptr;
   //
   // }


   string form_control::get_path()
   {

      return "";

   }


   bool form_control::open_document(const ::payload & payloadFile)
   {

      auto bOk = ::user::form::open_document(payloadFile);

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   bool form_control::open_html(const ::scoped_string & scopedstr)
   {

      auto bOk = ::user::form::open_html(scopedstr);

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   //void form_control::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   if (ptopic->id() == ::id_create)
   //   {

   //      if (is_child(ptopic->user_interaction()))
   //      {

   //         ptopic->user_interaction()->m_pform = this;

   //      }

   //   }
   //   else if(ptopic->id() == ::id_set_focus)
   //   {

   //      if(!_001OnControlSetFocus(ptopic->user_interaction()))
   //      {

   //         ptopic->Nok();

   //         return;

   //      }

   //   }
   //   else if(ptopic->id() == ::id_kill_focus)
   //   {

   //      if(!_001OnControlKillFocus(ptopic->user_interaction()))
   //      {

   //         ptopic->Nok();

   //         return;

   //      }

   //   }

   //   //if(m_pcallback != nullptr)
   //   //{

   //   //   m_pcallback->handle(ptopic, phandlercontext);

   //   //   if(ptopic->m_bRet)
   //   //   {

   //   //      return;

   //   //   }

   //   //}

   //   ::user::interaction::handle(ptopic, phandlercontext);

   //   if(ptopic->m_bRet)
   //   {

   //      return;

   //   }

   //   if(ptopic->id() == ::id_tab_key)
   //   {

   //      ::pointer<::user::interaction_base>pfocus = ptopic->user_interaction()->keyboard_get_next_focusable();

   //      if(pfocus != nullptr)
   //      {

   //         pfocus->set_keyboard_focus();

   //      }

   //   }
   //   else if(ptopic->id() == ::id_click)
   //   {

   //      ::pointer<interaction>pinteraction = ptopic->user_interaction();

   //      if (::is_null(pinteraction))
   //      {

   //         return;

   //      }

   //      if(pinteraction->has_function(e_control_function_action))
   //      {

   //         if(pinteraction != nullptr)
   //         {

   //            _001OnButtonAction(pinteraction);

   //            ptopic->m_bRet = true;

   //            return;

   //         }
   //         else
   //         {

   //            return;

   //         }

   //      }

   //   }
   //   else if(ptopic->id() == ::id_set_check && ptopic->m_actioncontext.is_user_source())
   //   {

   //      ::pointer<interaction>pinteraction = ptopic->user_interaction();

   //      if (!pinteraction)
   //      {

   //         return;

   //      }

   //      if(pinteraction->m_eddx == e_control_ddx_dbflags)
   //      {

   //         ::int_array_base ia;

   //         ::pointer<::database::client>pclient = pinteraction;

   //         if (pclient.is_null())
   //         {

   //            informationf("control doesn't implement database::client");

   //            return;

   //         }

   //         pclient->datastream()->get(pinteraction->m_strDataKey, ia);

   //         ::pointer<check>pcheck = ptopic->user_interaction();

   //         if(pcheck->echeck() == ::e_check_checked)
   //         {

   //            ia.add_unique(pinteraction->m_iDataValue);

   //         }
   //         else
   //         {

   //            ia.erase(pinteraction->m_iDataValue);

   //         }

   //         pclient->datastream()->set(pinteraction->m_strDataKey, ia);

   //      }

   //   }

   //   if (::is_set(m_pcallback))
   //   {

   //      m_pcallback->handle(ptopic, phandlercontext);

   //      if (ptopic->m_bRet)
   //      {

   //         return;

   //      }

   //   }

   //}


   bool form_control::_001OnControlSetFocus(::user::interaction * pinteraction)
   {

      return true;

   }


   bool form_control::_001OnControlKillFocus(::user::interaction * pinteraction)
   {

      return true;

   }


   bool form_control::_001Initialize()
   {

      if (m_bInitialized)
      {

         return true;

      }

      _001InitializeFormPreData();

      _001UpdateFunctionStatic();

      for(auto pinteraction : proper_children())
      {

         _001Update(pinteraction);

      }

      m_bInitialized = true;

      return true;

   }


   bool form_control::_001IsPointInside(::user::interaction * pinteraction, const long_long_point & point)
   {

      if(pinteraction == nullptr)
         return false;

      return pinteraction->_001IsPointInside(point);

   }



   //bool form_control::normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor)
   //{

   //   if(pdescriptor->m_type)
   //   {

   //      return true;

   //   }

   //   //pdescriptor->m_type = controltype_to_typeinfo(pdescriptor->get_control_type());

   //   //if(pdescriptor->m_type)
   //   //{

   //   //   return true;

   //   //}

   //   return false;

   //}


   //void form_control::on_before_navigate(::payload & payloadFile,unsigned int nFlags, const ::scoped_string & scopedstrTargetFrameName,byte_array& baPostedData, const ::scoped_string & scopedstrHeaders,bool* pbCancel)

   //{

   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   __UNREFERENCED_PARAMETER(nFlags);
   //   __UNREFERENCED_PARAMETER(scopedstrTargetFrameName);

   //   __UNREFERENCED_PARAMETER(baPostedData);
   //   __UNREFERENCED_PARAMETER(scopedstrHeaders);

   //   __UNREFERENCED_PARAMETER(pbCancel);

   //}


   void form_control::control_get_window_rect(::user::interaction * pinteraction, ::int_rectangle & rectangle)
   {

      pinteraction->window_rectangle(rectangle);

   }
   

   void form_control::control_get_client_rect(::user::interaction * pinteraction, ::int_rectangle & rectangle)
   {

      rectangle = pinteraction->rectangle();

   }


   ::user::form * form_control::get_form()
   {

      if (::is_set(m_pformParent))
      {

         return m_pformParent;

      }

      auto pinteraction = ::user::form::get_form();

      if (!pinteraction)
      {

         return nullptr;

      }

      ::pointer < ::user::form > pform = pinteraction;

      if (!pform)
      {

         return nullptr;

      }

      return pform;

   }


   //void form_control::install_message_routing(::channel * pchannel)
   //{
   //   form_control::install_message_routing(pchannel);

   //}


   //void form_control::on_message_create(::message::message * pmessage)
   //{
   //   pmessage->previous();
   //}


   void form_control::on_timer(::timer * ptimer)
   {

      ::user::form::on_timer(ptimer);

      if(m_pcallback != nullptr)
      {
         
         auto pextendedtopic = __allocate ::extended_topic(id_timer);
         
         pextendedtopic->m_puserelement = this;
         
         pextendedtopic->m_uiEvent = ptimer->m_uTimer;
         
         pextendedtopic->m_etimer = ptimer->m_etimer;
         
         auto papp = get_app();
         
         papp->route(pextendedtopic);
         
         if(pextendedtopic->m_bRet)
         {
            
            return;
            
         }
         
         //m_pcallback->route(pextendedtopic);
         route(pextendedtopic);
         
      }

//      if(ptimer->m_uTimer == 24)
//      {
//
//         kill_timer(24);
//
//         top_level_frame()->EndModalLoop(e_dialog_result_ok);
//
//      }

   }


   void form_control::_001OnUser123(::message::message * pmessage)
   {
      ::pointer<::user::message>pusermessage(pmessage);

#ifdef WINDOWS_DESKTOP

      if(pusermessage->m_wparam == 0x80000001)
      {
      
         if(top_level() != nullptr)
         {

            throw todo;

            //top_level()->set_dialog_result(e_dialog_result_ok);

         }

         return;

      }

#endif

      //if(m_pcallback != nullptr)
      //{
      //   m_pcallback->OnUser123(pusermessage->m_wparam,pusermessage->m_lparam);
      //}
   }

   //::type form_control::controltype_to_typeinfo(::user::enum_control_type econtroltype)
   //{

   //   return papp->user_default_controltype_to_typeinfo(econtroltype);

   //}



   //e_control_ddx_dbflags::e_control_ddx_dbflags(::string strDataKey, iptr value)
   //{

   //   m_key = key;
   //   m_value = value;

   //}


      
} // namespace user


