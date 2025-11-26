#include "framework.h"
#include "interaction_array.h"
#include "interaction.h"


namespace user
{


   interaction_ptra & interaction_ptra::operator=(const interaction_array & a)
   {

      for (::collection::index i = 0; i < a.interaction_count(); i++)
      {

         add(a.get_interaction(i));

      }

      return *this;

   }





   ::user::interaction * interaction_ptra::find_first_typed(const ::type & type)
   {

      for (int i = 0; i < this->get_size(); i++)
      {

         ::user::interaction * pinteraction = this->element_at(i);

         if (type == pinteraction)
         {

            return pinteraction;

         }

      }

      return nullptr;

   }


   ::user::interaction * interaction_ptra::find_first(oswindow oswindow)
   {

      for (int i = 0; i < this->get_size(); i++)
      {

         if (this->element_at(i)->get_safe_oswindow() == oswindow)
         {

            return this->element_at(i);

         }

      }

      return nullptr;

   }


   bool interaction_ptra::get_child(::pointer<::user::interaction>& pinteraction)
   {

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (get_count() <= 0)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = element_at(0);

         return true;

      }
      else
      {

         for (::collection::index i = get_upper_bound(); i >= 0; i--)
         {

            if (element_at(i) == pinteraction)
            {

               i++;

               if (i < get_count())
               {

                  pinteraction = element_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }

   bool interaction_ptra::rget_child(::pointer<::user::interaction>& pinteraction)
   {

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (get_count() <= 0)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = last();

         return true;

      }
      else
      {

         for (::collection::index i = 0; i < get_size(); i++)
         {

            if (element_at(i) == pinteraction)
            {

               i--;

               if (i >= 0)
               {

                  pinteraction = element_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }

   
   //interaction_pointer_array::interaction_pointer_array()
   //{


   //}


   //::user::interaction * interaction_pointer_array::find_first_typed(const ::type & type)
   //{

   //   for (int i = 0; i < interaction_count(); i++)
   //   {

   //      auto pprimitive = interaction_at(i).m_p;

   //      if (type == pprimitive)
   //      {

   //         return pprimitive;

   //      }

   //   }

   //   return nullptr;

   //}


   //::user::interaction * interaction_pointer_array::find_first(oswindow oswindow)
   //{

   //   for (int i = 0; i < interaction_count(); i++)
   //   {

   //      ::pointer<::user::interaction>puserinteraction = interaction_at(i);

   //      if (puserinteraction && puserinteraction->get_safe_oswindow() == oswindow)
   //      {

   //         return interaction_at(i);

   //      }

   //   }

   //   return nullptr;

   //}


   //bool interaction_pointer_array::get_child(::pointer<::user::interaction>& pinteraction)
   //{

   //   if (has_no_interaction())
   //   {

   //      return false;

   //   }

   //   if (pinteraction == nullptr)
   //   {

   //      pinteraction = interaction_at(0);

   //      return true;

   //   }
   //   else
   //   {

   //      for (::collection::index i = interaction_last_index(); i >= 0; i--)
   //      {

   //         if (interaction_at(i) == pinteraction)
   //         {

   //            i++;

   //            if (i < interaction_count())
   //            {

   //               pinteraction = interaction_at(i);

   //               return true;

   //            }
   //            else
   //            {

   //               return false;

   //            }

   //         }

   //      }

   //   }

   //   return false;

   //}


   //bool interaction_pointer_array::rget_child(::pointer<::user::interaction>& pinteraction)
   //{

   //   if (has_no_interaction())
   //   {

   //      return false;

   //   }

   //   if (pinteraction == nullptr)
   //   {

   //      pinteraction = last_interaction();

   //      return true;

   //   }
   //   else
   //   {

   //      for (::collection::index i = 0; i < interaction_count(); i++)
   //      {

   //         if (interaction_at(i) == pinteraction)
   //         {

   //            i--;

   //            if (i >= 0)
   //            {

   //               pinteraction = interaction_at(i);

   //               return true;

   //            }
   //            else
   //            {

   //               return false;

   //            }

   //         }

   //      }

   //   }

   //   return false;

   //}


   interaction_array::interaction_array()
   {

   }


   interaction_array::interaction_array(const address_array_base < ::user::interaction * > & ptra)
   {

      for (::collection::index i = 0; i < ptra.get_count(); i++)
      {

         try
         {

            add_interaction(ptra[i]);

         }
         catch (...)
         {

         }

      }

   }


#ifdef _DEBUG


   long long interaction_array::increment_reference_count()
   {

      return ::matter::increment_reference_count();

   }


   long long interaction_array::decrement_reference_count()
   {

      return ::matter::decrement_reference_count();

   }


#endif


   ::pointer<::user::interaction>interaction_array::find_first(oswindow oswindow)
   {

      for (int i = 0; i < this->interaction_count(); i++)
      {

         if (this->interaction_at(i)->get_safe_oswindow() == oswindow)
         {

            return this->interaction_at(i);

         }

      }

      return nullptr;

   }


   interaction_array & interaction_array::operator = (const pointer_array < ::user::interaction > & a)
   {

      m_interactiona.copy(a);

      return *this;

   }


   interaction_array & interaction_array::operator = (const interaction_array & a)
   {

      m_interactiona.copy(a.m_interactiona);

      return *this;

   }


   void interaction_array::send_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
   {

      for (int i = 0; i < this->interaction_count(); i++)
      {

         try
         {

            this->interaction_at(i)->send_message(eusermessage, wparam, lparam);

         }
         catch (...)
         {

         }

      }

   }


   void interaction_array::send_message_to_descendants(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, bool bRecursive)
   {

      for (int i = 0; i < this->interaction_count(); i++)
      {

         try
         {

            this->interaction_at(i)->send_message_to_descendants(eusermessage, wparam, lparam, bRecursive);

         }
         catch (...)
         {

         }

      }

   }


   bool interaction_array::get_child(::pointer<::user::interaction>& pinteraction)
   {

      if (interaction_count() <= 0)
      {

         return false;

      }

      if (pinteraction.is_null())
      {

         pinteraction = interaction_at(0);

         return true;

      }
      else
      {

         for (::collection::index i = this->interaction_last_index(); i >= 0; i--)
         {

            if (interaction_at(i) == pinteraction)
            {

               i++;

               if (i < interaction_count())
               {

                  pinteraction = interaction_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }


   bool interaction_array::rget_child(::pointer<::user::interaction>& pinteraction)
   {

      if (interaction_count() <= 0)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = last_interaction();

         return true;

      }
      else
      {

         for (::collection::index i = 0; i < interaction_count(); i++)
         {

            if (interaction_at(i) == pinteraction)
            {

               i--;

               if (i >= 0)
               {

                  pinteraction = interaction_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }




//   void oswindow_array::top_windows_by_z_order()
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      int iOrder = 0;
//      ::windowing::window * pwindowOrder = ::get_desktop_window();
//      oswindowOrder = ::GetWindow(oswindowOrder, GW_CHILD);
//      while (oswindowOrder != nullptr
//         && ::is_window(oswindowOrder))
//      {
//         add(oswindowOrder);
//         oswindowOrder = ::GetWindow(oswindowOrder, GW_HWNDNEXT);
//         iOrder++;
//      }
//
//#else
//
//      throw ::interface_only();
//
//#endif
//
//   }
















} // namespace user



