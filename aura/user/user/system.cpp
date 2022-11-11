//
//  user_create_struct.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 19/06/18.
//
#include "framework.h"
#include "system.h"
#include "interaction.h"
#include "acme/constant/id.h"
#include "aura/platform/application.h"


namespace user
{


   system::system(const system & system)
   {

      create_common_construct();

//#ifdef WINDOWS
//      //m_createstruct = system.m_createstruct;
//      //set_class_name(string(system.m_createstruct.lpszClass));
//      //set_window_name(string(system.m_createstruct.lpszName));
//#else
//      //m_createstruct = system.m_createstruct;
//      //set_class_name(system.m_createstruct.lpszClass);
//      //set_window_name(system.m_createstruct.lpszName);
//#endif
      m_procedureFailure = system.m_procedureFailure;
      m_procedureSuccess = system.m_procedureSuccess;
      //m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (::user::system *) this;
   }


   //system::system(u32 uiExStyle, const ::string & pszClassName, const ::string & pszWindowName, u32 uStyle, ::rectangle_i32 rectangle, ::create * pcreate) :
   //system(rectangle)
   //{

   //   m_createstruct.dwExStyle = uiExStyle;
   //   set_class_name(pszClassName);
   //   set_window_name(pszWindowName);
   //   m_createstruct.style = uStyle;
   //   m_pcreate = pcreate;
   //   m_puserinteractionOwner = nullptr;

   //}


   //system::system(const ::rectangle_i32 & rectangle, ::u32 uExStyle, ::u32 uStyle, ::create * pcreate)
   //system::system(const ::rectangle_i32& rectangle, ::create* pcreate)
   system::system(::create* pcreate)
   {

      //__zero(m_createstruct);

      create_common_construct();
         
      //set_rect(rectangle);

      //m_createstruct.dwExStyle = uExStyle;

      //m_createstruct.style = uStyle;

      //m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (::user::system *)this;

   }


   void system::create_common_construct()
   {

      //m_bAutoWindowFrame = true;
      //m_bWindowFrame = false;

   }


   //void system::set_class_name(const ::string & pszClassName)
   //{

   //   m_strClassName = pszClassName;

   //   m_createstruct.lpszClass = m_strClassName;

   //}


   //void system::set_window_name(const ::string & pszWindowName)
   //{

   //   m_strWindowName = pszWindowName;

   //   m_createstruct.lpszName = m_strWindowName;

   //}


   //void system::set_rect(const ::rectangle_i32 & rectangle)
   //{

   //   m_createstruct.x = rectangle.left;
   //   m_createstruct.y = rectangle.top;
   //   m_createstruct.cx = rectangle.width();
   //   m_createstruct.cy = rectangle.height();

   //}

   void system::add_visible(bool bAdd)
   {

      if (!bAdd)
      {

         return;

      }

      //if (!(m_createstruct.style & WS_VISIBLE))
      //{

      //   m_createstruct.style |= WS_VISIBLE;

      //}

   }


   ::pointer<::user::interaction>system::create_impact(::user::interaction * puserinteractionParent, const ::atom & atom)
   {

      ASSERT(m_typeNewImpact || m_puserprimitiveNew != nullptr);

      auto papp = puserinteractionParent->get_app();

      ::pointer<::user::interaction>pinteraction;

      //::e_status estatus = ::success;

      if (m_puserprimitiveNew != nullptr)
      {

         pinteraction = m_puserprimitiveNew;

      }
      else
      {

         ::pointer<::object>pparticle = m_pdocumentCurrent;

         if(pparticle.is_null())
         {

            pparticle = papp;

         }

         if (pparticle.is_null() || ::is_null(pparticle->get_app()))
         {

            _ERROR(pparticle, "Cannot create impact. Document doesn't have context application. (Should it be a blocking thing...)");

            return nullptr;

         }

         auto pcontextJustForInspection = pparticle->m_pcontext;

         string strType = typeid(*pcontextJustForInspection).name();

         //estatus =
         pparticle->__id_construct(pinteraction, m_typeNewImpact);

      }

      if (pinteraction.is_null())
      {

         return nullptr;

      }

      pinteraction->m_pusersystem = this;

      pinteraction->display(e_display_restored);

      pinteraction->m_atom = atom;

      //if (!pinteraction->create_interaction(nullptr, nullptr, WS_VISIBLE | WS_CHILD, puserinteractionParent, atom, pcreate))
      //if (!pinteraction->create_child(puserinteractionParent))

      pinteraction->create_child(puserinteractionParent);
      //{

      //   return nullptr;

      //}


      pinteraction->signal(id_initial_update);
      

//      ::pointer<::user::impact>pimpact = pinteraction;
//
//      if (pimpact.is_set())
//      {
//
//         auto pdocument = pimpact->get_document();
//
//         pdocument->signal(id_initial_update);
//
//      }

      //if (pinteraction.is_set())
      //{

      //   if (pinteraction->get_parent() != nullptr)
      //   {

      //      if (pinteraction->get_parent()->is_place_holder())
      //      {

      //         pinteraction->get_parent()->place_hold(pinteraction);

      //      }

      //   }

      //}

      return pinteraction;

   }


   //void system::get_rect(RECTANGLE_I32 * lprect)
   //{

   //   lprect->left = m_createstruct.x;
   //   lprect->top = m_createstruct.y;
   //   lprect->right = m_createstruct.x + m_createstruct.cx;
   //   lprect->bottom = m_createstruct.y + m_createstruct.cy;

   //}


} // namespace user



