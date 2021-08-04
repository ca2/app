#include "framework.h"
#include "base/user/user/_user.h"
#include "axis/user/validate.h"
#include "aura/message.h"
//#include "acme/os/_os.h"


namespace user
{


   form_control::form_control()
   {

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


   //__pointer(class control_descriptor) form_control::new_form_control()
   //{

   //   auto pdescriptor = __new(::user::control_descriptor());

   //   m_controldescriptorset.add(pdescriptor);

   //   pdescriptor->m_iControl = m_controldescriptorset.find_first(pdescriptor);

   //   pdescriptor->m_puserinteractionParent = this;

   //   if(pdescriptor->m_bTransparent)
   //   {

   //      switch(pdescriptor->m_econtroltype)
   //      {
   //      case e_control_type_static:
   //      {
   //         /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pinteraction->m_id)->GetSafeoswindow_());
   //         if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
   //         {
   //         pstatic = new CTransparentStatic;
   //         VERIFY(pstatic->subclass_window(pform->get_child_by_id(pinteraction->m_id)->GetSafeoswindow_()));
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

      ::u32 uNotificationCode = HIWORD(wparam);

      ::id id(LOWORD(wparam));

      __pointer(::user::interaction) pinteraction = get_child_by_id(id);

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


   bool form_control::OnCommandButton(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


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


   bool form_control::OnCommandCheckBox(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_check_box);

#ifdef WINDOWS

      //switch(uNotificationCode)
      //{
      //case BN_CLICKED:
      //{
      //   /*      linux   ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->m_id);
      //   i32 i = pbutton->get_check() != 0;
      //   VmsDataSet(pinteraction->m_dataid, 0, 0, i);*/
      //}
      //break;
      //default:
      //   break;
      //}

#endif

      return false;

   }


   bool form_control::OnCommandComboBox(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_combo_box);

#ifdef WINDOWS

      //switch(uNotificationCode)
      //{
      //case CBN_SELCHANGE:
      //{
      //   /* linux         __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) get_child_by_id(pinteraction->m_id);
      //   i32 iSel = pcombo->current_item();
      //   if(iSel != CB_ERR)
      //   {
      //   u32 dwData = pinteraction->GetComboBox()->m_dwaData[iSel];
      //   VmsDataSet(pinteraction->m_dataid, 0, 0, (i32) dwData);
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


   bool form_control::OnCommandEdit(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


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

      pinteraction->_001GetText(str);

      ::user::validate validate;

      if(!validate.Validate(str, pinteraction))
      {
         // que tal um balão para indicar o erro
         return false;
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

         ::database::selection selection;

         _001GetSelection(pinteraction->m_datakey, selection);

         throw_todo();

         //_data_set(selection, payload);

      }

      return true;

   }


   void form_control::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      for(auto pinteraction : proper_children())
      {

         _001Update(pinteraction);

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

      int_array ia;

      try
      {

         throw_todo();

         //pinteraction->data_get(pinteraction->m_datakey,ia);

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

      //if(data_get(pinteraction->m_datakey, payload))
      //{
         /* linux      ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->m_id);
         pbutton->SetCheck((i != 0) ? 1 : 0); */
      //}

   }


   void form_control::_001UpdateComboBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      /* linux   ASSERT(pinteraction->get_type() == e_control_type_combo_box);
      i32 i;
      if(VmsDataGet(pinteraction->m_dataid, 0, 0, i))
      {
      iptr iSel = pinteraction->GetComboBox()->m_dwaData.find_first((u32) i);
      if(iSel >= 0)
      {
      __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) get_child_by_id(pinteraction->m_id);
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

      __keep(m_bOnEditUpdate);

      ASSERT(pinteraction->get_control_type() == e_control_type_edit
             || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      if(pinteraction->has_function(e_control_function_vms_data_edit))
      {
         ::payload payload;
         ::database::selection selection;
         _001GetSelection(pinteraction->m_datakey,selection);
         if(selection.get_item_count() > 0)
         {

            //::database::selection_item & item = selection.get_item(0);

            if (!pinteraction)
            {

               return;

            }

            //if(data_get(pinteraction->m_datakey.m_strDataKey + "." + item.m_datakey.m_strDataKey,::payload))
            //{
            //   switch(payload.get_type())
            //   {
            //   case ::e_type_string:
            //   {

            //      string str;

            //      str = payload.m_str;

            //      pinteraction->_001SetText(str,::e_source_database);

            //   }
            //   break;
            //   case ::e_type_i32:
            //   {

            //      string str;

            //      str.Format("%d",payload.i32());

            //      pinteraction->_001SetText(str,::e_source_database);

            //   }
            //   break;
            //   default:
            //      ASSERT(false);
            //      break;
            //   }
            //}
         }
      }
   }

   void form_control::_001UpdateSimpleList(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;

      ASSERT(pinteraction->get_control_type() == e_control_type_simple_list);

      /*      ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pinteraction->m_id));

      if(typeid(plist->GetDataInterface()) == __type(::user::simple_mesh_data))
      {
      ::user::simple_mesh_data * pdata = dynamic_cast < ::user::simple_mesh_data * > (plist->GetDataInterface());
      string_array stra;
      data_get(pinteraction->m_dataid, stra);
      ASSERT(plist != nullptr);
      pdata->set_data(plist, stra);
      }*/
   }

   void form_control::_000OnPosCreate(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //      __pointer(::user::message) pusermessage(pmessage);
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


   bool form_control::_001GetData(id uId,bool &bData)
   {

      __pointer(::user::interaction) pinteraction = get_child_by_id(uId);

      if(pinteraction == nullptr)
      {

         return false;

      }

      ::payload payload;

      //if(!data_get(pinteraction->m_datakey, payload))
      //{

      //   return false;

      //}

      bData = (payload.i32() != 0) ? 1 : 0;

      return true;

   }


   bool form_control::_001SetData(id uId,bool bData)
   {

      __pointer(::user::interaction) pinteraction = get_child_by_id(uId);

      if(pinteraction == nullptr)
      {

         return false;

      }

      //i32 i = bData ? 1 : 0;

      //data_set(pinteraction->m_datakey,i);

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
      MESSAGE_LINK(e_message_pos_create, pchannel,this,&form_control::_000OnPosCreate);
      MESSAGE_LINK(e_message_language, pchannel,this,&form_control::_001OnAppLanguage);
      //MESSAGE_LINK(e_message_key_down                     , pchannel,this,&form_control::on_message_key_down);
      //MESSAGE_LINK(e_message_key_up                       , pchannel,this,&form_control::on_message_key_up);
      MESSAGE_LINK(WM_USER + 123, pchannel,this,&form_control::_001OnUser123);

      install_update_data_message_routing(pchannel);

   }


   void form_control::_001GetSelection(::database::key & id,::database::selection &selection)
   {

      selection.add_item(id);

   }


   void form_control::on_command(::message::command * pcommand)
   {

      ::user::form::on_command(pcommand);

   }


   void form_control::_001OnNotify(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      __pointer(::message::notify) pnotify(pmessage);

      pnotify->m_bRet = false;

#else

      __throw(todo);

#endif

   }


   void form_control::_001OnMessageNotify(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      // revamp pusermessage->set_lresult(user::NotifyRetContinue);

      pusermessage->m_bRet = false;

   }


   bool form_control::_001Validate(::user::interaction * pinteraction,::payload & payload)
   {

      UNREFERENCED_PARAMETER(pinteraction);
      UNREFERENCED_PARAMETER(payload);

      return true;

   }


   //void form_control::_001RemoveControls()
   //{

   //   m_controldescriptorset.erase_all();

   //}


   bool form_control::_001OnBeforeSave(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

      return true;

   }


   bool form_control::update_data(bool bSaveAndValidate)
   {

      ::user::interaction::update_data(bSaveAndValidate);

      ::user::control_event ev;

      ev.m_bOk = true;

      ev.m_puserinteraction = this;

      if (bSaveAndValidate)
      {

         ev.m_eevent = ::user::e_event_save_form_data;

         m_bNeedSaveFormData = false;

      }
      else
      {

         ev.m_eevent = ::user::e_event_load_form_data;

         m_bNeedLoadFormData = false;

      }

      on_control_event(&ev);

      return ev.m_bOk;

   }


   void form_control::data_on_after_change(::database::client* pclient, const ::database::key& key, const ::payload & payload, ::subject::subject * psubject)
   {

      for(auto pinteraction : proper_children())
      {

         if(pinteraction->m_eddx == e_control_ddx_dbflags)
         {

            _001UpdateDbFlags(pinteraction);

         }
         else if(pinteraction->m_datakey == key)
         {

            _001Update(pinteraction);

         }

      }

   }


   void form_control::_001UpdateFunctionStatic()
   {

      auto papplication = get_application();

      for(auto pinteraction : proper_children())
      {

         if(pinteraction->has_function(e_control_function_static))
         {

            string str;

            str = papplication->load_string(pinteraction->m_id);

            pinteraction->set_window_text(str);

         }
         else if(pinteraction->has_function(e_control_function_static2))
         {

            string str;

            str = papplication->load_string(pinteraction->m_uiText);

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

      ::user::control_event ev;

      ev.m_puserinteraction         = pinteraction;
      ev.m_actioncontext        = ::e_source_database;
      ev.m_eevent       = ::user::e_event_initialize_control;
      ev.m_uiEvent      = 0;

      on_control_event(&ev);

   }


   void form_control::_001OnButtonAction(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

   }


   void form_control::_001OnAppLanguage(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      __keep(m_bOnLanguageChange);

      _017OnAppLanguage();

      pusermessage->m_bRet = false;

   }


   void form_control::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pmessagecreate(pmessage);

      auto pcreate = (::create *) pmessagecreate->get_create();

      if(::is_set(pcreate))
      {

         set_form_callback(pcreate->m_varArgs["form_callback"].cast < ::user::form_callback >());

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
      if(!pinteraction->GetComboBox()->m_datakeyFill.IsNull())
      {
      pinteraction->GetComboBox()->m_wstra.erase_all();
      pinteraction->GetComboBox()->m_dwaData.erase_all();
      ::payload payload;
      payload.m_etype = ::e_type_element;
      payload.m_pca2 = pinteraction->GetComboBox();
      VmsDataGet(
      pinteraction->GetComboBox()->m_datakeyFill,
      0, 0,
      ::payload);
      __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) pinteraction->m_puserinteraction;
      pcombo->ResetContent();
      string str;
      for(i32 i = 0; i < pinteraction->GetComboBox()->m_wstra.get_size(); i++)
      {
      str = pinteraction->GetComboBox()->m_wstra[i];
      pcombo->AddString(str);
      }

      }
      } */
   }


   void form_control::_017OnAppLanguage()
   {

      //for(i32 i = 0; i < m_controldescriptorset.get_size() ; i++)
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
      //         //            ASSERT(pinteraction->m_type->IsDerivedFrom(__type(window)));
      //         if(descriptor.m_pcontrol.is_set())
      //         {
      //            //window_id wndidTemp = get_child_by_id(pinteraction->m_id)->GetSafeoswindow_();
      //            //if(wndidTemp != nullptr)
      //            {
      //               //xxx        VERIFY(pinteraction->m_puserinteraction->subclass_window(wndidTemp));
      //            }
      //         }
      //      }
      //      if(descriptor.m_pcontrol != nullptr)
      //      {
      //         //               ::type ti = typeid(descriptor.m_pcontrol);
      //         /*               if(ti == __type(::user::list))
      //         {
      //         if(descriptor.m_etype == e_control_type_simple_list)
      //         {
      //         ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
      //         plist->m_dataid = descriptor.m_idPrivateDataSection;
      //         plist->_001SetSingleColumnMode(false);
      //         }
      //         }*/
      //         /*            else if(pinteraction->m_type->IsDerivedFrom(__type(simple_static)))
      //         {
      //         simple_static * pstatic = (simple_static *) pinteraction->m_puserinteraction;
      //         pstatic->m_bTransparent = pinteraction->m_bTransparent;
      //         }*/
      //         _001OnInitializeForm(descriptor.m_pcontrol);
      //      }
      //   }
      //}

   }


   //bool form_control::create_interaction(::user::interaction * pinteractionParent, const ::id & id)
   //{

   //   //if(!normalize_control_descriptor_typeinfo(pdescriptor))
   //   //{
   //   //   TRACE("form_control::create_interaction: failed to create control, could not find proper type for allocation");
   //   //   return false;
   //   //}

   ///*   __pointer(object) pobject;

   //   __id_construct(pobject, pdescriptor->m_type);

   //   if(!pobject)
   //   {

   //      TRACE("form_control::create_interaction: failed to create control, allocation error");

   //      return false;

   //   }

   //   __pointer(interaction) pinteraction = pobject;

   //   if(!pinteraction)
   //   {

   //      pobject.release();

   //      TRACE("form_control::create_interaction: failed to create control, object is not derived from user::control_descriptor");

   //      return false;

   //   }

   //   pdescriptor->m_iItem = iIndex;*/

   //   if(!create_interaction(pinteractionParent, id))
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


   string form_control::get_path()
   {

      return "";

   }


   ::e_status form_control::open_document(const ::payload & varFile)
   {

      return true;

   }


   ::e_status     form_control::open_html(const ::string & str)
   {

      return error_not_implemented;

   }

   void form_control::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_create)
      {

         if (is_child(pevent->m_puserinteraction))
         {

            pevent->m_puserinteraction->m_pform = this;

         }

      }
      else if(pevent->m_eevent == ::user::e_event_set_focus)
      {

         if(!_001OnControlSetFocus(pevent->m_puserinteraction))
         {

            pevent->Nok();

            return;

         }

      }
      else if(pevent->m_eevent == ::user::e_event_kill_focus)
      {

         if(!_001OnControlKillFocus(pevent->m_puserinteraction))
         {

            pevent->Nok();

            return;

         }

      }

      //if(m_pcallback != nullptr)
      //{

      //   m_pcallback->on_control_event(pevent);

      //   if(pevent->m_bRet)
      //   {

      //      return;

      //   }

      //}

      ::user::interaction::on_control_event(pevent);

      if(pevent->m_bRet)
      {

         return;

      }

      if(pevent->m_eevent == ::user::e_event_tab_key)
      {

         __pointer(::user::primitive) pfocus = pevent->m_puserinteraction->keyboard_get_next_focusable();

         if(pfocus != nullptr)
         {

            pfocus->set_keyboard_focus();

         }

      }
      else if(pevent->m_eevent == ::user::e_event_click)
      {

         __pointer(interaction) pinteraction = pevent->m_puserinteraction;

         if (::is_null(pinteraction))
         {

            return;

         }

         if(pinteraction->has_function(e_control_function_action))
         {

            if(pinteraction != nullptr)
            {

               _001OnButtonAction(pinteraction);

               pevent->m_bRet = true;

               return;

            }
            else
            {

               return;

            }

         }

      }
      else if(pevent->m_eevent == ::user::e_event_set_check && pevent->m_actioncontext.is_user_source())
      {

         __pointer(interaction) pinteraction = pevent->m_puserinteraction;

         if (!pinteraction)
         {

            return;

         }

         if(pinteraction->m_eddx == e_control_ddx_dbflags)
         {

            int_array ia;

            __pointer(::database::client) pclient = pinteraction;

            if (pclient.is_null())
            {

               TRACE("control doesn't implement database::client");

               return;

            }

            pclient->data_get(pinteraction->m_datakey, ia);

            __pointer(check) pcheck = pevent->m_puserinteraction;

            if(pcheck->echeck() == ::check_checked)
            {

               ia.add_unique(pinteraction->m_iDataValue);

            }
            else
            {

               ia.erase(pinteraction->m_iDataValue);

            }

            pclient->data_set(pinteraction->m_datakey, ia);

         }

      }

      if (::is_set(m_pcallback))
      {

         m_pcallback->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

   }


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


   bool form_control::_001IsPointInside(::user::interaction * pinteraction,point_i64 point)
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


   //void form_control::on_before_navigate(::payload & varFile,u32 nFlags, const ::string & pszTargetFrameName,byte_array& baPostedData, const ::string & pszHeaders,bool* pbCancel)

   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(nFlags);
   //   UNREFERENCED_PARAMETER(pszTargetFrameName);

   //   UNREFERENCED_PARAMETER(baPostedData);
   //   UNREFERENCED_PARAMETER(pszHeaders);

   //   UNREFERENCED_PARAMETER(pbCancel);

   //}


   void form_control::control_get_window_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle)

