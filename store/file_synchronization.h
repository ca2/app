// Created by camilo on 2023-03-15 03:21 <3ThomasBorregaardSorensen!!
#pragma once



namespace application_build_helper
{


   /// function(bUpdated,relative_path,target_len,source_len,target_modification_time,source_modification_time)


   class file_synchronization
   {
   public:


      bool                    m_bSynchronized = false;
      bool                    m_bTargetExists;
      //::filesize              m_filesizeTarget;
      //::filesize              m_filesizeSource;
      class ::time            m_timeModificationTarget;
      class ::time            m_timeModificationSource;
      //::string                m_strHashTarget;
      //::string                m_strHashSource;
      //::memory_pointer        m_pmemoryTarget;
      //::memory_pointer        m_pmemorySource;

      //bool up_to_date() const;

      /*inline static auto different_length_and_or_modification_time()
      {

         return [](file_needs_update* pfileneedsupdate)
         {

            if (pfileneedsupdate->m_timeModificationTarget != pfileneedsupdate->m_timeModificationSource)
            {

               return true;

            }

            if (pfileneedsupdate->m_filesizeTarget != pfileneedsupdate->m_filesizeSource)
            {

               return true;

            }

            return false;


         };

      }*/


      bool source_is_newer() const
      {

         if (!m_bTargetExists)
         {

            return true;

         }

         return m_timeModificationSource > m_timeModificationTarget;

      }


      inline static auto newer()
      {

         return [](const file_synchronization & filesynchronization)
         {

            return filesynchronization.source_is_newer();

         };

      }

      //inline static auto different_hash()
      //{

      //   return [](file_needs_update* pfileneedsupdate)
      //   {

      //      if (!pfileneedsupdate->m_strHashSource.case_insensitive_equals(pfileneedsupdate->m_strHashTarget))
      //      {

      //         return true;

      //      }

      //      return false;

      //   };

      //}

      //inline static auto different_contents()
      //{

      //   return [](file_needs_update* pfileneedsupdate)
      //   {

      //      if (!pfileneedsupdate->m_pmemorySource->order(*pfileneedsupdate->m_pmemoryTarget) != 0)
      //      {

      //         return true;

      //      }

      //      return false;

      //   };

      //}

      //inline static auto enough_different()
      //{

      //   return [](file_needs_update* pfileneedsupdate)
      //   {

      //      if (pfileneedsupdate->m_pmemorySource && pfileneedsupdate->m_pmemoryTarget)
      //      {

      //         return pfileneedsupdate->m_pmemorySource->order(*pfileneedsupdate->m_pmemoryTarget) != 0;

      //      }
      //      else if (pfileneedsupdate->m_strHashSource.has_character() && pfileneedsupdate->m_strHashTarget.has_character())
      //      {

      //         return !pfileneedsupdate->m_strHashSource.case_insensitive_equals(pfileneedsupdate->m_strHashTarget);

      //      }

      //      if (pfileneedsupdate->m_timeModificationTarget != pfileneedsupdate->m_timeModificationSource)
      //      {

      //         return true;

      //      }

      //      if (pfileneedsupdate->m_filesizeTarget != pfileneedsupdate->m_filesizeSource)
      //      {

      //         return true;

      //      }

      //      return false;

      //   };

      //}


   };


   using should_do_file_synchronization_function = ::function < bool(const file_synchronization&) >;

   using file_synchronization_function = ::function < void(const file_synchronization&) >;


} // namespace application_build_helper



