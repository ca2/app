//
//  user_create_struct.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 19/06/18.
//
#include "framework.h"
#include "system.h"
#include "interaction.h"
#include "acme/constant/id.h"
#include "acme/graphics/graphics/output_purpose.h"
#include "acme/platform/scoped_restore.h"
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


   //system::system(unsigned int uiExStyle, const ::scoped_string & scopedstrClassName, const ::scoped_string & scopedstrWindowName, unsigned int uStyle, ::int_rectangle rectangle, ::request * prequest) :
   //system(rectangle)
   //{

   //   m_createstruct.dwExStyle = uiExStyle;
   //   set_class_name(scopedstrClassName);
   //   set_window_name(scopedstrWindowName);
   //   m_createstruct.style = uStyle;
   //   m_pcreate = pcreate;
   //   m_puserinteractionOwner = nullptr;

   //}


   //system::system(const ::int_rectangle & rectangle, unsigned int uExStyle, unsigned int uStyle, ::request * prequest)
   //system::system(const ::int_rectangle& rectangle, ::create* pcreate)
   system::system(::request * prequest)
   {

      //zero(m_createstruct);

      create_common_construct();

      //set_rect(rectangle);

      //m_createstruct.dwExStyle = uExStyle;

      //m_createstruct.style = uStyle;

      //m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (::user::system *)this;

   }


   void system::create_common_construct()
   {


   }


   void system::destroy()
   {

      ::property_object::destroy();

      m_puserprimitiveOwner.release();
      m_procedureSuccess.m_pbase.release();
      m_procedureFailure.m_pbase.release();
      //m_pwindow.release();
      m_prequest.release();
      m_pwindow.release();

      m_pdocumentCurrent.release();
      m_puserprimitiveNew.release();

      m_ptemplateNewDocument.release();

      m_puserprimitiveLastImpact.release();
      m_puserprimitiveCurrentFrame.release();
      m_pimpactdata.release();
      m_graphicsoutputpurposea.clear();

   }


   void system::add(::graphics::output_purpose * pgraphicsoutputpurpose)
   {

      if(::is_null(pgraphicsoutputpurpose))
      {

         return;

      }

      if(pgraphicsoutputpurpose->m_egraphicsoutputpurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      m_graphicsoutputpurposea.add(pgraphicsoutputpurpose);

   }


   //void system::set_class_name(const ::scoped_string & scopedstrClassName)
   //{

   //   m_strClassName = pszClassName;

   //   m_createstruct.lpszClass = m_strClassName;

   //}


   //void system::set_window_name(const ::scoped_string & scopedstrWindowName)
   //{

   //   m_strWindowName = pszWindowName;

   //   m_createstruct.lpszName = m_strWindowName;

   //}


   //void system::set_rect(const ::int_rectangle & rectangle)
   //{

   //   m_createstruct.x() = rectangle.left();
   //   m_createstruct.y() = rectangle.top();
   //   m_createstruct.cx() = rectangle.width();
   //   m_createstruct.cy() = rectangle.height();

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

      ASSERT(m_typeatomNewImpact || m_puserprimitiveNew != nullptr);

      auto papp = puserinteractionParent->get_app();

      ::pointer<::user::interaction>pinteraction;

      __check_refdbg

      //::e_status estatus = ::success;

      if (m_puserprimitiveNew != nullptr)
      {

         pinteraction = m_puserprimitiveNew;

      }
      else
      {

         ::pointer<::object>pparticle = m_pdocumentCurrent;

         if (pparticle.is_null())
         {

            pparticle = papp;

         }

         __check_refdbg

         if (pparticle.is_null() || ::is_null(pparticle->get_app()))
         {

            pparticle->error() << "Cannot create impact. Document doesn't have context application. (Should it be a blocking thing...)";

            return nullptr;

         }

         auto pcontextJustForInspection = pparticle->m_papplication;

         string strType = typeid(*pcontextJustForInspection).name();


         __check_refdbg

         //estatus =
         pparticle->__id_construct(pinteraction, m_typeatomNewImpact);

         __check_refdbg

      }

      if (pinteraction.is_null())
      {

         return nullptr;

      }

      {

         at_end_of_scope
         {

            pinteraction->m_bLockGraphicalUpdate = false;

         };

         pinteraction->m_bLockGraphicalUpdate = true;

         pinteraction->m_pusersystem = this;

         pinteraction->id() = atom;

         //if (!pinteraction->create_interaction(nullptr, nullptr, WS_VISIBLE | WS_CHILD, puserinteractionParent, atom, pcreate))
         //if (!pinteraction->create_child(puserinteractionParent))

         __check_refdbg

         pinteraction->create_child(puserinteractionParent);
         //{

         //   return nullptr;

         //}

         __check_refdbg

         pinteraction->on_topic(id_initial_update);

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

         __check_refdbg

         pinteraction->display(e_display_normal);

         pinteraction->set_need_layout();

         pinteraction->set_need_redraw();

         __check_refdbg

      }

      pinteraction->post_redraw();

      return pinteraction;

   }


   //void system::get_rect(::int_rectangle * lprect)
   //{

   //   lprect->left() = m_createstruct.x();
   //   lprect->top() = m_createstruct.y();
   //   lprect->right() = m_createstruct.x() + m_createstruct.cx();
   //   lprect->bottom() = m_createstruct.y() + m_createstruct.cy();

   //}


} // namespace user



