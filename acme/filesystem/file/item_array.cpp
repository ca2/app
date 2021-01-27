#include "framework.h"


namespace file
{


   item_array::item_array(std::nullptr_t)
   {

   }


   item_array::item_array(const item_array & itema) :
      __pointer_array(item)(itema)
   {

   }


   item_array::item_array(item_array && itema) :
      __pointer_array(item)(::move(itema))
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

         if (this->element_at(0)->m_filepathUser.has_char())
         {

            return this->element_at(0)->m_filepathUser;

         }
         else
         {

            return this->element_at(0)->m_filepathFinal;

         }

      }
      else
      {

         class ::payload payload;

         for (index i = 0; i < this->get_count(); i++)
         {

            if (this->element_at(i)->m_filepathUser.has_char())
            {

               payload.stra().add(this->element_at(i)->m_filepathUser);

            }
            else
            {

               payload.stra().add(this->element_at(i)->m_filepathFinal);

            }

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

         if (this->element_at(0)->m_filepathFinal.has_char())
         {

            return this->element_at(0)->m_filepathFinal;

         }
         else
         {

            return this->element_at(0)->m_filepathUser;

         }

      }
      else
      {

         class ::payload payload;

         for (index i = 0; i < this->get_count(); i++)
         {

            if (this->element_at(i)->m_filepathFinal.has_char())
            {

               payload.stra().add(this->element_at(i)->m_filepathFinal);

            }
            else
            {

               payload.stra().add(this->element_at(i)->m_filepathUser);

            }

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

         payload["FileManagerItem_flags"] = __new(flags < enum_flag >(this->element_at(0)->m_flags));

         return payload;

      }
      else
      {

         class ::payload payload;

         for (index i = 0; i < this->get_count(); i++)
         {

            class ::payload varPropSet;

            varPropSet["FileManagerItem_flags"] = __new(flags < enum_flag >(this->element_at(i)->m_flags));

            payload.vara().add(varPropSet);

         }

         return payload;

      }

   }


   item_array & item_array::operator = (const item_array & itema)
   {

      __pointer_array(item)::operator = (itema);

      return *this;

   }


   item_array & item_array::operator = (item_array && itema)
   {

      __pointer_array(item)::operator = (::move(itema));

      return *this;

   }


} // namespace file



