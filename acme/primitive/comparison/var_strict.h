#pragma once


namespace comparison
{


   class CLASS_DECL_ACME var_strict
   {
   public:


      const payload * m_pvar;


      var_strict(const payload & payload);
      var_strict(const ::comparison::var_strict & compare);


      bool operator == (const payload & payload) const;
      bool operator == (const char * psz) const;
      bool operator == (const string & str) const;
      bool operator == (double d) const;
      bool operator == (i32 i) const;
      bool operator == (bool b) const;

      bool operator != (const payload & payload) const;
      bool operator != (const char * psz) const;
      bool operator != (const string & str) const;
      bool operator != (double d) const;
      bool operator != (i32 i) const;
      bool operator != (bool b) const;

      friend bool CLASS_DECL_ACME operator == (const char * psz, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator == (const string & str, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator == (double d, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator == (i32 i, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator == (bool b, const ::comparison::var_strict & payload);

      friend bool CLASS_DECL_ACME operator != (const char * psz, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator != (const string & str, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator != (double d, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator != (i32 i, const ::comparison::var_strict & payload);
      friend bool CLASS_DECL_ACME operator != (bool b, const ::comparison::var_strict & payload);

      var_strict & operator = (const var_strict & payload);


   };



} // namespace comparison


