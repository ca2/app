#pragma once


#include "attribute.h"
#include "base.h"
#include "acme/primitive/collection/address_array.h"


namespace html
{


   class tag : public base
   {
   public:


      atom                m_atomName;
      attribute_array   m_attra;
      base_ptr_array    m_baseptra;


      tag(tag * pparent);
      virtual ~tag();

      type get_type();

      attribute_array & attra();

      void set_name(atom idName);
      atom get_name();

      attribute * get_attr(atom idName);
      string get_attr_value(atom idName);

      base_ptr_array & baseptra();


   };



} // namespace html
