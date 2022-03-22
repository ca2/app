#pragma once


namespace user
{


   class interaction_array;


   class CLASS_DECL_AURA interaction_ptra:
      public address_array < ::user::interaction * >
   {
   public:

      
      //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(interaction_ptra, ref_array < ::user::interaction >)

      
      //interaction_ptra(const interaction_array & a);


      interaction_ptra & operator = (const interaction_array & a);

      
      
      using address_array < ::user::interaction * >::find_first;
      ::user::interaction * find_first_typed(const ::type & type);
      ::user::interaction * find_first(oswindow oswindow);

      
      virtual bool get_child(__pointer(::user::interaction ) & pinteraction);
      virtual bool rget_child(__pointer(::user::interaction) & pinteraction);


   };



   class CLASS_DECL_AURA primitive_pointer_array :
      virtual public matter
   {
   public:


      DECLARE_ARRAY_OF(primitive_pointer_array, primitive, ::user::primitive);


      primitive_pointer_array();
      primitive_pointer_array(const address_array < ::user::primitive * > & a);
      primitive_pointer_array(const __pointer_array(::user::primitive) & a)
      {

         m_primitivea.copy(a);

      }
      primitive_pointer_array(const ::user::primitive_pointer_array & a)
      {

         m_primitivea.copy(a.m_primitivea);

      }


      ::user::primitive * find_first_typed(const ::type & type);
      ::user::primitive * find_first(oswindow oswindow);


      virtual bool get_child(__pointer(::user::primitive) & pprimitive);
      virtual bool rget_child(__pointer(::user::primitive) & pprimitive);


   };


   class CLASS_DECL_AURA interaction_array :
      virtual public matter
   {
   public:


      DECLARE_ARRAY_OF(interaction_array, interaction, ::user::interaction);


      interaction_array();
      interaction_array(const address_array < ::user::interaction * > & a);
      interaction_array(const __pointer_array(::user::interaction) & a) :
      m_interactiona(a) {}

      template < typename OTHER >
      interaction_array(const __pointer_array(OTHER) & a) :
      m_interactiona(a) {}

      interaction_array(const ::user::interaction_array & a)
      {

         m_interactiona.copy(a.m_interactiona);

      }

#ifdef MOVE_SEMANTICS

      interaction_array(const ::user::interaction_array&& a)
      {

         m_interactiona.copy(a.m_interactiona);

      }

#endif


      //using __pointer_array(::user::interaction)::find_first;
      __pointer(::user::interaction) find_first_typed(const ::std::type_info & info);
      __pointer(::user::interaction) find_first(oswindow oswindow);

      //::user::oswindow_array get_hwnda();
      void send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0);

      void send_message_to_descendants(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, bool bRecursive = true);


      interaction_array & operator = (const __pointer_array(::user::interaction) & a);
      interaction_array & operator = (const interaction_array & a);

      virtual bool get_child(__pointer(::user::interaction) & pinteraction);
      virtual bool rget_child(__pointer(::user::interaction) & pinteraction);


      template < typename CHILD >
      bool get_typed_child(CHILD * & pchild);

      template < typename CHILD >
      __pointer(CHILD) get_typed_child()
      {

         __pointer(CHILD) pchild;

         if (!get_typed_child(pchild))
         {

            return nullptr;

         }

         return pchild;

      }

   };


} // namespace user



