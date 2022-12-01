#pragma once


namespace core
{


   template < class CORE_OBJECT >
   class core :
      virtual public CORE_OBJECT
   {
   public:


      inline ::core::application* get_app() const;
      inline ::core::session* get_session() const;
      inline ::core::system* acmesystem() const;
      inline ::core::user* user() const;



   };


} // namespace core





