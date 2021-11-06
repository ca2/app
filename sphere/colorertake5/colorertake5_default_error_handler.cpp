#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{

   DefaultErrorHandler::DefaultErrorHandler()
   {
   }

   DefaultErrorHandler::~DefaultErrorHandler()
   {
   }

   void DefaultErrorHandler::fatalError(const string &msg)
   {
      __UNREFERENCED_PARAMETER(msg);
   }

   void DefaultErrorHandler::error(const string &msg)
   {
      __UNREFERENCED_PARAMETER(msg);
   }

   void DefaultErrorHandler::warning(const string &msg)
   {
      __UNREFERENCED_PARAMETER(msg);
   }


} // namespace colorertake5
