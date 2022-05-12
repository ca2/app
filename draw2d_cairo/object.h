#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO object :
      virtual public ::draw2d::object
   {
   public:


      object();
      virtual ~object();


      //virtual void * get_os_data() const;


      bool delete_object();


      i32 get_object(i32 nCount, void * lpObject) const;
      ::u32 GetObjectType() const override;
      bool CreateStockObject(i32 nIndex) override;
      bool UnrealizeObject() override;
      bool operator==(const object& obj) const;
      bool operator!=(const object& obj) const;

      void dump(dump_context & dumpcontext) const override;
      void assert_ok() const override;

   };


} // namespace draw2d_cairo
