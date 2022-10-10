#pragma once


namespace user
{



   
   //template < typename CHILD >
   //inline bool interaction::get_typed_child(CHILD*& pchild)
   //{

   //   auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //   if (!puserinteractionpointeraChild)
   //   {

   //      return false;

   //   }

   //   return puserinteractionpointeraChild->get_typed_child(pchild);

   //}

   //template < typename CHILD >
   //inline ::pointer<CHILD>interaction::get_typed_child()
   //{

   //   auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //   if (!puserinteractionpointeraChild)
   //   {

   //      return nullptr;

   //   }

   //   return puserinteractionpointeraChild->get_typed_child < CHILD >();

   //}


   //template < typename CHILD >
   //inline bool interaction_array::get_typed_child(CHILD*& pchild)
   //{

   //   for (i32 i = 0; i < this->interaction_count(); i++)
   //   {

   //      pchild = this->interaction_at(i).cast < CHILD >();

   //      if (pchild)
   //      {

   //         return true;

   //      }

   //   }

   //   for (i32 i = 0; i < this->interaction_count(); i++)
   //   {

   //      if (this->interaction_at(i)->get_typed_child(pchild))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


} // namespace user






//namespace user
//{
//
//
//   template < class VIEW >
//   inline ::pointer<VIEW>split_impact::create_pane_impact(index iPane, atom atom, ::user::interaction* pviewLast)
//   {
//
//      return create_impact < VIEW >(get_pane_holder(iPane), atom, pviewLast);
//
//   }
//
//
//} // namespace user






//namespace user
//{
//
//
//
//
//   template < class VIEW >
//   inline ::pointer<VIEW>impact::create_impact(::user::document* pdocument, ::user::interaction* puserinteractionParent, atom atom, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
//   {
//
//      return create_impact(__type(VIEW), pdocument, puserinteractionParent, atom, pviewLast, pimpactdata);
//
//   }
//
//
//   template < class VIEW >
//   inline ::pointer<VIEW>impact::create_impact(::user::interaction* puserinteractionParent, atom atom, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
//   {
//
//      return create_impact < VIEW >(get_document(), puserinteractionParent, atom, pviewLast, pimpactdata);
//
//   }
//
//
//   template < class VIEW >
//   inline ::pointer<VIEW>impact::create_impact(::user::impact_data* pimpactdata, ::user::interaction* pviewLast)
//   {
//
//      return create_impact < VIEW >(get_document(), pimpactdata->m_pplaceholder, pimpactdata->m_atom, pviewLast, pimpactdata);
//
//   }
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
//} //   namespace aura






//inline bool thread::has_property(const ::atom& atom) const { return command() && has_property(atom); }
//inline ::payload thread::command_value(const ::atom& atom) const { return has_property(atom) ? (const ::payload&)&command()->payload(atom) : (const ::payload&)e_type_new; }
//inline bool thread::command_value_is_true(const ::atom& atom) const { return has_property(atom) ? command()->m_varQuery.is_true(atom) : false; }





//namespace draw2d
//{
//
//
//   inline bool graphics::set_font(::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate)
//   {
//
//      return set(pinteraction->get_font(pinteraction->get_style(m_puserstyle), eelement, estate));
//
//   }
//
//
//} // namespace draw2d


namespace user
{








} // namespace user



