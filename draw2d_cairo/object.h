#pragma once


#include "aura/graphics/draw2d/object.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO object :
      virtual public ::draw2d::object
   {
   public:


      object();
      ~object() override;


      //virtual void * get_os_data() const;


      bool delete_object();


      int get_object(int nCount, void * lpObject) const;
//      unsigned int GetObjectType() const override;
//      bool CreateStockObject(int nIndex) override;
//      bool UnrealizeObject() override;
//      bool operator==(const object& obj) const;
//      bool operator!=(const object& obj) const;

      // void dump(dump_context & dumpcontext) const override;
      // void assert_ok() const override;

   };


} // namespace draw2d_cairo
