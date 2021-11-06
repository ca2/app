#include "framework.h"
#include "base/user/user/_user.h"


//
//namespace user
//{
//
//
//   control_descriptor_set::control_descriptor_set()
//   {
//
//   }
//
//
//   control_descriptor_set::~control_descriptor_set()
//   {
//
//   }
//
//
//   __pointer(interaction) control_descriptor_set::get_control(::user::form * pform, id id)
//   {
//
//      for (i32 i = 0; i < this->get_size(); i++)
//      {
//
//         class control_descriptor & control_descriptor = *this->element_at(i);
//
//         if (control_descriptor.m_id == id)
//         {
//
//            return control_descriptor.m_pinteraction;
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   bool control_descriptor_set::find_control(::user::interaction * pinteraction, index & iItem, index & iSubItem)
//   {
//
//      for (i32 i = 0; i < this->get_size(); i++)
//      {
//
//         class control_descriptor & control_descriptor = *this->element_at(i);
//
//         iItem = control_descriptor.find_control(pinteraction);
//
//         if (iItem >= 0)
//         {
//
//            iSubItem = control_descriptor.m_iSubItem;
//
//            return true;
//
//         }
//
//      }
//
//      iItem = -1;
//
//      iSubItem = -1;
//
//      return false;
//
//   }
//
//
//   //class control_descriptor * control_descriptor_set::get(__pointer(::user::interaction) puie)
//   //{
//
//   //   __pointer(control) pinteraction =  (puie.m_p);
//
//   //   if(pinteraction == nullptr)
//   //      return nullptr;
//
//   //   for(i32 i = 0; i < this->get_size(); i++)
//   //   {
//
//   //      class control_descriptor & control_descriptor = *this->element_at(i);
//
//   //      if(control_descriptor.m_pcontrol == pinteraction)
//   //      {
//
//   //         return &control_descriptor;
//
//   //      }
//
//   //   }
//
//   //   return nullptr;
//
//   //}
//
//
//   class control_descriptor * control_descriptor_set::get_by_sub_item(index iSubItem)
//   {
//
//      for (i32 i = 0; i < this->get_size(); i++)
//      {
//
//         class control_descriptor & control_descriptor = *this->element_at(i);
//
//         if (control_descriptor.m_iSubItem == iSubItem)
//         {
//
//            return &control_descriptor;
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//
//} // namespace user
//
//

