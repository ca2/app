#include "framework.h"

#include "attribute.h"


namespace html
{


   void attribute::set_name(const ::atom & atom)
   {

      m_atomName = atom;

   }

   atom attribute::get_name() const
   {

      return m_atomName;

   }


   void attribute::set_value(const ::scoped_string & scopedstrValue)
   {

      m_strValue = scopedstrValue;

   }


   string attribute::get_value() const
   {

      return m_strValue;

   }


   // attribute_array

   ::pointer<attribute>attribute_array::get(const ::atom & atom)
   {

      for(int i = 0; i < this->get_size(); i++)
      {

         if(this->element_at(i)->get_name() == atom)
         {
            return this->element_at(i);
         }

      }

      return nullptr;

   }


   ::pointer<attribute>attribute_array::get(const ::atom & atom) const
   {

      return const_cast < attribute_array * > (this)->get(atom);

   }


   string attribute_array::get_value(const ::atom & atom) const
   {

      auto pattribute = get(atom);

      if (!pattribute)
      {

         return nullptr;

      }

      return pattribute->get_value();

   }


} // namespace html



