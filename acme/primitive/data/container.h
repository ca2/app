#pragma once


namespace data
{


   class CLASS_DECL_ACME data_container :
      virtual public ::object
   {
   public:


      __pointer(data)       m_spdata;


      data_container();
      virtual ~data_container();


      virtual bool set_data(::data::data * pdata);
      data * get_data();

      virtual bool is_data_locked() const;

      virtual void on_update_data(i32 iHint);

   };


   class CLASS_DECL_ACME data_container_base :
      virtual public ::object
   {
   public:


      data_map       m_datamap;


      data_container_base();
      virtual ~data_container_base();


      bool set_data(const ::id & id, ::data::data * pdata);
      bool add_data(::data::data * pdata);
      bool erase_data(::data::data * pdata);
      data * get_data(const ::id & id);
      ::count get_count() const;


      bool is_empty() const;


      template < typename TYPE >
      TYPE * get_typed_data(index i = 0)
      {

        return m_datamap.get_typed_ptr < TYPE >();

      }


      template < class TYPE >
      bool replace_data(const ::id & id, TYPE * pdata)
      {

         m_datamap.set(id, pdata);

         return true;

      }


      synchronization_array get_synca();


   };



} // namespace data



