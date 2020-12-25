#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   control_descriptor::control_descriptor()
   {

      control_descriptor_common_construct();

   }


   control_descriptor::control_descriptor(arguments arguments)
   {

      control_descriptor_common_construct();

      for (auto & argument : arguments)
      {

         auto etype = argument.get_type();

         switch (etype)
         {
         case type_type:
         {

            m_type.m_strName = argument.m_str;

            break;

         }
         case type_string:
         {

            string str = argument.get_string();

            if (str::begins_eat_ci(str, "class="))
            {

               m_strClass = str;

            }
            else if (str::begins_eat_ci(str, "style="))
            {

               m_strStyle = str;

            }
            else
            {

               m_id = argument.get_id();

            }

            break;
         };
         case type_id:
         case type_i64:
         case type_i32:
         {

            m_id = argument.get_id();

            break;

         }
         case type_element:
         {

            //auto pinteraction = argument.cast < interaction >();

            //if (pinteraction)
            //{

            //   if (::is_null(get_context_object()))
            //   {

            //      set_context_object(pinteraction);

            //   }

            //   if (pinteraction->is_window())
            //   {

            //      m_puserinteractionParent = pinteraction;

            //      break;

            //   }
            //   else
            //   {

            //      m_pusercontrol = pinteraction;

            //      break;

            //   }

            //}

            //auto playout = argument.cast < layout >();

            //if (playout)
            //{

            //   if (::is_null(get_context_object()))
            //   {

            //      set_context_object(playout->get_context_object());

            //   }

            //   m_playout = playout;

            //}

            //if (::is_null(get_context_object()))
            //{

            //   set_context_object(argument.cast < ::object > ());

            //}

         }
               break;
            default:
               break;

         }

      }

   }

   control_descriptor::~control_descriptor()
   {

      //if(m_pcontrol != nullptr)
      //{

      //   if(m_bCreated)
      //   {

      //      m_pcontrol->DestroyWindow();

      //   }
      //   else if(m_bSubclassed)
      //   {

      //      m_pcontrol->unsubclass_window();

      //   }

      //   m_pcontrol.release();

      //}

   }


   void control_descriptor::control_descriptor_common_construct()
   {

      m_id.is_empty();
      m_iItem = 0;
      m_econtroltype = e_control_type_none;
      m_bTransparent = false;
      m_bCreated = false;
      m_edatatype = e_control_data_type_string;
      m_flagsfunction.clear();
      m_controlmap.remove_all();
      m_bSubclassed = false;
      m_iSubItem = -1;
      m_iColumn = -1;

   }


   //void control_descriptor::clear()
//{

//   m_playout = nullptr;
//   m_puserinteractionParent = nullptr;
//   m_playout = nullptr;
//   m_id.is_empty();
//   m_iItem = 0;
//   m_econtroltype = e_control_type_none;
//   m_bTransparent = false;
//   m_bCreated = false;
//   m_edatatype = e_control_data_type_string;
//   m_flagsfunction.clear();
//   m_controlmap.remove_all();
//   m_bSubclassed = false;
//   m_iSubItem = -1;
//   m_iColumn = -1;

