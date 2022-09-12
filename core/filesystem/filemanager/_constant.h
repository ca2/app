#pragma once


namespace filemanager
{


   enum enum_flag
   {

      e_flag_zip_compressed,
      e_flag_folder,
      e_flag_folder_ex001,
      e_flag_folder_ex001_calc,
      e_flag_has_sub_folder,
      e_flag_has_sub_folder_unknown

   };

   
   enum enum_attribute
   {

      e_attribute_name

   };


   enum EFolder
   {


      FolderMyComputer,


   };


   enum enum_operation
   {
      
      
      e_operation_none,
      e_operation_copy,
      e_operation_delete,
      e_operation_move,


   };


   enum enum_state
   {
      

      e_state_initial,
      e_state_start,
      e_state_step,
      e_state_finish,


   };


} // namespace filenamager


#define FILE_MANAGER_ID_FILE_NAME 1




#define FILEMANAGER_SHELL_COMMAND_FIRST 0x1000
#define FILEMANAGER_SHELL_COMMAND_LAST 0x2000


