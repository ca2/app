#pragma once


namespace sockets
{


   class CLASS_DECL_BASE sip_base :
      virtual public ::object
   {
   public:

      string new_guid();
      string new_branchid();
      string new_derived_branchid(
         const char * pszToTag,
         const char * pszFromTag);

   };


} // namespace sockets






