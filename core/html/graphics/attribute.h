#pragma once


namespace html
{


   class attribute :
      virtual public ::object
   {
   public:


      atom          m_idName;
      string      m_strValue;


      void set_name(atom idName);
      atom get_name() const;

      void set_value(const ::string & pszValue);
      string get_value() const;


   };


   class attribute_array : public __pointer_array(attribute)
   {
   public:


      __pointer(class attribute) get(atom idName);
      __pointer(class attribute) get(atom idName) const;
      string get_value(atom idName) const;


   };



} // namespace html





