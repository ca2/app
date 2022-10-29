#pragma once


#include "acme/primitive/collection/atom_map.h"
#include "acme/primitive/primitive/object.h"


namespace data
{


   typedef CLASS_DECL_ACME pointer_array < listener > listener_array;
   typedef CLASS_DECL_ACME atom_map < ::pointer<data >>data_map;


   class CLASS_DECL_ACME data :
      virtual public ::object
   {
   protected:


      friend class ::data::data_container_base;

      ::pointer<::data::data_container_base>    m_pdatacontainerbase;


   public:


      listener_array                               m_listenera;
      ::atom                 m_atom;


      data();
      ~data() override;


      virtual void dump(dump_context &) const override;
      // void assert_ok() const override;


      virtual ::data::data_container_base* get_data_container();


      virtual ::count get_data_bound_impact_count() const;
      virtual ::user::primitive * get_data_bound_impact(index iInteraction);

      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void on_update_data(i32 iHint);


   protected:


      virtual void initialize_data(::data::data_container_base* pdocument);



   };


} // namespace data



