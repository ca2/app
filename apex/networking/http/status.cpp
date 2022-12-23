#include "framework.h"
//#include "acme/primitive/primitive/payload.h"
// #include "acme/primitive/string/string.h"


namespace http
{


//   bool succeeded(const ::e_status & estatus)
//   {
//
//      switch (estatus)
//      {
//      case status_ok:
//      case status_unchanged:
//         return true;
//      default:
//         break;
//      }
//
//      return false;
//
//   }


//   bool status_succeeded(i64 i)
//   {
//
//      return succeeded((void    ) i);
//
//   }
//

//   bool failed(const ::e_status & estatus)
//   {
//
//      return !succeeded(estatus);
//
//   }

//
//   bool status_failed(i64 i)
//   {
//
//      return !status_succeeded(i);
//
//   }

   CLASS_DECL_APEX string conn_status(property_set & set)
   {

      ::e_status      estatus = (::e_status)set["get_status"].as_i32();

      string str;

      if (estatus == ::success)
      {

         str = "OK: ";

      }
      else if (estatus == error_connection_timed_out)
      {

         str = "ERR: HTTP_CONNECTION_ERROR: connection timed out";

      }
      else if (estatus == error_on_connection_timeout)
      {

         str = "ERR: HTTP_CONNECTION_ERROR: ongoing connection timeout";

      }
      else if (estatus == ::success_none)
      {

         str = "ERR: HTTP_CONNECTION_ERROR: Unknown error, ";

      }
      else
      {

         str = "ERR: HTTP_CONNECTION_ERROR: ";

      }

      if (str.has_char())
      {

         str += ", ";

      }

      str += "HTTP_STATUS_CODE: " + set["get_attrs"]["http_status_code"];

      str += ", HTTP_STATUS: \"" + set["get_attrs"]["http_status"] + "\"";

      return str;

   }




} // namespace http
















