#pragma once



//CLASS_DECL_ACME bool demangle(string & str, const char * psz);
inline void demangle(string & str);
#ifdef WINDOWS
inline const char * demangle_cstr(const char* psz)
{

   if (psz[0] == 'c' &&
      psz[1] == 'l' &&
      psz[2] == 'a' &&
      psz[3] == 's' &&
      psz[4] == 's' &&
      psz[5] == ' ')
   {

      return psz + 6;

   }
   else if (psz[0] == 's' &&
      psz[1] == 't' &&
      psz[2] == 'r' &&
      psz[3] == 'u' &&
      psz[4] == 'c' &&
      psz[5] == 't' &&
      psz[6] == ' ')
   {

      return psz + 7;

   }
   else
   {

      return psz;

   }

}

inline void demangle(string& str)
{

   str = demangle_cstr(str);

}


#elif defined(__APPLE__)


namespace str
{


   CLASS_DECL_ACME string demangle(const char * psz);


} // namespace str


inline void demangle(string& str)
{

   str = str::demangle(str);

}


#else


inline const char * demangle_cstr(const char* psz)
{

    return psz;

}


#endif






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
      
      demangle(m_strName);

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

   type(const ::matter * pobject);

   template < typename BASE >
   type(const __pointer(BASE) & point);


   type & operator = (const ::std::type_info & typeinfo)
   {

      //demangle(m_strName, typeinfo.name());
      
      string strName = typeinfo.name();
      
      demangle(strName);
      
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

      demangle(strName);

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


   bool operator == (const ::matter * pobject) const
   {

      return operator ==(::type(pobject));

   }


   bool operator != (const ::matter* pobject) const
   {

      return !operator==(pobject);

   }

   //inline __pointer(matter) alloc(::matter * pobject) const;

   inline operator bool() const { return m_strName.has_char(); }


   inline operator const char * () const { return m_strName; }

   inline operator const string & () const { return m_strName; }

   inline const string & to_string() const { return m_strName; }


};


inline CLASS_DECL_ACME string get_demangle(const char * lpszName)
{

   string str(lpszName);

   demangle(str);

   return str;

}


template < typename T >
inline string friendly_this_name(T const * pthis)
{

   string str = typeid(*pthis).name();

   demangle(str);

   return str;

}


#define THIS_FRIENDLY_NAME() friendly_this_name(this)


template < typename TYPE >
::type ___type()
{

   return ::type(typeid(TYPE));

}



#define __type(TYPE)  ___type<TYPE>()
