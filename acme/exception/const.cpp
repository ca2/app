#include "framework.h"


namespace status
{


   string result::get_error_text(const ::e_status & estatus)
   {

      string strError;

      switch (estatus.m_estatus)
      {
      case error_failed:
         strError = "error_failed";
         break;
      case error_multiple:
         strError = "error_multiple";
         break;
      case error_exception:
         strError = "error_exception";
         break;
      case error_invalid_argument:
         strError = "error_invalid_argument";
         break;
      case error_io:
         strError = "error_io";
         break;
      case success:
         strError = "success";
         break;
      case success_multiple:
         strError = "success_multiple";
         break;
      default:

         if (::succeeded(estatus))
         {

            strError = "(unknown) success";

         }
         else
         {
            strError = "(unknown) error";

         }
      };

      strError += " (0x" + ::hex::lower_from(estatus.m_estatus) + ")";

      return strError;

   }


} // namespace status



