//
// Created by camilo on 2025-07-10 00:49 <3ThomasBorregaardSørensen!!
//
#pragma once

#include "acme/prototype/data/block.h"


namespace platform
{


    class CLASS_DECL_ACME application_sink :
       virtual public ::particle
   {
      public:


    int m_iWidth;
    int m_iHeight;

    long long m_lMemFreeAvailableKb;

    bool m_bRedraw;
       bool m_bSetApplicationReady;
    //::pointer_array<::message_box> m_messageboxa;

    ::pointer<::acme::asset_manager> m_passetmanager;

    ::pointer<::acme::asset> m_passetResourceFolder;

    string_array_base               m_straOpenUrl;

    ::string_array_base             m_straListFileEnumerate;

    //::data::block_array             m_datablockaMediaStore;

    ::pointer <::message_sink>      m_pmessagesink;
    ::pointer <::message_sink>      m_pmessagesinkMediaStore;


    application_sink();
    ~application_sink() override;


    static ::platform::application_sink *get();

    static void set(::platform::application_sink * papplicationsink);

    virtual void exchange1();

    virtual void after_exchange();

//    virtual void set_data(const ::scoped_string & scopedstrRelativeName,
//                            const ::scoped_string & scopedstrMimeType,
//                            const ::block & block);
//    virtual ::string get_data(const ::scoped_string & scopedstrRelativeName,
//                               const ::scoped_string & scopedstrMimeType,
//                               const class ::time & timeTimeout);

    virtual void post_message_box(::message_box *pmessagebox);

    //virtual ::pointer<::message_box> pick_message_box();

       //virtual ::pointer<::data::block> pick_media_store_operation();

       //virtual void defer_post_all_media_store_operations();

       //virtual void on_media_store_operation(::data::block * pdatablock);
       //virtual void on_write_input_output_data_block(::data::block * pdatablock);
       //virtual void on_read_input_output_data_block(::data::block * pdatablock);

    virtual void open_url(const ::scoped_string & scopedstrOpenUrl);

    virtual void list_file_enumerate(const ::scoped_string & scopedstrListFileEnumerate);
       //virtual ::file::path synchronously_getDocumentFolder(const class ::time & timeOut);

       //virtual ::pointer < ::data::block > media_store_set_data(const ::scoped_string & scopedstrPath, const ::block & block);
       //virtual ::pointer < ::data::block > media_store_get_data(const ::scoped_string & scopedstrPath);

       virtual void post_media_store_operation(::data::block * pdatablock);

       //virtual void on_main_task_iteration();

      virtual void context_on_size_changed();

      virtual ::message_sink * message_sink();

      virtual ::message_sink * media_store_message_sink();

    };


} // namespace platform



