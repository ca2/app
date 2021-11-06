#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA object :
      virtual public ::material_object,
      virtual public ::osdata_array
   {
   public:


      void *         m_pthis;
      bool           m_bUpdated2;
      void *         m_powner; // in a normal usage/flow I can machine the object only if I am the owner, otherwise create another object
      void *         m_osdata[8];


      object();
      ~object() override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      
      //inline ::aura::application* get_application();
      //inline ::aura::session* get_session();
      inline ::aura::system* get_system();


      inline bool is_set() const { return m_osdata[0] != nullptr; }
      inline bool nok() const { return !is_set(); }
      inline bool is_up_to_date() const { return is_set() && m_bUpdated2; }
      inline bool is_modified() const { return !is_up_to_date(); }


      virtual void defer_update(::draw2d::graphics * pgraphics, ::i8 i) const;
      virtual ::e_status destroy_os_data();

      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate);
      ::e_status destroy() override;

      inline void set_modified() { m_bUpdated2 = false; }

      inline void set_updated() { m_bUpdated2 = true; }

      
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

      }


      template < typename POINTER >
      inline POINTER get_os_data(::draw2d::graphics* pgraphics, ::i8 i = 0) const
      {

         if (!m_bUpdated2 || !m_osdata[i])
         {

            defer_update(pgraphics, i);

         }

         return (POINTER) m_osdata[i];

      }


      inline void* get_os_data(::draw2d::graphics* pgraphics, ::i8 i = 0) const
      {

         return get_os_data < void * >(pgraphics, i);

      }



      virtual ::u32 GetObjectType() const;
      virtual bool CreateStockObject(i32 nIndex);
      virtual bool UnrealizeObject();
      virtual bool operator==(const ::draw2d::object & obj) const;
      virtual bool operator!=(const ::draw2d::object & obj) const;


   };


} // namespace draw2d



