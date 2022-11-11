#pragma once


#include "acme/primitive/primitive/atom.h"
#include "acme/primitive/collection/pointer_array.h"


namespace html
{


   class attribute :
      virtual public ::particle
   {
   public:


      atom          m_atomName;
      string      m_strValue;


      void set_name(atom idName);
      atom get_name() const;

      void set_value(const ::string & pszValue);
      string get_value() const;


   };


   class attribute_array : public pointer_array < attribute >
   {
   public:


      ::pointer<class attribute> get(atom idName);
      ::pointer<class attribute> get(atom idName) const;
      string get_value(atom idName) const;


   };



} // namespace html





