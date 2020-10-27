#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "axis/user/validate.h"
#include "aura/message.h"


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


   __pointer(class control_descriptor) form_control::new_form_control()
   {

      auto pdescriptor = __new(::user::control_descriptor());

      m_controldescriptorset.add(pdescriptor);

      pdescriptor->m_iControl = m_controldescriptorset.find_first(pdescriptor);

      pdescriptor->m_puserinteractionParent = this;

      if(pdescriptor->m_bTransparent)
      {

         switch(pdescriptor->m_econtroltype)
         {
         case control_type_static:
         {
            /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pinteraction->m_id)->GetSafeoswindow_());
            if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
            {
            pstatic = new CTransparentStatic;
            VERIFY(pstatic->subclass_window(pform->get_child_by_id(pinteraction->m_id)->GetSafeoswindow_()));
            }
            pinteraction->m_unionwndptr.m_pstatic = pstatic;*/
         }
         break;
         default:
            break;

         }

      }

      return pdescriptor;

   }


   bool form_control::OnCommand(WPARAM wparam,LPARAM lparam)
   {

      UINT uiNotificationCode = HIWORD(wparam);

      ::id id(LOWORD(wparam));

      __pointer(::user::interaction) pinteraction = m_controldescriptorset.get_control(this, id);

      if (!pinteraction)
      {

         return false;

      }

      switch(pinteraction->descriptor().get_control_type())
      {
      case control_type_button:
         OnCommandButton(pinteraction,uiNotificationCode,lparam);

         break;
      case control_type_check_box:
         OnCommandCheckBox(pinteraction,uiNotificationCode,lparam);

         break;
      case control_type_combo_box:
         OnCommandComboBox(pinteraction,uiNotificationCode,lparam);

         break;
      case control_type_edit:
         OnCommandEdit(pinteraction,uiNotificationCode,lparam);

         break;
      default:
         break;
      }

      return false;

   }


   bool form_control::OnCommandButton(::user::interaction * pinteraction,UINT uiNotificationCode,LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_button);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case BN_CLICKED:
      {
         if(pinteraction->descriptor().has_function(control_function_action))
         {
            _001OnButtonAction(pinteraction);
            return true;
         }
      }
      break;
      default:
         break;
      }

#endif

      return false;
   }


   bool form_control::OnCommandCheckBox(::user::interaction * pinteraction,UINT uiNotificationCode,LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_check_box);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case BN_CLICKED:
      {
         /*      linux   ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->m_id);
         i32 i = pbutton->get_check() != 0;
         VmsDataSet(pinteraction->descriptor().m_dataid, 0, 0, i);*/
      }
      break;
      default:
         break;
      }

#endif

      return false;

   }


   bool form_control::OnCommandComboBox(::user::interaction * pinteraction,UINT uiNotificationCode,LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_combo_box);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case CBN_SELCHANGE:
      {
         /* linux         __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) get_child_by_id(pinteraction->m_id);
         i32 iSel = pcombo->current_item();
         if(iSel != CB_ERR)
         {
         u32 dwData = pinteraction->GetComboBox()->m_dwaData[iSel];
         VmsDataSet(pinteraction->descriptor().m_dataid, 0, 0, (i32) dwData);
         }*/
      }
      break;
      case EN_KILLFOCUS:
      {
         //_001SaveEdit(control);
      }
      default:
         break;
      }

#endif

      return false;

   }


   bool form_control::OnCommandEdit(::user::interaction * pinteraction,UINT uiNotificationCode,LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_edit);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case EN_CHANGE:
      {
         if(pinteraction->descriptor().has_function(control_function_save_on_change))
         {
            _001SaveEdit(pinteraction);
         }
      }
      break;
      case EN_KILLFOCUS:
      {
         _001SaveEdit(pinteraction);
      }
      default:
         break;
      }