//}




   //control_descriptor::control_descriptor(const class control_descriptor & control_descriptor)
   //{

   //   operator =(control_descriptor);

   //}


   //class control_descriptor & control_descriptor::operator = (const control_descriptor & control_descriptor)
   //{

   //   if (&control_descriptor == this)
   //      return *this;

   //   m_iItem = control_descriptor.m_iItem;
   //   m_id = control_descriptor.m_id;
   //   m_econtroltype = control_descriptor.m_econtroltype;
   //   m_datakey = control_descriptor.m_datakey;
   //   m_bTransparent = control_descriptor.m_bTransparent;
   //   m_flagsfunction = control_descriptor.m_flagsfunction;
   //   m_type = control_descriptor.m_type;
   //   m_bCreated = control_descriptor.m_bCreated;
   //   m_edatatype = control_descriptor.m_edatatype;
   //   m_idPrivateDataSection = control_descriptor.m_idPrivateDataSection;
   //   //m_pcontrol              = control_descriptor.m_pcontrol;
   //   m_controlmap.remove_all();
   //   m_eddx = control_descriptor.m_eddx;
   //   m_puserinteractionParent = control_descriptor.m_puserinteractionParent;
   //   m_iSubItem = control_descriptor.m_iSubItem;
   //   m_iColumn = control_descriptor.m_iColumn;
   //   m_setValue = control_descriptor.m_setValue;
   //   m_iSubItemDisableCheckBox = control_descriptor.m_iSubItemDisableCheckBox;
   //   m_iSubItemDuplicateCheckBox = control_descriptor.m_iSubItemDuplicateCheckBox;
   //   m_iaSubItemDuplicate = control_descriptor.m_iaSubItemDuplicate;
   //   m_iaSubItemDisable = control_descriptor.m_iaSubItemDisable;

   //   return *this;

   //}


   /*::database::client * control_descriptor::get_data_client()
   {
      if(m_puserinteraction == nullptr)
      {

         return nullptr;

      }

      return dynamic_cast < ::database::client * > (m_puserinteraction);

   }*/


   bool control_descriptor::operator == (const control_descriptor & descriptor) const
   {

 /*     if (m_pusercontrol && ::is_set(descriptor.m_pusercontrol))
      {

         return m_pusercontrol == descriptor.m_pusercontrol;

      }*/

      return m_id == descriptor.m_id && m_puserinteractionParent->descriptor() == descriptor.m_puserinteractionParent->descriptor();

   }


   void control_descriptor::add_function(enum_control_function enum_control_function)
   {

      m_flagsfunction.add(enum_control_function);

   }


   void control_descriptor::remove_function(enum_control_function enum_control_function)
   {

      m_flagsfunction.remove(enum_control_function);

   }


   bool control_descriptor::has_function(enum_control_function enum_control_function)
   {

      return m_flagsfunction.has(enum_control_function);

   }


   void control_descriptor::set_data_type(enum_control_data_type edatatype)
   {

      m_edatatype = edatatype;

   }


   enum_control_data_type control_descriptor::get_data_type()
   {

      return m_edatatype;

   }


   void control_descriptor::set_ddx_dbflags(::database::key datakey, iptr value)
   {

      m_eddx = ::user::e_control_ddx_dbflags;

      m_datakey = datakey;

      m_iDataValue = (int)value;




   }

   //control * control_descriptor::get_control(::user::form * pform, index iItem)
   //{

   //   __pointer(interaction) &  pinteraction = m_controlmap[0];

   //   if (pinteraction != nullptr)
   //   {

   //      return pinteraction;

   //   }

   //   iItem = 0;

   //   if (!pform->create_control(this, iItem))
   //   {

   //      pinteraction.release();

   //      return nullptr;

   //   }

   //   pinteraction = m_puserinteraction;

   //   return pinteraction.cast < control>();

   //}

   index control_descriptor::find_control(::user::interaction * pinteraction)
   {

      for (auto pair : m_controlmap)
      {

         if (pair.element2() == pinteraction)
         {

            return pair.element1();

         }

      }

      return -1;

   }


   void control_descriptor::set_control_type(enum_control_type econtroltype)
   {

      m_econtroltype = econtroltype;

      switch (m_econtroltype)
      {
      case e_control_type_edit:

         //         m_type = __type(CSimpleFormListEdit);

         break;

      case e_control_type_combo_box:
      {

         //__throw(todo());

//            m_data.m_pcombobox = new Ex1FormInterfaceComboBox;

      }
      break;
      default:
         break;
      }

   }


   enum_control_type control_descriptor::get_control_type()
   {

      return m_econtroltype;

   }


   __pointer(interaction) control_descriptor::alloc()
   {

      ASSERT(::is_set(m_puserinteractionParent));

      enum_control_type econtroltype = e_control_type_none;

      if (m_type.m_strName.is_empty())
      {

         if (m_id.has_char())
         {

            m_type = App(m_puserinteractionParent).control_type_from_id(m_id, econtroltype);

         }
         //else if(m_econtroltype != e_control_type_none)
         //{

         //   m_type = App(m_puserinteractionParent).user_default_controltype_to_typeinfo(m_econtroltype);

         //}

      }

      if (m_econtroltype == e_control_type_none)
      {

         m_econtroltype = econtroltype;

      }

      if (m_type.m_strName.is_empty())
      {

         dev_log("Could not allocate control: (empty type name)");

         return nullptr;

      }

      auto pinteraction = m_puserinteractionParent->__id_create<interaction>(m_type);

      if (pinteraction.is_null())
      {

         dev_log("Could not allocate control: Type \"" + m_type.m_strName + "\" doesn't have allocator or isn't ::user::interaction");

      }

      return ::move(pinteraction);

   }


} // namespace user




