// Created by camilo on 2023-06-27 23:21 <3ThomasBorregaardSorensen!!
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA placement_log_item
   {
   protected:

      friend class placement_log;


      class ::time            m_time;
      ::i32_rectangle         m_rectangle;


   };


   class CLASS_DECL_AURA placement_log :
      virtual public ::array < placement_log_item >
   {
   public:

      
      void on_initialize_particle() override;


      void add(const ::i32_rectangle& rectangle);
      bool has_recent(const ::i32_rectangle& rectangle);
      bool has_recent(const ::i32_size & size);
      bool has_recent(const ::i32_point& point);
      void clean_recent();


   };


} // namespace windowing



