#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "axis/user/user/_component.h"
#endif
#include "window.h"
#include "axis/user/user/validate.h"
////#include "aura/message.h"
#include "acme/include/_c_swap.h"
#include "aura/message/user.h"
#include "axis/platform/application.h"


namespace user
{


   form_window::form_window()
   {

      m_bOnEditUpdate         = false;
      m_bOnLanguageChange     = false;
      m_bInitialized          = false;

   }


   form_window::~form_window()
   {

   }


//   index form_window::_001AddControl(::user::interaction * pinteractionParent, const ::atom & atom)
//   {
//
//      //index indexNew = m_controldescriptorset.add(memory_new class control_descriptor(descriptorParam));
//
//      m_controldescriptorset.add(pdescriptor);
//
//      ///descriptorParam.clear();
//
//      pdescriptor->m_puserinteractionParent = this;
//
//      if(pdescriptor->m_bTransparent)
//      {
//
//         switch(pdescriptor->m_econtroltype)
//         {
//         case e_control_type_static:
//         {
//            /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pinteraction->m_atom)->GetSafeoswindow_());
//                        if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
//                        {
//                           pstatic = memory_new CTransparentStatic;
//                           VERIFY(pstatic->subclass_window(pform->get_child_by_id(pinteraction->m_atom)->GetSafeoswindow_()));
//                        }
//                        pinteraction->m_unionwndptr.m_pstatic = pstatic;*/
//         }
//         break;
//         default:
//            break;
//
//         }
//      }
//
////      if(pdescriptor->m_type)
////      {
////
////         if(pdescriptor->m_bCreated && pdescriptor->m_pcontrol != nullptr)
////         {
////
////            pdescriptor->m_bCreated = false;
////
////            pdescriptor->m_pcontrol.release();
////
////            pdescriptor->m_pcontrol.release();
////
////         }
////
////         if( (pdescriptor->m_pcontrol.m_p) != nullptr)
////         {
////         }
////         else
////         {
////
////            if(create_interaction(pdescriptor))
////            {
////            }
////            else
////            {
////               // Failed creation
////               ASSERT(false);
////            }
////         }
////
////      }
////      else if(create_interaction(pdescriptor))
////      {
////      }
////      if(pdescriptor->m_pcontrol != nullptr)
////      {
////         //::type ti = typeid(pdescriptor->m_pcontrol);
/////*         if(ti == __type(::user::list))
////         {
////            if(pdescriptor->m_etype == e_control_type_simple_list)
////            {
////               ::user::list * plist = dynamic_cast <::user::list *>(pdescriptor->m_pcontrol);
////               plist->m_dataid = pdescriptor->m_atomPrivateDataSection;
////               plist->_001SetSingleColumnMode(false);
////            }
////         }*/
////         /*else if(ti == __type(simple_still))
////         {
////            simple_still * pstatic = (simple_still *) pinteraction->m_puserinteraction;
////            pstatic->m_bTransparent = pinteraction->m_bTransparent;
////         }*/
////
//
//      //}
//
//      return m_controldescriptorset.get_upper_bound();
//
//   }


   bool form_window::OnCommand(wparam wparam, lparam lparam)
   {

      ::u32 uNotificationCode = second_u16(wparam);

      ::atom atom(first_u16(wparam));

      auto pinteraction = get_child_by_id(atom);

      if(!pinteraction)
      {

         return false;

      }

      switch(pinteraction->get_control_type())
      {
      case e_control_type_button:
         OnCommandButton(pinteraction, uNotificationCode, lparam);

         break;
      case e_control_type_check_box:
         OnCommandCheckBox(pinteraction, uNotificationCode, lparam);

         break;
      case e_control_type_combo_box:
         OnCommandComboBox(pinteraction, uNotificationCode, lparam);

         break;
      case e_control_type_edit:
         OnCommandEdit(pinteraction, uNotificationCode, lparam);

         break;
      default:
         break;
      }

      return false;

   }


   bool form_window::OnCommandButton(::user::interaction * pinteraction, ::u32 uNotificationCode, lparam lparam)

   {

      __UNREFERENCED_PARAMETER(lparam);


      ASSERT(pinteraction != nullptr);

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_button);

#ifdef WINDOWS