#endif

      return false;

   }


   bool form_control::_001SaveEdit(::user::interaction * pinteraction)
   {

      if (::is_null(pinteraction))
      {

         return false;

      }

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_edit || pinteraction->descriptor().get_control_type() == control_type_edit_plain_text);

      string str;

      pinteraction->_001GetText(str);

      ::user::validate validate;

      if(!validate.Validate(str, &pinteraction->descriptor()))
      {
         // que tal um balão para indicar o erro
         return false;
      }

      var var;

      if(!pinteraction->get_data(pinteraction,var))
      {

         return false;

      }

      if(!_001Validate(pinteraction,var))
      {
         return false;
      }

      if(pinteraction->descriptor().has_function(control_function_vms_data_edit))
      {

         ::database::selection selection;

         _001GetSelection(pinteraction->descriptor().m_datakey, selection);

         throw_todo();

         //_data_set(selection, var);

      }

      return true;

   }


   void form_control::on_apply(::action * paction)
   {

      for(auto & pdescriptor : m_controldescriptorset.ptra())
      {

         auto pinteraction = pdescriptor->m_pinteraction;

         if (!pinteraction)
         {

            continue;

         }

         _001Update(pinteraction);

      }

   }


   void form_control::_001Update(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      switch(pinteraction->descriptor().get_control_type())
      {
      case control_type_check_box:
         _001UpdateCheckBox(pinteraction);
         break;
      case control_type_combo_box:
         _001UpdateComboBox(pinteraction);
         break;
      case control_type_edit:
      case control_type_edit_plain_text:
         _001UpdateEdit(pinteraction);
         break;
      case control_type_simple_list:
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
      switch(pinteraction->descriptor().get_control_type())
      {
      case control_type_check_box:
         //_001UpdateDbFlagsCheckBox(pinteraction);
         break;
      /*   case control_type_combo_box:
      _001UpdateComboBox(control);
      break;
      case control_type_edit:
      case control_type_edit_plain_text:
      _001UpdateEdit(control);
      break;
      case control_type_simple_list:
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

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_check_box);

      ASSERT(pinteraction->descriptor().m_eddx == control_ddx_dbflags);

      int_array ia;

      try
      {

         throw_todo();

         //pinteraction->data_get(pinteraction->descriptor().m_datakey,ia);

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
      ASSERT(pinteraction->descriptor().get_control_type() == control_type_check_box);

      var var;

      //if(data_get(pinteraction->descriptor().m_datakey, var))
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
      /* linux   ASSERT(pinteraction->descriptor().get_type() == control_type_combo_box);
      i32 i;
      if(VmsDataGet(pinteraction->descriptor().m_dataid, 0, 0, i))
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

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_edit
             || pinteraction->descriptor().get_control_type() == control_type_edit_plain_text);

      if(pinteraction->descriptor().has_function(control_function_vms_data_edit))
      {
         var var;
         ::database::selection selection;
         _001GetSelection(pinteraction->descriptor().m_datakey,selection);
         if(selection.get_item_count() > 0)
         {

            //::database::selection_item & item = selection.get_item(0);

            if (!pinteraction)
            {

               return;

            }

            //if(data_get(pinteraction->descriptor().m_datakey.m_strDataKey + "." + item.m_datakey.m_strDataKey,var))
            //{
            //   switch(var.get_type())
            //   {
            //   case ::type_string:
            //   {

            //      string str;

            //      str = var.m_str;

            //      pinteraction->_001SetText(str,::source_database);

            //   }
            //   break;
            //   case ::type_i32:
            //   {

            //      string str;

            //      str.Format("%d",var.i32());

            //      pinteraction->_001SetText(str,::source_database);

            //   }
            //   break;
            //   default:
            //      ASSERT(FALSE);
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

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_simple_list);

      /*      ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pinteraction->m_id));

      if(typeid(plist->GetDataInterface()) == __type(::user::simple_mesh_data))
      {
      ::user::simple_mesh_data * pdata = dynamic_cast < ::user::simple_mesh_data * > (plist->GetDataInterface());
      string_array stra;
      data_get(pinteraction->descriptor().m_dataid, stra);
      ASSERT(plist != nullptr);
      pdata->set_data(plist, stra);
      }*/
   }

   void form_control::_000OnPosCreate(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //      SCAST_PTR(::message::base, pbase, pmessage);
   }

   void form_control::_001InitializeFormPreData()
   {
      if(m_pcallback != nullptr)
      {
         m_pcallback->_001InitializeFormPreData(this);
      }

      /*
      if(GetOwner() != nullptr)
      {
      GetOwner()->SendMessage(
      WM_USER + 723,
      GetDlgCtrlId(),
      (LPARAM) this);
      }
      */

   }


   bool form_control::_001GetData(id uiId,bool &bData)
   {

      __pointer(::user::interaction) pinteraction = m_controldescriptorset.get_control(this, uiId);

      if(pinteraction == nullptr)
      {

         return false;

      }

      var var;

      //if(!data_get(pinteraction->descriptor().m_datakey, var))
      //{

      //   return false;

      //}

      bData = (var.i32() != 0) ? 1 : 0;

      return true;

   }


   bool form_control::_001SetData(id uiId,bool bData)
   {

      __pointer(::user::interaction) pinteraction = m_controldescriptorset.get_control(this, uiId);

      if(pinteraction == nullptr)
      {

         return false;

      }

      //i32 i = bData ? 1 : 0;

      //data_set(pinteraction->descriptor().m_datakey,i);

      return true;

   }


   void form_control::Update(bool bSave)
   {
      if(bSave)
      {

      }
      else
      {

         for(auto & pdescriptor : m_controldescriptorset.ptra())
         {

            auto pinteraction = pdescriptor->m_pinteraction;

            if (!pinteraction)
            {

               continue;

            }

            _001Update(pinteraction);

         }

      }

   }


   void form_control::install_message_routing(::channel *pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel,this,&form_control::_001OnCreate);
      MESSAGE_LINK(e_message_pos_create, pchannel,this,&form_control::_000OnPosCreate);
      MESSAGE_LINK(e_message_language, pchannel,this,&form_control::_001OnAppLanguage);
      //MESSAGE_LINK(WM_KEYDOWN                     , pchannel,this,&form_control::_001OnKeyDown);
      //MESSAGE_LINK(WM_KEYUP                       , pchannel,this,&form_control::_001OnKeyUp);
      MESSAGE_LINK(WM_USER + 123, pchannel,this,&form_control::_001OnUser123);

      install_update_data_message_routing(pchannel);

   }


   void form_control::_001GetSelection(::database::key & id,::database::selection &selection)
   {

      selection.add_item(id);

   }


   void form_control::on_command(::user::command * pcommand)
   {

      ::user::form::on_command(pcommand);

   }


   void form_control::_001OnNotify(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      SCAST_PTR(::message::notify,pnotify,pmessage);

      pnotify->m_bRet = false;

#else

      __throw(todo());

#endif

   }


   void form_control::_001OnMessageNotify(::message::message * pmessage)
   {

      SCAST_PTR(::message::base,pbase,pmessage);

      // revamp pbase->set_lresult(user::NotifyRetContinue);

      pbase->m_bRet = false;

   }


   bool form_control::_001Validate(::user::interaction * pinteraction,var & var)
   {

      UNREFERENCED_PARAMETER(pinteraction);
      UNREFERENCED_PARAMETER(var);

      return true;

   }


   void form_control::_001RemoveControls()
   {

      m_controldescriptorset.remove_all();

   }


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

      ev.m_puie = this;

      if (bSaveAndValidate)
      {

         ev.m_eevent = ::user::event_save_form_data;

         m_bNeedSaveFormData = false;

      }
      else
      {

         ev.m_eevent = ::user::event_load_form_data;

         m_bNeedLoadFormData = false;

      }

      on_control_event(&ev);

      return ev.m_bOk;

   }


   void form_control::data_on_after_change(::database::client* pclient, const ::database::key& key, const var& var, ::action * paction)
   {

      for(auto & pdescriptor : m_controldescriptorset.ptra())
      {

         auto pinteraction = pdescriptor->m_pinteraction;

         if (!pinteraction)
         {

            continue;

         }

         if(pdescriptor->m_eddx == control_ddx_dbflags)
         {

            _001UpdateDbFlags(pinteraction);

         }
         else if(pdescriptor->m_datakey == key)
         {

            _001Update(pinteraction);

         }

      }

   }


   void form_control::_001UpdateFunctionStatic()
   {

      for(auto & pdescriptor : m_controldescriptorset.ptra())
      {

         if(pdescriptor->has_function(control_function_static))
         {

            string str;

            str = Application.load_string(pdescriptor->m_id);

            pdescriptor->m_pinteraction->set_window_text(str);

         }
         else if(pdescriptor->has_function(control_function_static2))
         {

            string str;

            str = Application.load_string(pdescriptor->m_uiText);

            pdescriptor->m_pinteraction->set_window_text(str);

         }

      }

   }




   void form_control::WfiOnClose()
   {

      post_message(WM_CLOSE);

   }


   void form_control::_001OnInitializeForm(::user::interaction * pinteraction)
   {

      ::user::control_event ev;

      ev.m_puie         = pinteraction;
      ev.m_actioncontext        = ::source_database;
      ev.m_eevent       = ::user::event_initialize_control;
      ev.m_uiEvent      = 0;

      on_control_event(&ev);

   }


   void form_control::_001OnButtonAction(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

   }


   void form_control::_001OnAppLanguage(::message::message * pmessage)
   {

      SCAST_PTR(::message::base,pbase,pmessage);

      __keep(m_bOnLanguageChange);

      _017OnAppLanguage();

      pbase->m_bRet = false;

   }


   void form_control::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pmessagecreate, pmessage);

      auto pcreate = (::create *) pmessagecreate->m_lpcreatestruct->CREATE_STRUCT_P_CREATE_PARAMS;

      if(::is_set(pcreate))
      {

         set_form_callback(pcreate->m_varArgs["form_callback"].cast < ::user::form_callback >());

      }

      if (pmessagecreate->previous())
      {

         return;

      }

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
      pinteraction->GetComboBox()->m_wstra.remove_all();
      pinteraction->GetComboBox()->m_dwaData.remove_all();
      var var;
      var.m_etype = ::type_element;
      var.m_pca2 = pinteraction->GetComboBox();
      VmsDataGet(
      pinteraction->GetComboBox()->m_datakeyFill,
      0, 0,
      var);
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
      //         if(descriptor.m_etype == control_type_simple_list)
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


   bool form_control::create_control(class control_descriptor * pdescriptor, index iIndex)
   {

      if(!normalize_control_descriptor_typeinfo(pdescriptor))
      {
         TRACE("form_control::create_control: failed to create control, could not find proper type for allocation");
         return false;
      }

      __pointer(object) pobject;

      __id_construct(pobject, pdescriptor->m_type);

      if(!pobject)
      {

         TRACE("form_control::create_control: failed to create control, allocation error");

         return false;

      }

      __pointer(interaction) pinteraction = pobject;

      if(!pinteraction)
      {

         pobject.release();

         TRACE("form_control::create_control: failed to create control, object is not derived from user::control_descriptor");

         return false;

      }

      pdescriptor->m_iItem = iIndex;

      if(!pinteraction->create_control(pdescriptor))
      {

         pinteraction.release();

         return false;

      }

      return true;

   }


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


   ::estatus form_control::open_document(const var & varFile)
   {

      return true;

   }


   ::estatus     form_control::open_html(const ::string & str)
   {

      return error_not_implemented;

   }

   void form_control::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_create)
      {

         if (is_child(pevent->m_puie))
         {

            pevent->m_puie->m_pform = this;

         }

      }
      else if(pevent->m_eevent == ::user::event_set_focus)
      {

         if(!_001OnControlSetFocus(pevent->m_puie))
         {

            pevent->Nok();

            return;

         }

      }
      else if(pevent->m_eevent == ::user::event_kill_focus)
      {

         if(!_001OnControlKillFocus(pevent->m_puie))
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

      if(pevent->m_eevent == ::user::event_tab_key)
      {

         __pointer(::user::primitive) pfocus = pevent->m_puie->keyboard_get_next_focusable();

         if(pfocus != nullptr)
         {

            auto psession = Session;

            psession->set_keyboard_focus(pfocus);

         }

      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {

         __pointer(interaction) pinteraction = pevent->m_puie;

         if (::is_null(pinteraction))
         {

            return;

         }

         class control_descriptor * pdescriptor = pinteraction->m_pdescriptor;

         if (::is_null(pdescriptor))
         {

            return;

         }

         if(pdescriptor->has_function(control_function_action))
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
      else if(pevent->m_eevent == ::user::event_set_check && pevent->m_actioncontext.is_user_source())
      {

         __pointer(interaction) pinteraction = pevent->m_puie;

         if (!pinteraction)
         {

            return;

         }

         auto pdescriptor = pinteraction->m_pdescriptor;

         if (!pdescriptor)
         {

            return;

         }

         if(pdescriptor->m_eddx == control_ddx_dbflags)
         {

            int_array ia;

            __pointer(::database::client) pclient = pdescriptor->m_pinteraction;

            if (pclient.is_null())
            {

               TRACE("control doesn't implement database::client");

               return;

            }

            pclient->data_get(pdescriptor->m_datakey, ia);

            __pointer(check) pcheck = pevent->m_puie;

            if(pcheck->echeck() == ::check_checked)
            {

               ia.add_unique(pdescriptor->m_iDataValue);

            }
            else
            {

               ia.remove(pdescriptor->m_iDataValue);

            }

            pclient->data_set(pdescriptor->m_datakey, ia);

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

      for(auto & pdescriptor : m_controldescriptorset.ptra())
      {

         __pointer(interaction) pinteraction = pdescriptor->m_pinteraction;

         if (!pinteraction)
         {

            continue;

         }

         _001Update(pinteraction);

      }

      m_bInitialized = true;

      return true;

   }


   bool form_control::_001IsPointInside(::user::interaction * pinteraction,point64 point)
   {

      if(pinteraction == nullptr)
         return false;

      return pinteraction->_001IsPointInside(point);

   }



   bool form_control::normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor)
   {

      if(pdescriptor->m_type)
      {

         return true;

      }

      //pdescriptor->m_type = controltype_to_typeinfo(pdescriptor->get_control_type());

      //if(pdescriptor->m_type)
      //{

      //   return true;

      //}

      return false;

   }


   //void form_control::on_before_navigate(var & varFile,u32 nFlags,const char * pszTargetFrameName,byte_array& baPostedData,const char * pszHeaders,bool* pbCancel)

   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(nFlags);
   //   UNREFERENCED_PARAMETER(pszTargetFrameName);

   //   UNREFERENCED_PARAMETER(baPostedData);
   //   UNREFERENCED_PARAMETER(pszHeaders);

   //   UNREFERENCED_PARAMETER(pbCancel);

   //}


   void form_control::control_get_window_rect(::user::interaction * pinteraction,RECT * prect)

   {

      pinteraction->get_window_rect(prect);


   }

   void form_control::control_get_client_rect(::user::interaction * pinteraction,RECT * prect)

   {

      pinteraction->get_client_rect(prect);


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


   //void form_control::_001OnCreate(::message::message * pmessage)
   //{
   //   pmessage->previous();
   //}


   void form_control::_001OnTimer(::timer * ptimer)
   {

      ::user::form::_001OnTimer(ptimer);

      if(m_pcallback != nullptr)
      {

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::e_event_timer;

         ev.m_uiEvent = ptimer->m_uEvent;

         ev.m_etimer = ptimer->m_etimer;

         Application.on_control_event(&ev);

         if(ev.m_bRet)
         {

            return;

         }

         m_pcallback->on_control_event(&ev);

      }

      if(ptimer->m_uEvent == 24)
      {
         KillTimer(24);
         GetTopLevelFrame()->EndModalLoop(IDOK);
      }
   }

   void form_control::_001OnUser123(::message::message * pmessage)
   {
      SCAST_PTR(::message::base,pbase,pmessage);
      if(pbase->m_wparam == 0x80000001)
      {
         if(GetTopLevel() != nullptr)
         {
            GetTopLevel()->EndModalLoop(IDOK);
         }
         return;
      }
      //if(m_pcallback != nullptr)
      //{
      //   m_pcallback->OnUser123(pbase->m_wparam,pbase->m_lparam);
      //}
   }

   //::type form_control::controltype_to_typeinfo(::user::e_control_type econtroltype)
   //{

   //   return Application.user_default_controltype_to_typeinfo(econtroltype);

   //}



   //control_ddx_dbflags::control_ddx_dbflags(::database::key key, iptr value)
   //{

   //   m_key = key;
   //   m_value = value;

   //}



} // namespace user


