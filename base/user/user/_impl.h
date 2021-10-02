#pragma once


namespace user
{


   template < class VIEW >
   inline __pointer(VIEW) split_view::create_pane_view(index iPane, id id, ::user::interaction* pviewLast)
   {

      return create_view < VIEW >(get_pane_holder(iPane), id, pviewLast);

   }


} // namespace user






namespace user
{




   template < class VIEW >
   inline __pointer(VIEW) impact::create_view(::user::document* pdocument, ::user::interaction* puserinteractionParent, const ::id & id, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
   {

      return create_view(__type(VIEW), pdocument, puserinteractionParent, id, pviewLast, pimpactdata);

   }


   template < class VIEW >
   inline __pointer(VIEW) impact::create_view(::user::interaction* puserinteractionParent, const ::id & id, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
   {

      return create_view < VIEW >(get_document(), puserinteractionParent, id, pviewLast, pimpactdata);

   }


   template < class VIEW >
   inline __pointer(VIEW) impact::create_view(::user::impact_data* pimpactdata, ::user::interaction* pviewLast)
   {

      return create_view < VIEW >(get_document(), pimpactdata->m_pplaceholder, pimpactdata->m_id, pviewLast, pimpactdata);

   }


   template < class DATA >
   DATA* impact::get_typed_data()
   {

      ASSERT(::is_set(this));

      return m_pdocument->get_typed_data < DATA >();

   }


   template < class DOCUMENT >
   ::data::data* impact::get_typed_document_data()
   {

      ASSERT(::is_set(this));

      return m_pdocument->get_typed_document_data < DOCUMENT >();

   }


   template < class DOCUMENT >
   DOCUMENT* impact::get_typed_document()
   {

      ASSERT(::is_set(this));

      return m_pdocument->get_typed_document < DOCUMENT >();

   }


   inline ::base::session* menu_interaction::get_session() const
   {

      return m_pcontext ? m_pcontext->m_pbasesession : nullptr;

   }


   inline ::base::application* form_control::get_application() const
   {
      
      return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr;
   
   }


   inline ::base::session* form_control::get_session() const
   { 
      
      return m_pcontext ? m_pcontext->m_pbasesession : nullptr; 
   
   }


} // namespace user



namespace user
{


   template < class TOOLBAR >
      ::e_status frame_window::load_toolbar(const ::id & idToolbar, const ::string & strToolbar, u32 dwCtrlStyle, u32 uStyle)
      {

         return load_toolbar(__type(TOOLBAR), idToolbar, strToolbar, dwCtrlStyle, uStyle);

      }


} // namespace user





