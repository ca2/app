#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/collection/osdata_array.h"
//#include "acme/prototype/prototype/matter.h"


namespace draw2d
{


   class CLASS_DECL_AURA object :
      virtual public ::matter,
      virtual public ::osdata_array
   {
   public:


      void *         m_pthis;
      //void *         m_powner = nullptr; // in a normal usage/flow I can machine the object only if I am the owner, otherwise create another object
      void *         m_osdata[8] = {};
      bool           m_baCalculated[8] = {};
      double_point      m_pointUserOffset;

      //::e_status     m_estatus;
      //::e_status     m_estatusLast;


      object();
      ~object() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void on_initialize_particle() override;
      
      
      //inline ::aura::system* system();


      inline bool is_set(::collection::index iIndex) const { return m_baCalculated[0]; }
      inline bool nok(::collection::index iIndex) const { return !is_set(iIndex); }
      inline bool is_up_to_date(::collection::index iIndex) const { return is_set(iIndex); }
      inline bool is_modified(::collection::index iIndex) const { return !is_up_to_date(iIndex); }


      virtual void defer_update(::draw2d::graphics * pgraphics, char i) const;
      void destroy_os_data() override;

      virtual void create(::draw2d::graphics * pgraphics, char iCreate);
      void destroy() override;

      inline void set_modified() 
      { 
         m_baCalculated[0] = false;
         m_baCalculated[1] = false;
         m_baCalculated[2] = false;
         m_baCalculated[3] = false;
         m_baCalculated[4] = false;
         m_baCalculated[5] = false;
         m_baCalculated[6] = false;
         m_baCalculated[7] = false;
      }


      inline void clear_os_data()
      {

         m_osdata[0] = nullptr;
         m_osdata[1] = nullptr;
         m_osdata[2] = nullptr;
         m_osdata[3] = nullptr;
         m_osdata[4] = nullptr;
         m_osdata[5] = nullptr;
         m_osdata[6] = nullptr;
         m_osdata[7] = nullptr;
         m_baCalculated[0] = false;
         m_baCalculated[1] = false;
         m_baCalculated[2] = false;
         m_baCalculated[3] = false;
         m_baCalculated[4] = false;
         m_baCalculated[5] = false;
         m_baCalculated[6] = false;
         m_baCalculated[7] = false;

      }


      template < typename POINTER >
      inline POINTER get_os_data(::draw2d::graphics* pgraphics, char i = 0) const
      {

         if (!m_baCalculated[i])
         {

            defer_update(pgraphics, i);

         }

         return (POINTER) m_osdata[i];

      }


      inline void* get_os_data(::draw2d::graphics* pgraphics, char i = 0) const
      {

         return get_os_data < void * >(pgraphics, i);

      }



      //virtual unsigned int GetObjectType() const;
      //virtual bool CreateStockObject(int nIndex);
      ///virtual bool UnrealizeObject();
      //virtual bool operator==(const ::draw2d::object & obj) const;
      //virtual bool operator!=(const ::draw2d::object & obj) const;


   };


} // namespace draw2d



