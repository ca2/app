#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{

   place_holder_container::place_holder_container()
   {
   }



   place_holder_container::~place_holder_container()
   {
   }

   void place_holder_container::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);
   }


   ::user::place_holder * place_holder_container::get_new_place_holder(const ::rectangle_i32 & rectangleCreate)
   {

      auto pplaceholder = __create_new < ::user::place_holder >();

      if (!pplaceholder)
      {

         return nullptr;

      }

      pplaceholder->display(e_display_normal);

      pplaceholder->create_child(this);

      //if(!pplaceholder->create_child(this))
      //{

      //   return nullptr;

      //}

      m_placeholdera.add(pplaceholder);

      return pplaceholder;

   }


   bool place_holder_container::erase_place_holder(::user::place_holder * pholder)
   {
      bool bRemove = m_placeholdera.erase(pholder) > 0;
      return bRemove;
   }

   ::user::place_holder * place_holder_container::place_hold(::user::interaction * pinteraction,const ::rectangle_i32 & rectangleCreate)
   {
      __pointer(place_holder) pholder = get_new_place_holder(rectangleCreate);
      if(!on_place_hold(pinteraction, pholder))
      {
         erase_place_holder(pholder);
         return nullptr;
      }
      return pholder;
   }


   bool place_holder_container::unplace(::user::interaction * pinteraction)
   {

      for(i32 i = 0; i < m_placeholdera.get_count(); i++)
      {

         if(m_placeholdera[i]->is_place_holding(pinteraction))
         {

            if(on_unplace(pinteraction, m_placeholdera[i]))
            {

               m_placeholdera.erase_at(i);

               return true;

            }

            return false;

         }

      }

      return false;

   }


   bool place_holder_container::on_place_hold(::user::interaction * pinteraction, ::user::place_holder * pholder)
   {

      if(pholder->can_merge(pinteraction))
      {

         return pholder->merge(pinteraction);

      }
      else
      {

         return pholder->place_hold(pinteraction);

      }

   }


   bool place_holder_container::on_unplace(::user::interaction * pinteraction, ::user::place_holder * pholder)
   {

      return pholder->unplace(pinteraction);

   }


   //bool place_holder_container::create_interaction(::user::interaction * puiParent,id id)
   //{

   //   return ::user::interaction::create_interaction(puiParent) != false;

   //}


   place_holder_ptra place_holder_container_ptra::place(::user::interaction * pinteraction,const rectangle_i32 & rectangleCreate)
   {

      place_holder_ptra holderptra;

      __pointer(place_holder) pholder;

      for(i32 i = 0; i < this->get_count(); i++)
      {

         pholder = this->element_at(i)->place_hold(pinteraction,rectangleCreate);

         if(pholder != nullptr)
         {

            holderptra.add(pholder);

         }

      }

      return holderptra;

   }


   i32 place_holder_container_ptra::unplace(::user::interaction * pinteraction)
   {
      i32 count = 0;
      for(i32 i = 0; i < this->get_count(); i++)
      {
         if(this->element_at(i)->unplace(pinteraction))
         {
            count++;
         }
      }
      return count;
   }

} // namespace user
