#pragma once


namespace user
{


   class CLASS_DECL_CORE list_data :
      virtual public ::user::mesh_data
   {
   public:


      list_data();
      ~list_data() override;

   
      virtual count _001GetColumnCount(mesh * pmesh);


   };


} // namespace user



