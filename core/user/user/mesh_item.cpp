// From mesh.cpp by camilo on 2022-06-29 05:35 <3ThomasBorregaardSorensen!! ThomasLikesNumber5
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "core/user/user/_component.h"
#endif
#include "mesh_item.h"



namespace user
{


   mesh_subitem::mesh_subitem()
   {

      m_bOk = false;

      m_pdrawmeshsubitem = nullptr;
      m_plistsubitem = nullptr;
      m_pdrawlistsubitem = nullptr;

      m_iSubItem = -1;
      m_iImage = -1;

      //m_bRectangle = false;

   }


   void mesh_subitem::initialize_mesh_subitem(mesh_item * pmeshitem)
   {

      m_pitem = pmeshitem;

   }


   draw_mesh_subitem::draw_mesh_subitem()
   {

      m_pdrawmeshsubitem = this;
      m_iRectangleOrder = -1;

   }


   void draw_mesh_subitem::initialize_draw_mesh_subitem(mesh_item * pmeshitem)
   {

      initialize_mesh_subitem(pmeshitem);

   }


   mesh_item::mesh_item()
   {

      m_pdrawmeshitem = nullptr;
      m_plistitem = nullptr;
      m_pdrawlistitem = nullptr;

      //m_iGroup = -1;
      m_iItem = -1;
      m_iDisplayItem = -1;
      //m_iColumn         = -1;
      //m_iOrder = -1;
      //m_iSubItem        = -1;
      //m_iListItem       = -1;
      //m_colorText = __indexed_color(-1);
      //m_colorTextBackground = argb(255, 0, 0, 0);
      //m_colorItemBackground = ::color::transparent;
      m_iState = -1;
      //m_iImage = -1;
      m_bOk = false;

      m_iGroupTopDisplayIndex = -1;
      m_iGroupCount = -1;

   }


   void mesh_item::initialize_mesh_item(mesh * pmesh)
   {

      m_pmesh = pmesh;

   }


   draw_mesh_item::draw_mesh_item()
   {

      m_pdrawmeshitem = this;

      m_prectClient = nullptr;

      //m_iColumn = -1;
      m_iColumnWidth = 0;

      m_iRectangleDisplayItem = -1;

      //m_iSubItemRectItem         = -1;
      //m_iSubItemRectSubItem      = -1;
      //m_iSubItemRectOrder        = -1;
      //m_iSubItemRectColumn       = -1;

      //m_iListItemRectItem        = -1;
      //m_iListItemRectSubItem     = -1;
      //m_iListItemRectListItem    = -1;

      //m_bRectangle = false;

   }


   void draw_mesh_item::initialize_draw_mesh_item(mesh * pmesh)
   {

      initialize_mesh_item(pmesh);

   }


   ::pointer<::image_list>draw_mesh_subitem::get_image_list()
   {
      //if(m_bListItemHover && m_pcolumn->m_pimagelistHover != nullptr)
      //if(m_bListItemHover)
      //{
      //   return m_pcolumn->m_pimagelistHover;
      //}
      //else
      //{
      //   return m_pcolumn->m_pimagelist;
      //}

      return nullptr;

   }


   mesh_group::mesh_group()
   {


   }


   draw_mesh_group::draw_mesh_group()
   {


   }


   void draw_mesh_group::initialize_draw_mesh_group(mesh * pmesh)
   {



   }


   //::pointer<::image_list>get_image_list();
   //bool draw_image();
   void draw_mesh_group::draw_group_image()
   {


   }


   void draw_mesh_group::update_group_color()
   {


   }


   void draw_mesh_group::set_text_color()
   {


   }


   void draw_mesh_group::draw_text()
   {


   }



} // namespace user



