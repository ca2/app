#pragma once


#include "aura/graphics/draw2d/object.h"


namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE object :
      virtual public ::draw2d::object
   {
   public:

      
      object();
      virtual ~object();


      virtual void * get_os_data() const;


      bool delete_object();


      int get_object(int nCount, void * lpObject) const;
      unsigned int GetObjectType() const;
      bool CreateStockObject(int nIndex);
      bool UnrealizeObject();
      bool operator==(const ::draw2d::object& obj) const;
      bool operator!=(const ::draw2d::object& obj) const;

      // void dump(dump_context & dumpcontext) const override;
      // void assert_ok() const override;

   };


} // namespace aura



