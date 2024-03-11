// Created by camilo on 2024-03-10 22:00 <3ThomasBorregaardSorensen!!
#pragma once


namespace nanoui
{


   class Widget;
   class in_place_edit_mapper;


   class CLASS_DECL_NANOUI in_place_edit :
      virtual public ::particle
   {
   public:

      
      ::pointer < Widget >    m_pwidget;
      int                     m_iClickCount;
      bool                    m_bEdit;
      ::rectangle_f32         m_rectangleInternal;
      ::pointer < Widget >    m_pwidgetParent;


      bool is_clicked()
      {

         return m_iClickCount > 0;

      }


      in_place_edit();
      ~in_place_edit() override;

      
      virtual void on_end_edit();
      virtual void set_need_update();
      virtual void set_edit_payload(const ::payload& payload);
      virtual ::string get_name_for_editing() const;

      virtual ::rectangle_f32 get_outer_rectangle(in_place_edit_mapper* pmapper);


   };






} // namespace nanoui