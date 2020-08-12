#include "framework.h"
#include "internal.h"


namespace html
{

   
   void attribute::set_name(id idName)
   {

      m_idName = idName;

   }

   id attribute::get_name() const
   {

      return m_idName;

   }


   void attribute::set_value(const char * pszValue)
   {

      m_strValue = pszValue;

   }


   string attribute::get_value() const
   {

      return m_strValue;

   }



   // attribute_array

   __pointer(attribute) attribute_array::get(id idName)
   {

      for(i32 i = 0; i < this->get_size(); i++)
      {

         if(this->element_at(i)->get_name() == idName)
            return this->element_at(i);

      }

      return nullptr;

   }


   __pointer(attribute) attribute_array::get(id idName) const 
   {

      return const_cast < attribute_array * > (this)->get(idName);

   }


   string attribute_array::get_value(id idName) const
   {

      auto pattribute = get(idName);

      if (!pattribute)
      {

         return nullptr;

      }

      return pattribute->get_value();

   }


} // namespace html



