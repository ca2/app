#pragma once

class simple_toolbar;

namespace user
{

   class toolbar;

   class CLASS_DECL_CORE image_manager :
      virtual public ::object
   {
   public:


      ::pointer<::image::image_list>m_pimagelist;
      ::pointer<::image::image_list>m_pimagelistDisable;
      ///CBaseNumericDiscreteRelation < ::u32, ::u32, ::u32, ::u32 > m_rel;
      atom_map < int > m_rel;


      image_manager();
      virtual ~image_manager();

      //void LoadToolbar(toolbar & toolbar, ::u32 * user);
      //void LoadToolbar(simple_toolbar & toolbar, ::u32 * user);
      ::image::image_list & GetImageList();
      ::image::image_list & GetImageListDisable();
      bool Initialize(::particle * pparticle, ::u32 uaMenuV003Map[][2]);


   };


} // namespace user



