#pragma once


//namespace str
//{
//
//
//   inline CLASS_DECL_BASE string         from(const id & id)
//   {
//
//      return id;
//
//   }
//
//   inline CLASS_DECL_BASE string &       from(string & str, const id & id)
//   {
//
//      str = id;
//
//      return str;
//
//   }
//
//
//   inline bool CLASS_DECL_BASE begins_eat(var & var, const string & strPrefix)
//   {
//
//      return begins_eat(var.get_ref_string(), strPrefix);
//
//   }
//
//   inline bool CLASS_DECL_BASE begins_eat_ci(var & var, const char * lpcszPrefix) // case insensitive
//   {
//
//      return begins_eat_ci(var.get_ref_string(), lpcszPrefix);
//
//   }
//
//   inline bool CLASS_DECL_BASE begins_eat_ci(var & var, const char * lpcszPrefix, const char * pszSeparator) // case insensitive
//   {
//
//      return begins_eat_ci(var.get_ref_string(), lpcszPrefix, pszSeparator);
//
//   }
//
//   //inline bool begins_eat(property & property, const string & strPrefix)
//   //{
//
//   //   return begins_eat(property.m_var, strPrefix);
//
//   //}
//
//   inline bool CLASS_DECL_BASE begins_eat_ci(property & property, const char * lpcszPrefix) // case insensitive
//   {
//
//      return begins_eat_ci(property.m_var, lpcszPrefix);
//
//   }
//
//   inline bool CLASS_DECL_BASE begins_eat_ci(property & property, const char * lpcszPrefix, const char * pszSeparator) // case insensitive
//   {
//
//      return begins_eat_ci(property.m_var, lpcszPrefix, pszSeparator);
//
//   }
//
//
//
//} // namespace str
//
//
//inline static string log_level_name(::aura::log::e_level elevel)
//{
//   switch (elevel)
//   {
//   case trace_level_warning:
//      return "warning";
//   case trace_level_error:
//      return "error";
//   case trace_level_fatal:
//      return "fatal";
//   case trace_level_information:
//      return "info";
//   default:
//      return "undefined log error";
//   }
//}
//
//
//
//
//
//
///*
//inline dump_context & dump_context::operator<<(const string & str)
//{
//*this << static_cast< const char * >( str );
//return *this;
//}
//
//*/
//
//
