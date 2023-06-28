// Created by camilo on 2023-06-27 23:21 <3ThomasBorregaardSorensen!!
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA placement_log_item
   {
   protected:

      friend class placement_log;


      class ::time            m_time;
      ::rectangle_i32         m_rectangle;


   };


   class CLASS_DECL_AURA placement_log :
      virtual public ::array < placement_log_item >
   {
   public:

      
      void on_initialize_particle() override;


      void add(const ::rectangle_i32& rectangle);
      bool has_recent(const ::rectangle_i32& rectangle);
      bool has_recent(const ::size_i32 & size);
      bool has_recent(const ::point_i32& point);
      void clean_recent();


   };


} // namespace windowing



