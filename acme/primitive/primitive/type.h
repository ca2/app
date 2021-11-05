#pragma once


CLASS_DECL_ACME string demangle(const char * psz);


class CLASS_DECL_ACME type
{
public:


   string   m_strName;


   type()
   {

   }


   type(const char * pszTypeName) :
      m_strName(pszTypeName)
   {
      
   }


   type(const ::type & type)
   {

      operator = (type);

   }


   type(::type && type):
      m_strName(::move(type.m_strName))
   {

   }


   type(const ::std::type_info & typeinfo)
   {

      operator = (typeinfo);

   }

   type(const ::element * pelement);

   template < typename BASE >
   type(const __pointer(BASE) & point);


   type & operator = (const ::std::type_info & typeinfo)
   {

      string strName = typeinfo.name();
      
      strName = demangle(strName);
      
      m_strName = strName;

      return *this;

   }


   type & operator = (const ::type & type)
   {

      if (this != &type)
      {

         m_strName = type.m_strName;

      }

      return *this;

   }


   string name() const { return m_strName; }


   bool operator == (const ::std::type_info & typeinfo) const
   {

      string strName = ::type(typeinfo).name();

      strName = demangle(strName);

      return m_strName == strName;

   }


   bool operator == (const ::type & type) const
   {

      return m_strName == type.m_strName;

   }

   bool operator == (const ::string & strType) const
   {

      return m_strName == strType;

   }


   bool operator == (const ::id& id) const;


   bool operator != (const ::std::type_info & typeinfo) const
   {

      return !operator==(typeinfo);

   }


   bool operator != (const ::type & type) const
   {

      return !operator==(type);

   }


   bool operator == (const ::element * pelement) const
   {

      return operator ==(::type(pelement));

   }


   bool operator != (const ::element * pelement) const
   {

      return !operator==(pelement);

   }

   inline operator bool() const { return m_strName.has_char(); }

   inline operator const char * () const { return m_strName; }

   inline operator const string & () const { return m_strName; }

   inline const string & to_string() const { return m_strName; }


};


template < typename TYPE >
::type ___type()
{

   return ::type(typeid(TYPE));

}


#define __type(TYPE)  ___type<TYPE>()



