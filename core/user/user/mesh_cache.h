#pragma once


namespace user
{


   template < class CELL >
   class mesh_cache  :
      public mesh_cache_interface
   {
   public:


      bool                                  m_bCaching;
      i32                               m_iCacheNextIndex;
      ::i32_map < ::i32_map < CELL > >      m_map;


      mesh_cache();
      virtual ~mesh_cache();


      void _001Invalidate();

      virtual void _001CacheHint(mesh * pmesh, index iItemStart, index iItemCount) override;

      virtual void _001GetItemText(::user::mesh_item * pitem);


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
   void mesh_cache<CELL>::_001CacheHint(::user::mesh * pmesh,index iItemStart,index iItemCount)
   {

      //draw_mesh_item item(pmesh);

      //index i = 0;

      //for(item.m_iItem = iItemStart; i < iItemCount; i++,item.m_iItem++)
      //{

      //

      //}

   }


   template < class CELL >
   void mesh_cache<CELL>::_001GetItemText(::user::mesh_item * pitem)
   {

      if(m_bCaching)
      {
         
         pitem->m_bOk = false;

         return;

      }

      if(pitem->m_iItem < 0)
      {
         
         pitem->m_bOk = false;

         return;

      }

      {

         auto passoc = m_map.plookup(pitem->m_iItem);

         if(passoc != nullptr)
         {

            auto passoc2 = passoc->element2().plookup(pitem->m_iColumn);

            if(passoc2 != nullptr)
            {

               passoc2->element2().get_topic_text(pitem->m_strText);

               pitem->m_bOk = true;

               return;

            }

         }

      }

      //_001CacheHint(pitem->m_plist, pitem->m_iItem, 1);

      //{

      //   auto passoc = m_map.plookup(pitem->m_iItem);

      //   if(passoc != nullptr)
      //   {

      //      auto passoc2 = passoc->element2().plookup(pitem->m_iItem);

      //      if(passoc2 != nullptr)
      //      {

      //         pitem->m_strText = passoc2->element2();

      //         return_(pitem->m_bOk,true);

      //      }

      //   }

      //}

      pitem->m_bOk = false;

      return;

   }


   template < class CELL >
   void mesh_cache<CELL>::_001Invalidate()
   {
      
      m_map.remove_all();

   }


} // namespace user



