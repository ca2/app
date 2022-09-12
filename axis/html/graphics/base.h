#pragma once


namespace html
{


   class tag;


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

      class tag * get_parent();

      class tag * get_tag();

      class value * get_value();




   };


   typedef address_array < base * > base_ptr_array;


} // namespace html