   {

      pinteraction->get_window_rect(prectangle);


   }

   void form_control::control_get_client_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle)

   {

      pinteraction->get_client_rect(prectangle);


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

      auto pform = pinteraction->cast < ::user::form >();

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


   void form_control::_001OnTimer(::timer * ptimer)
   {

      ::user::form::_001OnTimer(ptimer);

      if(m_pcallback != nullptr)
      {

         ::user::control_event ev;

         ev.m_puserinteraction = this;

         ev.m_eevent = ::user::e_event_timer;

         ev.m_uiEvent = ptimer->m_uEvent;

         ev.m_etimer = ptimer->m_etimer;

         auto papplication = get_application();

         papplication->on_control_event(&ev);

         if(ev.m_bRet)
         {

            return;

         }

         m_pcallback->on_control_event(&ev);

      }

//      if(ptimer->m_uEvent == 24)
//      {
//
//         KillTimer(24);
//
//         top_level_frame()->EndModalLoop(e_dialog_result_ok);
//
//      }

   }


   void form_control::_001OnUser123(::message::message * pmessage)
   {
      __pointer(::user::message) pusermessage(pmessage);

#ifdef WINDOWS_DESKTOP

      if(pusermessage->m_wparam == 0x80000001)
      {
         if(get_top_level() != nullptr)
         {
            get_top_level()->EndModalLoop(e_dialog_result_ok);
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

   //   return papplication->user_default_controltype_to_typeinfo(econtroltype);

   //}



   //e_control_ddx_dbflags::e_control_ddx_dbflags(::database::key key, iptr value)
   //{

   //   m_key = key;
   //   m_value = value;

   //}



} // namespace user


