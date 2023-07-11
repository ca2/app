#pragma once


namespace html
{


   class tag;
   class value;


   class base
   {
   public:


      enum type
      {
         type_value,
         type_tag,
      };

      class tag *             m_ptagParent;


      base(tag * pparent);
      virtual ~base();

      virtual type get_type() = 0;


      ::html::tag * get_parent();

      ::html::tag * get_tag();

      ::html::value * get_value();


   };


   typedef address_array < base * > base_ptr_array;


} // namespace html

