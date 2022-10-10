#include "framework.h"
// #if !BROAD_PRECOMPILED_HEADER
// #include "_graphics.h"
// #endif 
#include "attribute.h"


namespace html
{


   void attribute::set_name(atom idName)
   {

      m_atomName = idName;

   }

   atom attribute::get_name() const
   {

      return m_atomName;

   }


   void attribute::set_value(const ::string & pszValue)
   {

      m_strValue = pszValue;

   }


   string attribute::get_value() const
   {

      return m_strValue;

   }



   // attribute_array

   ::pointer<attribute>attribute_array::get(atom idName)
   {

      for(i32 i = 0; i < this->get_size(); i++)
      {

         if(this->element_at(i)->get_name() == idName)
            return this->element_at(i);

      }

      return nullptr;

   }


   ::pointer<attribute>attribute_array::get(atom idName) const
   {

      return const_cast < attribute_array * > (this)->get(idName);

   }


   string attribute_array::get_value(atom idName) const
   {

      auto pattribute = get(idName);

      if (!pattribute)
      {

         return nullptr;

      }

      return pattribute->get_value();

   }


} // namespace html



