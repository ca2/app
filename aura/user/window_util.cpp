#include "framework.h"


namespace user
{


   interaction_ptra & interaction_ptra::operator=(const interaction_array & a)
   {

      for (index i = 0; i < a.interaction_count(); i++)
      {

         add(a.get_interaction(i));

      }

      return *this;

   }





   ::user::interaction * interaction_ptra::find_first_typed(const ::type & type)
   {

      for (i32 i = 0; i < this->get_size(); i++)
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

      for (i32 i = 0; i < this->get_size(); i++)
      {

         if (this->element_at(i)->get_safe_oswindow() == oswindow)
         {

            return this->element_at(i);

         }

      }

      return nullptr;

   }


   bool interaction_ptra::get_child(__pointer(::user::interaction) & pinteraction)
   {

      //synchronization_lock synchronizationlock(mutex());

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

         for (index i = get_upper_bound(); i >= 0; i--)
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

   bool interaction_ptra::rget_child(__pointer(::user::interaction) & pinteraction)
   {

      //synchronization_lock synchronizationlock(mutex());

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

         for (index i = 0; i < get_size(); i++)
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







   primitive_ptra & primitive_ptra::operator=(const primitive_ptra & a)
   {

      remove_all();

      for (index i = 0; i < a.get_count(); i++)
      {

         add(a.element_at(i));

      }

      return *this;

   }




   ::user::primitive * primitive_ptra::find_first_typed(const ::type & type)
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         ::user::primitive * pprimitive = this->element_at(i);

         if (type == pprimitive)
         {

            return pprimitive;

         }

      }

      return nullptr;

   }


   ::user::primitive * primitive_ptra::find_first(oswindow oswindow)
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         if (this->element_at(i)->get_safe_oswindow() == oswindow)
         {

            return this->element_at(i);
         }
      }

      return nullptr;

   }



   bool primitive_ptra::get_child(__pointer(::user::primitive) & pprimitive)
   {

      //synchronization_lock synchronizationlock(mutex());

      if (get_count() <= 0)
      {

         return false;

      }

      if (pprimitive == nullptr)
      {

         pprimitive = element_at(0);

         return true;

      }
      else
      {

         for (index i = get_upper_bound(); i >= 0; i--)
         {

            if (element_at(i) == pprimitive)
            {

               i++;

               if (i < get_count())
               {

                  pprimitive = element_at(i);

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

   bool primitive_ptra::rget_child(__pointer(::user::primitive) & pprimitive)
   {

      //synchronization_lock synchronizationlock(mutex());

      if (get_count() <= 0)
      {

         return false;

      }

      if (pprimitive == nullptr)
      {

         pprimitive = last();

         return true;

      }
      else
      {

         for (index i = 0; i < get_size(); i++)
         {

            if (element_at(i) == pprimitive)
            {

               i--;

               if (i >= 0)
               {

                  pprimitive = element_at(i);

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



















   interaction_array::interaction_array()
   {

   }


   //interaction_pointer_array::interaction_pointer_array(::layered * pobjectContext) :
   //   ::object(pobject)
   //{

   //}


   interaction_array::interaction_array(const address_array < ::user::interaction * > & ptra)
   {

      for (index i = 0; i < ptra.get_count(); i++)
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


   //__pointer(::user::interaction) interaction_pointer_array::find_first_typed(::type info)
   //{

   //   for (i32 i = 0; i < this->get_size(); i++)
   //   {

   //      ::user::interaction * pinteraction = this->element_at(i);

   //      if (typeid(*pinteraction).name() == info->name())
   //      {

   //         return this->element_at(i);

   //      }

   //   }

   //   return nullptr;

   //}


   __pointer(::user::interaction) interaction_array::find_first(oswindow oswindow)
   {

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         if (this->interaction_at(i)->get_safe_oswindow() == oswindow)
         {

            return this->interaction_at(i);

         }

      }

      return nullptr;

   }


   interaction_array & interaction_array::operator = (const __pointer_array(::user::interaction) & a)
   {

      m_interactiona.copy(a);

      return *this;

   }


   interaction_array & interaction_array::operator = (const interaction_array & a)
   {

      m_interactiona.copy(a.m_interactiona);

      return *this;

   }


   void interaction_array::send_message(const ::id & id, wparam wparam, lparam lparam)

   {
      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         try
         {

            this->interaction_at(i)->send_message(id, wparam, lparam);

         }
         catch (...)
         {

         }

      }

   }


   void interaction_array::send_message_to_descendants(const ::id & id, wparam wparam, lparam lparam, bool bRecursive)
   {

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         try
         {

            this->interaction_at(i)->send_message_to_descendants(id, wparam, lparam, bRecursive);

         }
         catch (...)
         {

         }

      }

   }


   bool interaction_array::get_child(__pointer(::user::interaction) & pinteraction)
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

         for (index i = this->interaction_last_index(); i >= 0; i--)
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


   bool interaction_array::rget_child(__pointer(::user::interaction) & pinteraction)
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

         for (index i = 0; i < interaction_count(); i++)
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
//      i32 iOrder = 0;
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
//      ::exception::throw_not_implemented();
//
//#endif
//
//   }
















} // namespace user



