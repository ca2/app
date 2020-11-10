#pragma once


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D object :
   virtual public ::draw2d::object
   {
   public:
      
      
      object();
      virtual ~object();
      
      
      //virtual void * get_os_data() const;
      
      
      bool delete_object();
      
      
      i32 get_object(i32 nCount, LPVOID lpObject) const;
      ::u32 GetObjectType() const;
      bool CreateStockObject(i32 nIndex);
      bool UnrealizeObject();
      bool operator==(const ::draw2d::object& obj) const;
      bool operator!=(const ::draw2d::object& obj) const;
      
      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;
      
   };
   
   
} // namespace draw2d_quartz2d
