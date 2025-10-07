#include "framework.h"
#include "window.h"
#include "acme/constant/id.h"
#include "acme/platform/keep.h"
#include "acme/constant/user_message.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"
#include "acme/include/_c_swap.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/database/selection.h"
#include "axis/platform/application.h"
#include "axis/user/user/validate.h"
#include "aura/message/user.h"


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
//      //index indexNew = m_controldescriptorset.add(___new class control_descriptor (descriptorParam));
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
//            /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pinteraction->id())->GetSafeoswindow_());
//                        if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
//                        {
//                           pstatic = ___new CTransparentStatic();
//                           VERIFY(pstatic->subclass_window(pform->get_child_by_id(pinteraction->id())->GetSafeoswindow_()));
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
/////*         if(ti == ::type < ::user::list >())
////         {
////            if(pdescriptor->m_etype == e_control_type_simple_list)
////            {
////               ::user::list * plist = dynamic_cast <::user::list *>(pdescriptor->m_pcontrol);
////               plist->m_dataid = pdescriptor->m_atomPrivateDataSection;
////               plist->_001SetSingleColumnMode(false);
////            }
////         }*/
////         /*else if(ti == ::type < simple_still >())
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

      unsigned int uNotificationCode = upper_unsigned_short(wparam);

      ::atom atom(lower_unsigned_short(wparam));

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


   bool form_window::OnCommandButton(::user::interaction * pinteraction, unsigned int uNotificationCode, lparam lparam)

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


   bool form_window::OnCommandCheckBox(::user::interaction * pinteraction, unsigned int uNotificationCode, lparam lparam)

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
      //            int i = pbutton->get_check() != 0;
      //            VmsDataSet(pinteraction->m_dataid, 0, 0, i);*/
      //}
      //break;
      //default:
      //   break;
      //}

