#pragma once


namespace user
{


   inline bool interaction::has_prodevian() const noexcept { return m_pimpl2 ? m_pimpl2->has_prodevian() : false; }

   
   template < class T >
   __pointer(T) primitive::GetTypedParent() const
   {
      
      ASSERT_VALID(this);
      
      __pointer(T) point;
      
      ::user::interaction * puiParent = GetParent();  // start with one parent up
      
      while (puiParent != nullptr)
      {
         
         point = puiParent;
         
         if (point.is_set())
         {
            
            return point;
            
         }
         
         puiParent = puiParent->GetParent();
    
      }
      
      return nullptr;
      
   }

   template < typename CHILD >
   inline bool interaction::get_typed_child(CHILD*& pchild)
   {

      auto puiptraChild = m_puiptraChild;

      if (!puiptraChild)
      {

         return false;

      }

      return puiptraChild->get_typed_child(pchild);

   }

   template < typename CHILD >
   inline __pointer(CHILD) interaction::get_typed_child()
   {

      auto puiptraChild = m_puiptraChild;

      if (!puiptraChild)
      {

         return nullptr;

      }

      return puiptraChild->get_typed_child < CHILD >();

   }


   template < typename CHILD >
   inline bool interaction_array::get_typed_child(CHILD*& pchild)
   {

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         pchild = this->interaction_at(i).cast < CHILD >();

         if (pchild)
         {

            return true;

         }

      }

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         if (this->interaction_at(i)->get_typed_child(pchild))
         {

            return true;

         }

      }

      return false;

   }


   inline bool interaction::is_this_visible(e_layout elayout) const
   {

      return layout().is_this_visible(elayout);

   }


   inline bool interaction::is_this_screen_visible(e_layout elayout) const
   {

      return layout().is_this_screen_visible(elayout);

   }

   inline bool interaction::is_window_visible(e_layout elayout) const
   {

      if (!m_pdescriptor)
      {

         return false;

      }

      return m_pdescriptor->m_puserinteractionParent && !m_pdescriptor->m_puserinteractionParent->is_window_visible(elayout) ? false : layout().state(elayout).is_visible();

   }


   inline bool interaction::is_window_screen_visible(e_layout elayout) const
   {

      if (::is_null(m_pdescriptor))
      {

         return false;

      }

      return m_pdescriptor->m_puserinteractionParent && !m_pdescriptor->m_puserinteractionParent->is_window_screen_visible(elayout) ? false : is_screen_visible(layout().state(elayout).display());

   }


} // namespace user


inline prodevian::prodevian(::user::interaction* pinteraction) :
   m_pinteraction(pinteraction)
{

   m_pinteraction->add_prodevian(this);

}




//namespace user
//{
//
//
//   template < class VIEW >
//   inline __pointer(VIEW) split_view::create_pane_view(index iPane, id id, ::user::interaction* pviewLast)
//   {
//
//      return create_view < VIEW >(get_pane_holder(iPane), id, pviewLast);
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
//   inline __pointer(VIEW) impact::create_view(::user::document* pdocument, ::user::interaction* pwndParent, id id, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
//   {
//
//      return create_view(__type(VIEW), pdocument, pwndParent, id, pviewLast, pimpactdata);
//
//   }
//
//
//   template < class VIEW >
//   inline __pointer(VIEW) impact::create_view(::user::interaction* pwndParent, id id, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
//   {
//
//      return create_view < VIEW >(get_document(), pwndParent, id, pviewLast, pimpactdata);
//
//   }
//
//
//   template < class VIEW >
//   inline __pointer(VIEW) impact::create_view(::user::impact_data* pimpactdata, ::user::interaction* pviewLast)
//   {
//
//      return create_view < VIEW >(get_document(), pimpactdata->m_pplaceholder, pimpactdata->m_id, pviewLast, pimpactdata);
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






//inline bool thread::has_property(const ::id& id) const { return command() && has_property(id); }
//inline var thread::command_value(const ::id& id) const { return has_property(id) ? (const var&)&command()->m_varQuery[id] : (const var&)type_new; }
//inline bool thread::command_value_is_true(const ::id& id) const { return has_property(id) ? command()->m_varQuery.is_true(id) : false; }





//namespace draw2d
//{
//
//
//   inline bool graphics::set_font(::user::interaction* pinteraction, ::user::e_element eelement, ::user::estate estate)
//   {
//
//      return set(pinteraction->get_font(pinteraction->get_style(m_puserstyle), eelement, estate));
//
//   }
//
//
//} // namespace draw2d



