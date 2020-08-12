#pragma once

//
//namespace user
//{
//
//
//   class CLASS_DECL_AURA controller :
//      virtual public channel,
//      virtual public ::data::data_container_base
//   {
//   public:
//
//
//      bool                             m_bAutoDelete;     // TRUE => delete document when no more views
//      bool                             m_bEmbedded;       // TRUE => document is being created by OLE
//
//
//      controller();
//      virtual ~controller();
//
//
////      virtual ::stream & write(::stream & stream) const override;
////virtual ::stream & read(::stream & stream) override;
//
//      template < typename DATA >
//      __result(DATA) __create_data()
//      {
//
//         auto pdata = ::__create_new<DATA>();
//
//         if (!pdata)
//         {
//
//            return pdata;
//
//         }
//
//         auto estatus = pdata->initialize_data(this);
//         
//         if (!estatus)
//         {
//
//            return estatus;
//
//         }
//
//         return pdata;
//
//
//      }
//
//
//   };
//
//
// } // namespace user