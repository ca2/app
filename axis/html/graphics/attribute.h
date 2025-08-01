#pragma once


#include "acme/prototype/prototype/atom.h"
//#include "acme/prototype/collection/pointer_array.h"


namespace html
{


   class attribute :
      virtual public ::particle
   {
   public:


      atom          m_atomName;
      string      m_strValue;


      void set_name(const ::atom & atom);
      atom get_name() const;

      void set_value(const ::scoped_string & scopedstr);
      string get_value() const;


   };


   class attribute_array : public pointer_array < attribute >
   {
   public:


      ::pointer<class attribute> get(const ::atom & atom);
      ::pointer<class attribute> get(const ::atom & atom) const;
      string get_value(const ::atom & atom) const;


   };



} // namespace html





