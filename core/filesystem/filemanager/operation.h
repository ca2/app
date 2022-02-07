#pragma once


namespace filemanager
{


   class operation:
      virtual public ::object
   {
   public:


      e_operation                m_eoperation;
      ::file::listing            m_stra;
      double_array               m_daRead;
      double_array               m_daSize;
      ::file::path               m_str;
      ::file::path               m_strBase;
      double                     m_dSize;
      double                     m_dRead;
      file_pointer               m_fileSrc;
      file_pointer               m_fileDst;
      i32                        m_iFile;
      bool                       m_bReplaceAll;
      char *                     m_pchBuffer;
      i32                        m_iBufferSize;
      ::user::interaction *      m_oswindowCallback;
      atom                         m_atom;
      wparam                     m_wparamCallback;


      operation();
      virtual ~operation();

      virtual bool set_copy(::file::listing & stra,const ::file::path & pszDestBase,const ::file::path & pszSrcBase,bool bExpand);
      virtual bool set_move(::file::listing & stra,const ::file::path & psz);
      virtual bool set_delete(::file::listing & stra);

      //   virtual double size();
      //   virtual double progress();

      i32 get_item_count();
      string get_item_message(i32 iItem);
      double get_item_progress(i32 iItem);
      double get_item_read(i32 iItem);
      double get_item_size(i32 iItem);

      void expand(::file::listing & straExpanded,::file::patha & straExpand);

      virtual void start();
      virtual bool step() override;
      virtual bool end();
      virtual bool make_duplicate_name(::file::path & str,const ::file::path & psz);


      void initialize(::object * pobject) override;
      virtual bool open_src_dst(const ::file::path & pszSrc,::file::path & strDst,const ::file::path & pszDir);

      virtual void set_operation(e_operation eoperation);
      virtual e_operation get_operation();

   };


} // namespace filemanager














