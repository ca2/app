#pragma once


namespace html
{


   class attribute :
      virtual public ::object
   {
   public:


      id          m_idName;
      string      m_strValue;


      void set_name(id idName);
      id get_name() const;

      void set_value(const ::string & pszValue);
      string get_value() const;


   };


   class attribute_array : public __pointer_array(attribute)
   {
   public:


      __pointer(class attribute) get(id idName);
      __pointer(class attribute) get(id idName) const;
      string get_value(id idName) const;


   };



} // namespace html





