#pragma once


#include "interaction.h"


namespace user
{


   class CLASS_DECL_AURA interaction_ptra:
      public address_array < ::user::interaction * >
   {
   public:

      
      //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(interaction_ptra, ref_array < ::user::interaction >)

      
      //interaction_ptra(const interaction_array & a);


      interaction_ptra & operator = (const interaction_array & a);

      
      
      using address_array < ::user::interaction * >::find_first;
      ::user::interaction * find_first_typed(const ::type_atom & typeatom);
      ::user::interaction * find_first(oswindow oswindow);

      
      virtual bool get_child(::pointer<::user::interaction>& pinteraction);
      virtual bool rget_child(::pointer<::user::interaction>& pinteraction);


   };



   //class CLASS_DECL_AURA interaction_pointer_array :
   //   virtual public matter
   //{
   //public:


   //   DECLARE_ARRAY_OF(interaction_pointer_array, interaction, ::user::interaction);


   //   interaction_pointer_array();
   //   interaction_pointer_array(const address_array < ::user::interaction * > & a);
   //   interaction_pointer_array(const pointer_array < ::user::interaction > & a)
   //   {

   //      m_interactiona.copy(a);

   //   }
   //   interaction_pointer_array(const ::user::interaction_pointer_array & a)
   //   {

   //      m_interactiona.copy(a.m_interactiona);

   //   }


   //   ::user::interaction * find_first_typed(const ::type_atom & typeatom);
   //   ::user::interaction * find_first(oswindow oswindow);


   //   virtual bool get_child(::pointer<::user::interaction>& pinteraction);
   //   virtual bool rget_child(::pointer<::user::interaction>& pinteraction);


   //};


   class CLASS_DECL_AURA interaction_array :
      virtual public matter
   {
   public:


      DECLARE_ARRAY_OF(interaction_array, interaction, ::user::interaction);


      interaction_array();
      interaction_array(const address_array < ::user::interaction * > & a);
      interaction_array(const pointer_array < ::user::interaction > & a) :
         m_interactiona(a) {}

      template < typename OTHER >
      interaction_array(const pointer_array < OTHER > & a) :
         m_interactiona(a) {}

      interaction_array(const ::user::interaction_array & a)
      {

         m_interactiona.copy(a.m_interactiona);

      }

#ifdef MOVE_SEMANTICS

      interaction_array(const ::user::interaction_array && a)
      {

         m_interactiona.copy(a.m_interactiona);

      }

#endif
      
      
#ifdef _DEBUG
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
#endif

      //using pointer_array < ::user::interaction >::find_first;
      ::pointer<::user::interaction>find_first_typed(const ::std::type_info & info);
      ::pointer<::user::interaction>find_first(oswindow oswindow);

      //::user::oswindow_array get_hwnda();
      void send_message(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {});

      void send_message_to_descendants(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {}, bool bRecursive = true);


      interaction_array & operator = (const pointer_array < ::user::interaction > & a);
      interaction_array & operator = (const interaction_array & a);

      virtual bool get_child(::pointer<::user::interaction>& pinteraction);
      virtual bool rget_child(::pointer<::user::interaction>& pinteraction);


      template < typename TYPE >
      TYPE * typed_descendant(::user::interaction * puiExclude)
      {

         for (auto & pinteraction : this->interactiona())
         {

            if (pinteraction != puiExclude)
            {

               TYPE * p = dynamic_cast <TYPE *> (pinteraction.m_p);

               if (p != nullptr)
               {

                  return p;

               }

            }

         }

         for (auto & pinteraction : this->interactiona())
         {

            if (pinteraction != puiExclude)
            {

               TYPE * p = pinteraction->typed_descendant < TYPE >(pinteraction.m_p);

               if (p != nullptr)
               {

                  return p;

               }

            }

         }

         return nullptr;

      }


      //template < typename CHILD >
      //inline bool interaction::get_typed_child(CHILD *& pchild)
      //{

      //   auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      //   if (!puserinteractionpointeraChild)
      //   {

      //      return false;

      //   }

      //   return puserinteractionpointeraChild->get_typed_child(pchild);

      //}

      //template < typename CHILD >
      //bool get_typed_child(CHILD * & pchild);

      template < typename CHILD >
      inline bool get_typed_child(CHILD *& pchild)
      {

         for (int i = 0; i < this->interaction_count(); i++)
         {

            pchild = this->interaction_at(i).cast < CHILD >();

            if (pchild)
            {

               return true;

            }

         }

         for (int i = 0; i < this->interaction_count(); i++)
         {

            if (this->interaction_at(i)->get_typed_child(pchild))
            {

               return true;

            }

         }

         return false;

      }


      template < typename CHILD >
      ::pointer<CHILD>get_typed_child()
      {

         ::pointer<CHILD>pchild;

         if (!get_typed_child(pchild))
         {

            return nullptr;

         }

         return pchild;

      }

   };


} // namespace user



