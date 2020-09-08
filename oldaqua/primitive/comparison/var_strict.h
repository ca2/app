#pragma once


namespace comparison
{


   class CLASS_DECL_AQUA var_strict
   {
   public:


      const var * m_pvar;


      var_strict(const var & var);
      var_strict(const ::comparison::var_strict & compare);


      bool operator == (const var & var) const;
      bool operator == (const char * psz) const;
      bool operator == (const string & str) const;
      bool operator == (double d) const;
      bool operator == (i32 i) const;
      bool operator == (bool b) const;

      bool operator != (const var & var) const;
      bool operator != (const char * psz) const;
      bool operator != (const string & str) const;
      bool operator != (double d) const;
      bool operator != (i32 i) const;
      bool operator != (bool b) const;

      friend bool CLASS_DECL_AQUA operator == (const char * psz, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator == (const string & str, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator == (double d, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator == (i32 i, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator == (bool b, const ::comparison::var_strict & var);

      friend bool CLASS_DECL_AQUA operator != (const char * psz, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator != (const string & str, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator != (double d, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator != (i32 i, const ::comparison::var_strict & var);
      friend bool CLASS_DECL_AQUA operator != (bool b, const ::comparison::var_strict & var);

      var_strict & operator = (const var_strict & var);


   };



} // namespace comparison


