#pragma once


CLASS_DECL_ACME int_bool ensure_file_size_fd(int32_t fd, size_t iSize);
CLASS_DECL_ACME size_t get_file_size(int32_t fd);



CLASS_DECL_ACME int is_dir(const char * path1);




#ifdef __cplusplus

string file_first_line_dup(const ::string & strPath);

#endif