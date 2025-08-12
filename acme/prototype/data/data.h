#pragma once


#include "acme/prototype/collection/atom_map_base.h"
////#include "acme/prototype/prototype/object.h"


namespace data
{


   typedef CLASS_DECL_ACME pointer_array < listener > listener_array;
   typedef CLASS_DECL_ACME atom_map_base < ::pointer<data >>data_map;


   class CLASS_DECL_ACME data :
      virtual public ::object
   {
   //protected:


   //   friend class ::data::data_container_base;

   //   ::pointer<::data::data_container_base>    m_pdatacontainerbase;


   public:


      listener_array                m_listenera;
      ::atom                        m_atomData;
      bool                          m_bNew;
      ::pointer < ::user::controller >          m_pusercontroller;


      data();
      ~data() override;


      // virtual void dump(dump_context &) const override;
      // void assert_ok() const override;


      ///virtual ::data::data_container_base* get_data_container();


      virtual ::collection::count get_data_bound_impact_count() const;
      virtual ::user::element * get_data_bound_impact(::collection::index iInteraction);

      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void on_update_data(int iHint);


      bool is_new_data() const;
   //protected:


      //virtual void initialize_data(::data::data_container_base* pdocument);

      
      virtual void initialize_data();


      virtual bool on_new_data();

      virtual void read_data(::binary_stream & binarystream, const ::scoped_string & scopedstrFormat);
      virtual void write_data(::binary_stream & binarystream, const ::scoped_string & scopedstrFormat);
      //virtual bool on_open_data(const ::payload & payloadFile);
      //virtual bool on_save_data(::file::file * pfile);


   };


} // namespace data



