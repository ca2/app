#pragma once

//
//namespace user
//{
//
//
//   template < class VIEW >
//   inline ::pointer<VIEW>split_impact::create_pane_impact(::collection::index iPane, atom atom, ::user::interaction* pviewLast)
//   {
//
//      return create_impact < VIEW >(get_pane_holder(iPane), atom, pviewLast);
//
//   }
//
//
//} // namespace user
//




//
//namespace user
//{
//
//
//
//
//
//   template < class DATA >
//   DATA* impact::get_typed_data()
//   {
//
//      ASSERT(::is_set(this));
//
//      return m_pdocument->get_typed_data < DATA >();
//
//   }
//
//
//   template < class DOCUMENT >
//   ::data::data* impact::get_typed_document_data()
//   {
//
//      ASSERT(::is_set(this));
//
//      return m_pdocument->get_typed_document_data < DOCUMENT >();
//
//   }
//
//
//   template < class DOCUMENT >
//   DOCUMENT* impact::get_typed_document()
//   {
//
//      ASSERT(::is_set(this));
//
//      return m_pdocument->get_typed_document < DOCUMENT >();
//
//   }
//
//
//} // namespace user
//


namespace user
{


   template < class TOOLBAR >
      void frame_window::load_toolbar(const ::atom & idToolbar, const ::string & strToolbar, u32 dwCtrlStyle, u32 uStyle)
      {

         return load_toolbar(::type < TOOLBAR >(), idToolbar, strToolbar, dwCtrlStyle, uStyle);

      }


} // namespace user