#endif

      return false;

   }


   bool form_window::OnCommandComboBox(::user::interaction * pinteraction, unsigned int uNotificationCode, lparam lparam)

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
      //            int iSel = pcombo->current_item();
      //            if(iSel != CB_ERR)
      //            {
      //               unsigned int dwData = pinteraction->GetComboBox()->m_dwaData[iSel];
      //               VmsDataSet(pinteraction->m_dataid, 0, 0, (int) dwData);
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


   bool form_window::OnCommandEdit(::user::interaction * pinteraction, unsigned int uNotificationCode, lparam lparam)

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

      str = pinteraction->as_text();

      ::user::validate validate;

      try
      {

         validate.Validate(str, pinteraction);
         //{
         //   // que tal um balao para indicar o erro
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

         throw_todo();

//         ::database::selection selection;
//
//         get_selection(pinteraction->m_strDataKey, selection);
//
//         //auto ptask = new_task();
//
//         //ptask->set_handled_by(this);
//
//         throw_todo();
//
//         //_data_set(selection, payload, &update);

      }

      return true;

   }


   void form_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      
      
      __UNREFERENCED_PARAMETER(ptopic);


      //for(int i = 0; i < m_controldescriptorset.get_size(); i++)
      //{
      //   ::user::interaction * pinteraction = m_controldescriptorset[i]->m_pcontrol;
      //   if(pinteraction == nullptr)
      //      continue;
      //   _001Update(pinteraction);
      //}

      ::user::form_control::handle(ptopic, phandlercontext);

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
      else if (ptopic->id() == ::id_set_check && ptopic->m_actioncontext.is_user_source())
      {

         ::pointer<interaction>pinteraction = ptopic->user_interaction();

         if (!pinteraction)
         {

            return;

         }

         if (pinteraction->m_eddx == e_control_ddx_dbflags)
         {

            iptr_array ia;

            //pinteraction->datastream()->get(pdescriptor->m_strDataKey, ia);

            ::pointer<::user::check>pcheck = ptopic->user_interaction();

            if (pcheck->echeck() == ::e_check_checked)
            {

               ia.add_unique(pinteraction->m_iDataValue);

            }
            else
            {

               ia.erase(pinteraction->m_iDataValue);

            }

            //pinteraction->datastream()->get(pdescriptor->m_strDataKey, ia);

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
      //   pinteraction->datastream()->get(pinteraction->m_strDataKey, ia);

      //}
      //catch(...)
      //{
      //   return;
      //}
      {
         /*         check_box * pcheck = dynamic_cast < check_box * > (pinteraction);
                  if(pcheck != nullptr)
                  {
                     ::collection::index i = 0;
                     if(ia.BaseSortFind(pinteraction->m_ddx.m_pdbflags->m_value, i))
                     {
                        pcheck->set_check(e_check_checked, false);
                     }
                     else
                     {
                        pcheck->set_check(e_check_unchecked, false);
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
      //int i;
      //if(datastream()->get(pinteraction->m_strDataKey, i))
      //{
      //   /* linux      ::user::button * pbutton = (::user::button *) get_child_by_id(pinteraction->id());
      //         pbutton->SetCheck((i != 0) ? 1 : 0); */
      //}
   }

   void form_window::_001UpdateComboBox(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if(pinteraction == nullptr)
         return;
      /* linux   ASSERT(pinteraction->get_control_type() == e_control_type_combo_box);
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

   void form_window::_001UpdateEdit(::user::interaction * pinteraction)
   {

      ASSERT(pinteraction != nullptr);
      
      if (pinteraction == nullptr)
      {

         return;

      }

      __task_guard(m_bOnEditUpdate);

      ASSERT(pinteraction->get_control_type() == e_control_type_edit
             || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      if(pinteraction->has_function(e_control_function_vms_data_edit))
      {
throw_todo();
//         ::payload payload;
//         ::database::selection selection;
//         get_selection(pinteraction->m_strDataKey, selection);
//         if(selection.get_item_count() > 0)
//         {
//
//            if(!pinteraction)
//            {
//
//               return;
//
//            }
//
//            //if(datastream()->get(pinteraction->m_strDataKey + item.m_strDataKey, payload))
//            //{
//
//            //   switch(payload.get_type())
//            //   {
//            //   case ::e_type_string:
//            //   {
//            //      string str;
//            //      str = payload.m_str;
//            //      pinteraction->set_text(str, ::e_source_database);
//            //   }
//            //   break;
//            //   case ::e_type_int:
//            //   {
//            //      string str;
//            //      str.formatf("%d", payload.as_int());
//            //      pinteraction->set_text(str, ::e_source_database);
//            //   }
//            //   break;
//            //   default:
//            //      ASSERT(false);
//            //      break;
//            //   }
//            //}
//         }
      }
   }

   void form_window::_001UpdateSimpleList(::user::interaction * pinteraction)
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

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::pointer<interaction>pinteraction = get_child_by_id(atom);

      if (!pinteraction)
      {

         return false;

      }

      //int i;

      //if(!datastream()->get(pinteraction->m_strDataKey, i))
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

      //int i = bData ? 1 : 0;
      //datastream()->set(pinteraction->m_strDataKey, i);
      return true;

   }

   void form_window::Update(bool bSave)
   {
      if(bSave)
      {

      }
      else
      {
         //for(int i = 0; i < m_controldescriptorset.get_size(); i++)
         //{
         //   ::pointer<control>pinteraction = m_controldescriptorset[i]->m_pcontrol;
         //   if(pinteraction == nullptr)
         //      continue;
         //   _001Update(pinteraction);
         //}
      }
   }



   void form_window::get_selection(const ::scoped_string & scopedstrDataKey, string_array_base & stra)
   {

      stra.add_item(scopedstrDataKey);

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

   //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   //m_controldescriptorset.erase_all();

   //}


   bool form_window::_001OnBeforeSave(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return true;

   }


   void form_window::data_on_after_change(::database::client* pclient, const ::scoped_string & strDataKey, const ::payload & payload, ::topic * ptopic)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if(ptopic != nullptr)
      {

         if(!ptopic->has_modified_flag())
         {

            return;

         }

      }

      //for(int iControl = 0; iControl < m_controldescriptorset.get_size(); iControl++)
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
      //   else if(pdescriptor->m_strDataKey == key)
      //   {

      //      _001Update(pinteraction);

      //   }

      //}

   }


   void form_window::_001UpdateFunctionStatic()
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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


   void form_window::WfiOnClose()
   {

      post_message(::user::e_message_close);

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

      KEEP(m_bOnLanguageChange);

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


   void form_window::_017OnAppLanguage()
   {

//      for(int i = 0; i < m_controldescriptorset.get_size() ; i++)
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
//   //            ASSERT(pinteraction->m_type->IsDerivedFrom(::type < window >()));
//               if(descriptor.m_pcontrol.is_set())
//               {
//                  //window_id wndidTemp = get_child_by_id(pinteraction->id())->GetSafeoswindow_();
//                  //if(wndidTemp != nullptr)
//                  {
//             //xxx        VERIFY(pinteraction->m_puserinteraction->subclass_window(wndidTemp));
//                  }
//               }
//            }
//            if(descriptor.m_pcontrol != nullptr)
//            {
////               ::type ti = typeid(descriptor.m_pcontrol);
///*               if(ti == ::type < ::user::list >())
//               {
//                  if(descriptor.m_etype == e_control_type_simple_list)
//                  {
//                     ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
//                     plist->m_dataid = descriptor.m_atomPrivateDataSection;
//                     plist->_001SetSingleColumnMode(false);
//                  }
//               }*/
//   /*            else if(pinteraction->m_type->IsDerivedFrom(::type < simple_still >()))
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

   //   //   informationf("form_window::create_interaction: failed to create control, could not find proper type for allocation");

   //   //   return false;

   //   //}

   //   //auto pinteraction = papp->øid_create <::user::interaction>(pdescriptor->m_type);

   //   //if(!pinteraction)
   //   //{

   //   //   informationf("form_window::create_interaction: failed to create control, allocation error");

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

   //if (ptopic->id() == ::id_form_initialize)
   //{

   //   call_sync(get_document()->m_mapRunnablea["load"]);

   //}


   //void form_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   ::user::form_control::handle(ptopic, phandlercontext);

   //   if (ptopic->m_bRet)
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
   //   else if(ptopic->id() == ::id_set_check && ptopic->m_actioncontext.is_user_source())
   //   {

   //      ::pointer<interaction>pinteraction = ptopic->user_interaction();

   //      if (!pinteraction)
   //      {

   //         return;

   //      }

   //      if(pinteraction->m_eddx == e_control_ddx_dbflags)
   //      {

   //         iptr_array ia;

   //         //pinteraction->datastream()->get(pdescriptor->m_strDataKey, ia);

   //         ::pointer<check>pcheck = ptopic->user_interaction();

   //         if(pcheck->echeck() == ::e_check_checked)
   //         {

   //            ia.add_unique(pinteraction->m_iDataValue);

   //         }
   //         else
   //         {

   //            ia.erase(pinteraction->m_iDataValue);

   //         }

   //         //pinteraction->datastream()->get(pdescriptor->m_strDataKey, ia);

   //      }

   //   }

   //}


   bool form_window::_001Initialize()
   {

      if(m_bInitialized)
         return true;

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _001InitializeFormPreData();

      _001UpdateFunctionStatic();

      for(auto pinteraction : proper_children())
      {

         _001Update(pinteraction);

      }

      m_bInitialized = true;

      return true;

   }


   bool form_window::_001IsPointInside(::user::interaction * pinteraction, const long_long_point & point)
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

   //   

   //   pdescriptor->m_type = user()->controltype_to_typeinfo(pdescriptor->get_control_type());

   //   if(pdescriptor->m_type)
   //   {

   //      return true;

   //   }

   //   return false;

   //}


   //void form_window::on_before_navigate(::payload & payloadFile, unsigned int nFlags, const ::scoped_string & scopedstrTargetFrameName, byte_array& baPostedData, const ::scoped_string & scopedstrHeaders, bool* pbCancel)

   //{

   //   __UNREFERENCED_PARAMETER(payloadFile);
   //   __UNREFERENCED_PARAMETER(nFlags);
   //   __UNREFERENCED_PARAMETER(scopedstrTargetFrameName);

   //   __UNREFERENCED_PARAMETER(baPostedData);
   //   __UNREFERENCED_PARAMETER(scopedstrHeaders);

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


   void form_window::control_get_window_rect(::user::interaction * pinteraction, ::int_rectangle & rectangle)
   {

      pinteraction->window_rectangle(rectangle);

   }


   void form_window::control_get_client_rect(::user::interaction * pinteraction, ::int_rectangle & rectangle)
   {

      rectangle = pinteraction->rectangle();

   }


   void form_window::install_message_routing(::channel * pchannel)
   {
      ::user::form_control::install_message_routing(pchannel);
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &form_window::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_after_create, pchannel, this, &form_window::_000OnPosCreate);
      USER_MESSAGE_LINK(::user::e_message_language, pchannel, this, &form_window::_001OnAppLanguage);
      //USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
      //USER_MESSAGE_LINK(::user::e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

   }


} // namespace user



