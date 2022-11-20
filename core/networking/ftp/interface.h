#pragma once


//#include "acme/primitive/primitive/object.h"


namespace ftp
{


   class CLASS_DECL_CORE iinterface :
      virtual public object
   {
   protected:


      iinterface() {}
      virtual ~iinterface() {}


   private: // prevent copy action

      iinterface(const iinterface&);


      const iinterface& operator=(const iinterface&);

   };


} // namespace ftp