      /*switch(uNotificationCode)
      {
      case BN_CLICKED:
      {
         if(pinteraction->has_function(e_control_function_action))
         {
            _001OnButtonAction(pinteraction);
            return true;
         }
      }
      break;
      default:
         break;
      }*/

#endif

      return false;
   }


   bool form_window::OnCommandCheckBox(::user::interaction * pinteraction, ::u32 uNotificationCode, lparam lparam)

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
      //   /*      linux   ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->m_atom);
      //            i32 i = pbutton->get_check() != 0;
      //            VmsDataSet(pinteraction->m_dataid, 0, 0, i);*/
      //}
      //break;
      //default:
      //   break;
      //}

#endif

      return false;

   }


   bool form_window::OnCommandComboBox(::user::interaction * pinteraction, ::u32 uNotificationCode, lparam lparam)

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
      //   /* linux         ::pointer<::user::combo_box>pcombo = (::pointer<::user::combo_box>get_child_by_id(pinteraction->m_atom);
      //            i32 iSel = pcombo->current_item();
      //            if(iSel != CB_ERR)
      //            {
      //               u32 dwData = pinteraction->GetComboBox()->m_dwaData[iSel];
      //               VmsDataSet(pinteraction->m_dataid, 0, 0, (i32) dwData);
      //            }*/
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


   bool form_window::OnCommandEdit(::user::interaction * pinteraction, ::u32 uNotificationCode, lparam lparam)

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


   bool form_window::_001SaveEdit(::user::interaction * pinteraction)
   {

      if(pinteraction == nullptr)
         return false;

      ASSERT(pinteraction->get_control_type() == e_control_type_edit || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      if(!pinteraction)
      {

         return false;

      }

      string str;

      pinteraction->_001GetText(str);

      ::user::validate validate;

      try
      {

         validate.Validate(str, pinteraction);
         //{
         //   // que tal um balão para indicar o erro
         //   return false;
         //}

      }
      catch (...)
      {

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

         //auto ptask = new_task();

         //ptask->set_handled_by(this);

         throw_todo();

         //_data_set(selection, payload, &update);

      }

      return true;

   }


   void form_window::handle(::topic * ptopic, ::context * pcontext)
   {
      
      
      __UNREFERENCED_PARAMETER(ptopic);


      //for(i32 i = 0; i < m_controldescriptorset.get_size(); i++)
      //{
      //   ::user::interaction * pinteraction = m_controldescriptorset[i]->m_pcontrol;
      //   if(pinteraction == nullptr)
      //      continue;
      //   _001Update(pinteraction);
      //}

      ::user::form_control::handle(ptopic, pcontext);

      if (ptopic->m_bRet)
      {

         return;

      }

      if (ptopic->m_atom == ::id_tab_key)
      {

         ::pointer<::user::primitive>pfocus = ptopic->user_interaction()->keyboard_get_next_focusable();

         if (pfocus != nullptr)
         {

            pfocus->set_keyboard_focus();

         }

      }
      else if (ptopic->m_atom == ::id_click)
      {

         ::pointer<interaction>pinteraction = ptopic->user_interaction();

         if (!pinteraction)
         {

            return;

         }

         if (pinteraction->has_function(e_control_function_action))
         {

            if (pinteraction != nullptr)
            {

               _001OnButtonAction(pinteraction);

               ptopic->m_bRet = true;

            }

            return;

         }

      }
      else if (ptopic->m_atom == ::id_set_check && ptopic->m_actioncontext.is_user_source())
      {

         ::pointer<interaction>pinteraction = ptopic->user_interaction();

         if (!pinteraction)
         {

            return;

         }

         if (pinteraction->m_eddx == e_control_ddx_dbflags)
         {

            iptr_array ia;

            //pinteraction->datastream()->get(pdescriptor->m_datakey, ia);

            ::pointer<check>pcheck = ptopic->user_interaction();

            if (pcheck->echeck() == ::e_check_checked)
            {

               ia.add_unique(pinteraction->m_iDataValue);

            }
            else
            {

               ia.erase(pinteraction->m_iDataValue);

            }

            //pinteraction->datastream()->get(pdescriptor->m_datakey, ia);

         }

      }


   }

   void form_window::_001Update(::user::interaction * pinteraction)
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

   void form_window::_001UpdateDbFlags(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      switch(pinteraction->get_control_type())
      {
      case e_control_type_check_box:
         _001UpdateDbFlagsCheckBox(pinteraction);
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

   void form_window::_001UpdateDbFlagsCheckBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      ASSERT(pinteraction->get_control_type() == e_control_type_check_box);
      ASSERT(pinteraction->m_eddx == e_control_ddx_dbflags);
      iptr_array ia;
      //try
      //{
      //   pinteraction->datastream()->get(pinteraction->m_datakey, ia);

      //}
      //catch(...)
      //{
      //   return;
      //}
      {
         /*         check_box * pcheck = dynamic_cast < check_box * > (pinteraction);
                  if(pcheck != nullptr)
                  {
                     index i = 0;
                     if(ia.BaseSortFind(pinteraction->m_ddx.m_pdbflags->m_value, i))
                     {
                        pcheck->_001SetCheck(e_check_checked, false);
                     }
                     else
                     {
                        pcheck->_001SetCheck(e_check_unchecked, false);
                     }
                  }*/
      }
   }


   void form_window::_001UpdateCheckBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      ASSERT(pinteraction->get_control_type() == e_control_type_check_box);
      //i32 i;
      //if(datastream()->get(pinteraction->m_datakey, i))
      //{
      //   /* linux      ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->m_atom);
      //         pbutton->SetCheck((i != 0) ? 1 : 0); */
      //}
   }

   void form_window::_001UpdateComboBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      /* linux   ASSERT(pinteraction->get_control_type() == e_control_type_combo_box);
         i32 i;
         if(VmsDataGet(pinteraction->m_dataid, 0, 0, i))
         {
            iptr iSel = pinteraction->GetComboBox()->m_dwaData.find_first((u32) i);
            if(iSel >= 0)
            {
               ::pointer<::user::combo_box>pcombo = (::pointer<::user::combo_box>get_child_by_id(pinteraction->m_atom);
               pcombo->set_current_item(iSel);
            }
         }*/
   }

   void form_window::_001UpdateEdit(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;

      __task_guard(m_bOnEditUpdate);

      ASSERT(pinteraction->get_control_type() == e_control_type_edit
             || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      if(pinteraction->has_function(e_control_function_vms_data_edit))
      {

         ::payload payload;
         ::database::selection selection;
         _001GetSelection(pinteraction->m_datakey, selection);
         if(selection.get_item_count() > 0)
         {

            if(!pinteraction)
            {

               return;

            }

            //if(datastream()->get(pinteraction->m_datakey + item.m_datakey, payload))
            //{

            //   switch(payload.get_type())
            //   {
            //   case ::e_type_string:
            //   {
            //      string str;
            //      str = payload.m_str;
            //      pinteraction->_001SetText(str, ::e_source_database);
            //   }
            //   break;
            //   case ::e_type_i32:
            //   {
            //      string str;
            //      str.format("%d", payload.i32());
            //      pinteraction->_001SetText(str, ::e_source_database);
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

   void form_window::_001UpdateSimpleList(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;

      ASSERT(pinteraction->get_control_type() == e_control_type_simple_list);

      /*      ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pinteraction->m_atom));

            if(typeid(plist->GetDataInterface()) == __type(::user::simple_mesh_data))
            {
               ::user::simple_mesh_data * pdata = dynamic_cast < ::user::simple_mesh_data * > (plist->GetDataInterface());
               string_array stra;
               datastream()->get(pinteraction->m_dataid, stra);
               ASSERT(plist != nullptr);
               pdata->set_data(plist, stra);
            }*/
   }

   void form_window::_000OnPosCreate(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::user::message>pusermessage(pmessage);
   }

   void form_window::_001InitializeFormPreData()
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


   bool form_window::_001GetData(const ::atom & atom, bool &bData)
   {

      synchronous_lock synchronouslock(mutex());

      ::pointer<interaction>pinteraction = get_child_by_id(atom);

      if (!pinteraction)
      {

         return false;

      }

      //i32 i;

      //if(!datastream()->get(pinteraction->m_datakey, i))
      //   return false;

//      bData = (i != 0) ? 1 : 0;

      return true;

   }


   bool form_window::_001SetData(const ::atom & atom, bool bData)
   {

      ::pointer<interaction>pinteraction = get_child_by_id(atom);

      if (!pinteraction)
      {

         return false;

      }

      //i32 i = bData ? 1 : 0;
      //datastream()->set(pinteraction->m_datakey, i);
      return true;

   }

   void form_window::Update(bool bSave)
   {
      if(bSave)
      {

      }
      else
      {
         //for(i32 i = 0; i < m_controldescriptorset.get_size(); i++)
         //{
         //   ::pointer<control>pinteraction = m_controldescriptorset[i]->m_pcontrol;
         //   if(pinteraction == nullptr)
         //      continue;
         //   _001Update(pinteraction);
         //}
      }
   }



   void form_window::_001GetSelection(::database::key & atom, ::database::selection &selection)
   {
      selection.add_item(atom);
   }


   void form_window::on_command(::message::command * pcommand)
   {

      ::user::form::on_command(pcommand);

   }


   void form_window::_001OnNotify(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      ::pointer<::message::notify>pnotify(pmessage);

      pnotify->m_bRet = false;

#else

      throw ::exception(todo);

#endif

   }


   void form_window::_001OnMessageNotify(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      // revamp pusermessage->set_lresult(user::NotifyRetContinue);

      pusermessage->m_bRet = false;

   }


   bool form_window::_001Validate(::user::interaction * pinteraction, ::payload & payload)
   {

      __UNREFERENCED_PARAMETER(pinteraction);
      __UNREFERENCED_PARAMETER(payload);

      return true;

   }


   //void form_window::_001RemoveControls()
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   //m_controldescriptorset.erase_all();

   //}


   bool form_window::_001OnBeforeSave(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return true;

   }


   void form_window::data_on_after_change(::database::client* pclient, const ::database::key& key, const ::payload & payload, ::topic * ptopic)
   {

      synchronous_lock synchronouslock(mutex());

      if(ptopic != nullptr)
      {

         if(!ptopic->is_modified())
         {

            return;

         }

      }

      //for(i32 iControl = 0; iControl < m_controldescriptorset.get_size(); iControl++)
      //{

      //   auto pdescriptor = m_controldescriptorset[iControl];

      //   if (!pdescriptor)
      //   {

      //      continue;

      //   }

      //   auto pinteraction = pdescriptor->m_pinteraction;

      //   if (!pinteraction)
      //   {

      //      continue;

      //   }

      //   if(pdescriptor->m_eddx == e_control_ddx_dbflags)
      //   {

      //      _001UpdateDbFlags(pinteraction);

      //   }
      //   else if(pdescriptor->m_datakey == key)
      //   {

      //      _001Update(pinteraction);

      //   }

      //}

   }


   void form_window::_001UpdateFunctionStatic()
   {

      synchronous_lock synchronouslock(mutex());

      auto papp = get_app();

      for(auto pinteraction : proper_children())
      {

         if(pinteraction->has_function(e_control_function_static))
         {

            string str;

            str = papp->load_string(pinteraction->m_atom);

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


   void form_window::WfiOnClose()
   {

      post_message(e_message_close);

   }


   void form_window::_001OnInitializeControl(::user::interaction * pinteraction)
   {

      if (m_pcallback)
      {

         m_pcallback->_001OnInitializeControl(pinteraction);

      }

      auto pextendedtopic = create_extended_topic(id_initialize_control);

      pextendedtopic->m_puserelement         = pinteraction;
      pextendedtopic->m_actioncontext        = ::e_source_database;
      pextendedtopic->m_uiEvent              = 0;

      route(pextendedtopic);

   }


   void form_window::_001OnButtonAction(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

   }


   void form_window::_001OnInitializeForm()
   {

      if (m_pcallback)
      {

         m_pcallback->_001OnInitializeForm();

      }

   }


   //void form_window::_001OnInitializeControl(::user::interaction * pinteraction)
   //{


   //}



   void form_window::_001OnAppLanguage(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      __keep(m_bOnLanguageChange);

      _017OnAppLanguage();

      pusermessage->m_bRet = false;

   }


   void form_window::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      if(pmessage->m_bRet)
      {

         return;

      }

   }


   void form_window::_001FillCombo(::user::interaction * pinteraction)
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
               ::pointer<::user::combo_box>pcombo = (::pointer<::user::combo_box>pinteraction->m_puserinteraction;
               pcombo->reset_content();
               string str;
               for(i32 i = 0; i < pinteraction->GetComboBox()->m_wstra.get_size(); i++)
               {
                  str = pinteraction->GetComboBox()->m_wstra[i];
                  pcombo->AddString(str);
               }

            }
         } */
   }


   void form_window::_017OnAppLanguage()
   {

//      for(i32 i = 0; i < m_controldescriptorset.get_size() ; i++)
//      {
//         class control_descriptor & descriptor = m_controldescriptorset(i);
//         if(descriptor.m_type)
//         {
//            if(descriptor.m_bCreated && descriptor.m_pcontrol != nullptr)
//            {
//            }
//            else if(descriptor.m_bSubclassed && descriptor.m_pcontrol != nullptr)
//            {
//   //            if(::IsWindow(pinteraction->m_puserinteraction->GetSafeoswindow_()))
//               {
//                  //xxx pinteraction->m_puserinteraction->unsubclass_window();
//               }
//   //            ASSERT(pinteraction->m_type->IsDerivedFrom(__type(window)));
//               if(descriptor.m_pcontrol.is_set())
//               {
//                  //window_id wndidTemp = get_child_by_id(pinteraction->m_atom)->GetSafeoswindow_();
//                  //if(wndidTemp != nullptr)
//                  {
//             //xxx        VERIFY(pinteraction->m_puserinteraction->subclass_window(wndidTemp));
//                  }
//               }
//            }
//            if(descriptor.m_pcontrol != nullptr)
//            {
////               ::type ti = typeid(descriptor.m_pcontrol);
///*               if(ti == __type(::user::list))
//               {
//                  if(descriptor.m_etype == e_control_type_simple_list)
//                  {
//                     ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
//                     plist->m_dataid = descriptor.m_atomPrivateDataSection;
//                     plist->_001SetSingleColumnMode(false);
//                  }
//               }*/
//   /*            else if(pinteraction->m_type->IsDerivedFrom(__type(simple_still)))
//               {
//                  simple_still * pstatic = (simple_still *) pinteraction->m_puserinteraction;
//                  pstatic->m_bTransparent = pinteraction->m_bTransparent;
//               }*/
//               _001OnInitializeForm(descriptor.m_pcontrol);
//            }
//         }
//      }

   }


   //bool form_window::create_interaction(::user::interaction * pinteractionParent, const ::atom & atom)
   //{

   //   //if(!normalize_control_descriptor_typeinfo(pdescriptor))
   //   //{

   //   //   TRACE("form_window::create_interaction: failed to create control, could not find proper type for allocation");

   //   //   return false;

   //   //}

   //   //auto pinteraction = papp->__id_create <::user::interaction>(pdescriptor->m_type);

   //   //if(!pinteraction)
   //   //{

   //   //   TRACE("form_window::create_interaction: failed to create control, allocation error");

   //   //   return false;

   //   //}

   //   if(!create_interaction(pinteractionParent, atom))
   //   {

   //      return false;

   //   }

   //   //pinteraction->m_iEditItem = iItem;

   //   //_001OnInitializeControl(pinteraction);

   //   //pdescriptor->m_pinteraction = pinteraction;

   //   return true;

   //}


   void form_window::_001SetControlFactory()
   {

   }


   string form_window::get_path()
   {
      return "";
   }


   bool form_window::open_document(const ::payload & payloadFile)
   {

      //auto estatus = 
      
      auto bOk = ::user::form_control::open_document(payloadFile);

      if (!bOk)
      {

         return false;

      }

      //if(!estatus)
      //{

      //   return estatus;

      //}

      return true;

   }

   //if (ptopic->m_atom == ::id_form_initialize)
   //{

   //   call_sync(get_document()->m_mapRunnablea["load"]);

   //}


   //void form_window::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   ::user::form_control::handle(ptopic, pcontext);

   //   if (ptopic->m_bRet)
   //   {

   //      return;

   //   }

   //   if(ptopic->m_atom == ::id_tab_key)
   //   {

   //      ::pointer<::user::primitive>pfocus = ptopic->user_interaction()->keyboard_get_next_focusable();

   //      if(pfocus != nullptr)
   //      {

   //         pfocus->set_keyboard_focus();

   //      }

   //   }
   //   else if(ptopic->m_atom == ::id_click)
   //   {

   //      ::pointer<interaction>pinteraction = ptopic->user_interaction();

   //      if (!pinteraction)
   //      {

   //         return;

   //      }

   //      if(pinteraction->has_function(e_control_function_action))
   //      {

   //         if(pinteraction != nullptr)
   //         {

   //            _001OnButtonAction(pinteraction);

   //            ptopic->m_bRet = true;

   //         }

   //         return;

   //      }

   //   }
   //   else if(ptopic->m_atom == ::id_set_check && ptopic->m_actioncontext.is_user_source())
   //   {

   //      ::pointer<interaction>pinteraction = ptopic->user_interaction();

   //      if (!pinteraction)
   //      {

   //         return;

   //      }

   //      if(pinteraction->m_eddx == e_control_ddx_dbflags)
   //      {

   //         iptr_array ia;

   //         //pinteraction->datastream()->get(pdescriptor->m_datakey, ia);

   //         ::pointer<check>pcheck = ptopic->user_interaction();

   //         if(pcheck->echeck() == ::e_check_checked)
   //         {

   //            ia.add_unique(pinteraction->m_iDataValue);

   //         }
   //         else
   //         {

   //            ia.erase(pinteraction->m_iDataValue);

   //         }

   //         //pinteraction->datastream()->get(pdescriptor->m_datakey, ia);

   //      }

   //   }

   //}


   bool form_window::_001Initialize()
   {

      if(m_bInitialized)
         return true;

      synchronous_lock synchronouslock(mutex());

      _001InitializeFormPreData();

      _001UpdateFunctionStatic();

      for(auto pinteraction : proper_children())
      {

         _001Update(pinteraction);

      }

      m_bInitialized = true;

      return true;

   }


   bool form_window::_001IsPointInside(::user::interaction * pinteraction, point_i64 point)
   {

      if(pinteraction == nullptr)
      {

         return false;

      }

      return pinteraction->_001IsPointInside(point);

   }


   //bool form_window::normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor)
   //{

   //   if(pdescriptor->m_type)
   //   {

   //      return true;

   //   }

   //   auto psession = get_session();

   //   pdescriptor->m_type = psession->user()->controltype_to_typeinfo(pdescriptor->get_control_type());

   //   if(pdescriptor->m_type)
   //   {

   //      return true;

   //   }

   //   return false;

   //}


   //void form_window::on_before_navigate(::payload & payloadFile, u32 nFlags, const ::string & pszTargetFrameName, byte_array& baPostedData, const ::string & pszHeaders, bool* pbCancel)

   //{

   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   __UNREFERENCED_PARAMETER(nFlags);
   //   __UNREFERENCED_PARAMETER(pszTargetFrameName);

   //   __UNREFERENCED_PARAMETER(baPostedData);
   //   __UNREFERENCED_PARAMETER(pszHeaders);

   //   __UNREFERENCED_PARAMETER(pbCancel);

   //}
   //

   //::form_property_set * form_window::get_form_property_set()
   //{
   //
   //   auto pset = form_callback::get_form_property_set();
   //
   //   if(pset)
   //   {
   //
   //      return pset;
   //
   //   }
   //
   //   pset = form_control::get_form_property_set();
   //
   //   if(pset)
   //   {
   //
   //      return pset;
   //
   //   }
   //
   //   return nullptr;
   //
   //}


   void form_window::control_get_window_rect(::user::interaction * pinteraction, RECTANGLE_I32 * prectangle)

   {

      pinteraction->get_window_rect(prectangle);


   }


   void form_window::control_get_client_rect(::user::interaction * pinteraction, RECTANGLE_I32 & rectangle)
   {

      pinteraction->get_client_rect(rectangle);

   }


   void form_window::install_message_routing(::channel * pchannel)
   {
      ::user::form_control::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &form_window::on_message_create);
      MESSAGE_LINK(e_message_pos_create, pchannel, this, &form_window::_000OnPosCreate);
      MESSAGE_LINK(e_message_language, pchannel, this, &form_window::_001OnAppLanguage);
      //MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
      //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

   }


} // namespace user



