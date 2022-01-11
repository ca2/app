#pragma once


typedef CLASS_DECL_ACME __pointer_array(::matter) object_array;


namespace data
{


   typedef CLASS_DECL_ACME __pointer_array(listener) listener_array;
   typedef CLASS_DECL_ACME id_map < __pointer(data) > data_map;


   class CLASS_DECL_ACME data :
      virtual public ::object
   {
   protected:


      friend class ::data::data_container_base;

      __pointer(::data::data_container_base)     m_pdatacontainerbase;


   public:


      listener_array                               m_listenera;
      ::id                 m_id;


      data();
      ~data() override;


      virtual void dump(dump_context &) const override;
      void assert_valid() const override;


      virtual ::data::data_container_base* get_data_container();


      virtual ::count get_data_bound_view_count() const;
      virtual ::user::primitive * get_data_bound_view(index iInteraction);

      //void signal(::signal * psignal) override;
      void handle(::subject * psubject, ::context * pcontext) override;

      virtual void on_update_data(i32 iHint);


   protected:


      virtual void initialize_data(::data::data_container_base* pdocument);



   };


} // namespace data



