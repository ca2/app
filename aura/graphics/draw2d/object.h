#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/collection/osdata_array.h"
//#include "acme/prototype/prototype/matter.h"


#define DRAW2D_OBJECT_TRANSFER(a) \
::draw2d::object(::transfer(a)), \
MATTER_TRANSFER(a)

//::osdata_array(::transfer(a)), \

namespace draw2d
{


   class CLASS_DECL_AURA object :
      virtual public ::matter//,
      //virtual public ::osdata_array
   {
   public:


      //void *         m_pthis;
      //void *         m_powner = nullptr; // in a normal usage/flow I can machine the object only if I am the owner, otherwise create another object
      //void *         m_osdata[8] = {};
      //bool           m_baCalculated[8] = {};
      ::f64_point       m_pointUserOffset;
      bool              m_bUpToDate;
      //::e_status     m_estatus;
      //::e_status     m_estatusLast;


      object();
      object(object && object);
      ~object() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void on_initialize_particle() override;
      void clear_node_data() override;
      
      //inline ::aura::system* system();


      //inline bool is_set(::collection::index iIndex) const { return m_baCalculated[0]; }
      //inline bool nok(::collection::index iIndex) const { return !is_set(iIndex); }
      //inline bool is_up_to_date(::collection::index iIndex) const { return is_set(iIndex); }
      //inline bool is_modified(::collection::index iIndex) const { return !is_up_to_date(iIndex); }


      virtual void defer_update(::draw2d::graphics * pdraw2dgraphics);
      //// void destroy_os_data() override;

      virtual void update(::draw2d::graphics * pdraw2dgraphics);
      void destroy() override;


      virtual void on_changed();

      virtual void set_modified();
      virtual bool is_modified() const;
      virtual bool is_up_to_date() const;

      //virtual void clear_os_data();
      


      //template < typename POINTER >
      //inline POINTER get_os_data(::draw2d::graphics * pdraw2dgraphics, ::i8 i = 0) const
      //{

      //   if (!m_baCalculated[i])
      //   {

      //      defer_update(pdraw2dgraphics, i);

      //   }

      //   return (POINTER) m_osdata[i];

      //}


      //inline void* get_os_data(::draw2d::graphics * pdraw2dgraphics, ::i8 i = 0) const
      //{

      //   return get_os_data < void * >(pdraw2dgraphics, i);

      //}



      //virtual ::u32 GetObjectType() const;
      //virtual bool CreateStockObject(::i32 nIndex);
      //virtual bool UnrealizeObject();
      //virtual bool operator==(const ::draw2d::object & obj) const;
      //virtual bool operator!=(const ::draw2d::object & obj) const;


   };


} // namespace draw2d



