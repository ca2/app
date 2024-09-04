#include "framework.h"
#include "item_array.h"
#include "item.h"
#include "acme/platform/flags.h"
//#include "acme/primitive/primitive/payload.h"


namespace file
{


   item_array::item_array(nullptr_t)
   {

   }


   item_array::item_array(const item_array & itema) :
      pointer_array < item >(itema)
   {

   }


   item_array::item_array(item_array && itema) :
      pointer_array < item >(::transfer(itema))
   {

   }


   item_array::~item_array()
   {

   }


   ::payload item_array::get_var_file() const
   {

      if (this->get_count() <= 0)
      {

         return payload(::e_type_empty);

      }
      else if (this->get_count() == 1)
      {

         return this->element_at(0)->user_path();

      }
      else
      {

         class ::payload payload;

         for (::collection::index i = 0; i < this->get_count(); i++)
         {

            payload.as_string_array().add(this->element_at(i)->user_path());

         }

         return payload;

      }

   }


   ::payload item_array::get_var_final_path() const
   {

      if (this->get_count() <= 0)
      {

         return payload(::e_type_empty);

      }
      else if (this->get_count() == 1)
      {

         return this->element_at(0)->final_path();

      }
      else
      {

         class ::payload payload;

         for (::collection::index i = 0; i < this->get_count(); i++)
         {

            payload.as_string_array().add(this->element_at(i)->final_path());

         }

         return payload;

      }

   }


   ::payload item_array::get_var_query() const
   {

      if (this->get_count() <= 0)
      {

         return payload(::e_type_empty);

      }
      else if (this->get_count() == 1)
      {

         class ::payload payload;

         auto pflags = ::place(new  flags < enum_flag > (this->element_at(0)->m_flags));

         payload["FileManagerItem_flags"] = pflags;

         return payload;

      }
      else
      {

         class ::payload payload;

         for (::collection::index i = 0; i < this->get_count(); i++)
         {

            class ::payload varPropSet;

            varPropSet["FileManagerItem_flags"] = ::place(new flags < enum_flag > (this->element_at(i)->m_flags));

            payload.as_payload_array().add(varPropSet);

         }

         return payload;

      }

   }


   item_array & item_array::operator = (const item_array & itema)
   {

      pointer_array < item >::operator = (itema);

      return *this;

   }


   item_array & item_array::operator = (item_array && itema)
   {

      pointer_array < item >::operator = (::transfer(itema));

      return *this;

   }


} // namespace file



