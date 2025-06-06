#pragma once


namespace user
{


   template < class CELL >
   class mesh_cache  :
      public mesh_cache_interface
   {
   public:


      bool                                   m_bCaching;
      int                                    m_iCacheNextIndex;
      ::int_map < ::int_map < CELL > >       m_map;


      mesh_cache();
      ~mesh_cache() override;


      void _001Invalidate();

      virtual void _001CacheHint(mesh * pmesh, ::collection::index iItemStart, ::collection::index iItemCount) override;

      virtual void _001GetItemText(::user::mesh_subitem * pitem);


   };


   template < class CELL >
   mesh_cache<CELL>::mesh_cache()
   {
      m_bCaching = false;
      m_iCacheNextIndex = 0;
   }
   template < class CELL >
   mesh_cache<CELL>::~mesh_cache()
   {

   }
   template < class CELL >
   void mesh_cache<CELL>::_001CacheHint(::user::mesh * pmesh, ::collection::index iItemStart, ::collection::index iItemCount)
   {

      //draw_mesh_item item(pmesh);

      //::collection::index i = 0;

      //for(item.m_iItem = iItemStart; i < iItemCount; i++,item.m_iItem++)
      //{

      //

      //}

   }


   template < class CELL >
   void mesh_cache<CELL>::_001GetItemText(::user::mesh_subitem * psubitem)
   {

      if(m_bCaching)
      {
         
         psubitem->m_bOk = false;

         return;

      }

      if(psubitem->m_pitem->m_iItem < 0)
      {
         
         psubitem->m_bOk = false;

         return;

      }

      {

         auto passoc = m_map.plookup(psubitem->m_pitem->m_iItem);

         if(passoc != nullptr)
         {

            auto passoc2 = passoc->element2().plookup(psubitem->m_pcolumn->m_iColumn);

            if(passoc2 != nullptr)
            {

               passoc2->element2().get_topic_text(psubitem->m_strText);

               psubitem->m_bOk = true;

               return;

            }

         }

      }

      //_001CacheHint(pitem->m_plist, pitem->m_item.m_iItem, 1);

      //{

      //   auto passoc = m_map.plookup(pitem->m_item.m_iItem);

      //   if(passoc != nullptr)
      //   {

      //      auto passoc2 = passoc->element2().plookup(pitem->m_item.m_iItem);

      //      if(passoc2 != nullptr)
      //      {

      //         pitem->m_strText = passoc2->element2();

      //         return_(pitem->m_bOk,true);

      //      }

      //   }

      //}

      psubitem->m_bOk = false;

      return;

   }


   template < class CELL >
   void mesh_cache<CELL>::_001Invalidate()
   {
      
      m_map.erase_all();

   }


} // namespace user



