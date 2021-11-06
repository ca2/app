#pragma once


namespace html
{

   class tag : public base
   {
   public:


      id                m_idName;
      attribute_array   m_attra;
      base_ptr_array    m_baseptra;


      tag(tag * pparent);
      virtual ~tag();

      type get_type();

      attribute_array & attra();

      void set_name(id idName);
      id get_name();

      attribute * get_attr(id idName);
      string get_attr_value(id idName);

      base_ptr_array & baseptra();


   };



} // namespace html
