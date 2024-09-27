#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/parallelization/synchronization_array.h"
#include "data.h"


namespace data
{


   class CLASS_DECL_ACME data_container :
      virtual public ::object
   {
   public:


      ::pointer<data>      m_spdata;


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
      ~data_container_base() override;


      void destroy() override;

      virtual bool set_data(const ::atom & atom, ::data::data * pdata);
      virtual bool add_data(::data::data * pdata);
      virtual bool erase_data(::data::data * pdata);
      virtual data * get_data(const ::atom & atom);
      virtual ::pointer < data > create_data(const ::atom & atom);
      virtual ::collection::count get_count() const;


      virtual bool is_empty() const;


      template < typename TYPE >
      TYPE * get_typed_data(::collection::index i = 0)
      {

        return m_datamap.get_typed_ptr < TYPE >();

      }


      template < typename TYPE >
      bool replace_data(const ::atom & atom, TYPE * pdata)
      {

         m_datamap.set(atom, pdata);

         return true;

      }


      virtual synchronization_array get_synca();


   };



} // namespace data



