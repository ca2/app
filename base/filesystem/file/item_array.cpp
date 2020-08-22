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


   var item_array::get_var_file() const
   {

      if (this->get_count() <= 0)
      {

         return ::var(::type_empty);

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

         class var var;

         for (index i = 0; i < this->get_count(); i++)
         {

            if (this->element_at(i)->m_filepathUser.has_char())
            {

               var.stra().add(this->element_at(i)->m_filepathUser);

            }
            else
            {

               var.stra().add(this->element_at(i)->m_filepathFinal);

            }

         }

         return var;

      }

   }


   var item_array::get_var_final_path() const
   {

      if (this->get_count() <= 0)
      {

         return ::var(::type_empty);

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

         class var var;

         for (index i = 0; i < this->get_count(); i++)
         {

            if (this->element_at(i)->m_filepathFinal.has_char())
            {

               var.stra().add(this->element_at(i)->m_filepathFinal);

            }
            else
            {

               var.stra().add(this->element_at(i)->m_filepathUser);

            }

         }

         return var;

      }

   }


   var item_array::get_var_query() const
   {

      if (this->get_count() <= 0)
      {

         return ::var(::type_empty);

      }
      else if (this->get_count() == 1)
      {

         class var var;

         var["FileManagerItem_flags"] = __new(flags < e_flag >(this->element_at(0)->m_flags));

         return var;

      }
      else
      {

         class var var;

         for (index i = 0; i < this->get_count(); i++)
         {

            class var varPropSet;

            varPropSet["FileManagerItem_flags"] = __new(flags < e_flag >(this->element_at(i)->m_flags));

            var.vara().add(varPropSet);

         }

         return var;

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



