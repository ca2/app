#pragma once


namespace user
{


   inline bool interaction::has_prodevian() const noexcept { return m_pinteractionimpl ? m_pinteractionimpl->has_prodevian() : false; }

   
   template < class T >
   __pointer(T) primitive::GetTypedParent() const
   {
      
      ASSERT_VALID(this);
      
      __pointer(T) p;
      
      ::user::interaction * puiParent = get_parent();  // start with one parent up
      
      while (puiParent != nullptr)
      {
         
         p = puiParent;
         
         if (p.is_set())
         {
            
            return p;
            
         }
         
         puiParent = puiParent->get_parent();
    
      }
      
      return nullptr;
      
   }

   template < typename CHILD >
   inline bool interaction::get_typed_child(CHILD*& pchild)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      return puserinteractionpointeraChild->get_typed_child(pchild);

   }

   template < typename CHILD >
   inline __pointer(CHILD) interaction::get_typed_child()
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return nullptr;

      }

      return puserinteractionpointeraChild->get_typed_child < CHILD >();

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


   inline bool interaction::is_this_visible(enum_layout elayout) const
   {

      return layout().is_this_visible(elayout);

   }


   inline bool interaction::is_this_screen_visible(enum_layout elayout) const
   {

      return layout().is_this_screen_visible(elayout);

   }


   inline bool interaction::is_window_visible(enum_layout elayout) const
   {

      return m_puserinteractionParent && !m_puserinteractionParent->is_window_visible(elayout) ? false : layout().state(elayout).is_visible();

   }


   inline bool interaction::is_window_screen_visible(enum_layout elayout) const
   {

      return m_puserinteractionParent && !m_puserinteractionParent->is_window_screen_visible(elayout) ? false : is_screen_visible(layout().state(elayout).display());

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
//   inline __pointer(VIEW) split_view::create_pane_view(index iPane, atom atom, ::user::interaction* pviewLast)
//   {
//
//      return create_view < VIEW >(get_pane_holder(iPane), atom, pviewLast);
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
//   inline __pointer(VIEW) impact::create_view(::user::document* pdocument, ::user::interaction* puserinteractionParent, atom atom, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
//   {
//
//      return create_view(__type(VIEW), pdocument, puserinteractionParent, atom, pviewLast, pimpactdata);
//
//   }
//
//
//   template < class VIEW >
//   inline __pointer(VIEW) impact::create_view(::user::interaction* puserinteractionParent, atom atom, ::user::interaction* pviewLast, ::user::impact_data* pimpactdata)
//   {
//
//      return create_view < VIEW >(get_document(), puserinteractionParent, atom, pviewLast, pimpactdata);
//
//   }
//
//
//   template < class VIEW >
//   inline __pointer(VIEW) impact::create_view(::user::impact_data* pimpactdata, ::user::interaction* pviewLast)
//   {
//
//      return create_view < VIEW >(get_document(), pimpactdata->m_pplaceholder, pimpactdata->m_atom, pviewLast, pimpactdata);
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


   inline ::user::interaction_impl * message::userinteractionimpl()
   {

      auto pwindow = window();

      return pwindow ? pwindow->m_puserinteractionimpl : nullptr;

   }


   inline ::user::interaction * message::userinteraction()
   {

      auto pimpl = userinteractionimpl();

      return pimpl ? pimpl->m_puserinteraction : nullptr;

   }


   inline ::aura::application* interaction::get_app() const
   {

      return m_pcontext && m_pcontext->m_papplication ? m_pcontext->m_papplication->m_pauraapplication : nullptr;

   }


   inline ::aura::session* interaction::get_session() const
   {

      return m_pcontext ? m_pcontext->m_paurasession : nullptr;

   }


   inline ::aura::system* interaction::get_system() const
   {

      return m_psystem ? m_psystem->m_paurasystem : nullptr;

   }

   
   inline ::aura::application* user::get_app()
   {

      return m_pcontext && m_pcontext->m_papplication ? m_pcontext->m_papplication->m_pauraapplication : nullptr;

   }


   inline ::aura::session* user::get_session()
   {

      return m_pcontext ? m_pcontext->m_paurasession : nullptr;

   }


   inline ::aura::system* user::get_system()
   {

      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;

   }


   inline ::aura::application* primitive_impl::get_app() const
   {

      return m_pcontext ? m_pcontext->m_pauraapplication : nullptr;

   }


   inline ::aura::session* primitive_impl::get_session() const
   {

      return m_pcontext ? m_pcontext->m_paurasession : nullptr;

   }


   inline ::aura::system* primitive_impl::get_system() const
   {

      return m_psystem ? m_psystem->m_paurasystem : nullptr;

   }


   inline ::aura::application* form::get_app() const
   {
      
      return m_pcontext ? m_pcontext->m_pauraapplication : nullptr; 
   
   }


   inline ::aura::session* form::get_session() const 
   {
      
      return m_pcontext ? m_pcontext->m_paurasession : nullptr; 
   
   }


   inline double interaction::screen_scaler() const
   {

      return m_pinteractionScaler->screen_scaler();

   }


   inline double interaction::font_scaler() const
   {

      return m_pinteractionScaler->font_scaler();

   }


} // namespace user



