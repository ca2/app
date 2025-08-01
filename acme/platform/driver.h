//
// Created by camilo on 2025-07-10 00:49 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace acme
{


    class CLASS_DECL_ACME driver

    :
    virtual public ::particle
{
    public:


    int m_iWidth;
    int m_iHeight;

    long long m_lMemFreeAvailableKb;

    bool m_bRedraw;
    ::pointer_array<::message_box> m_messageboxa;

    ::pointer<::acme::asset_manager> m_passetmanager;

    ::pointer<::acme::asset> m_passetResourceFolder;

    string_array               m_straOpenUrl;

    ::string_array             m_straListFileEnumerate;



    driver();
    ~driver() override;


    static ::acme::driver *get();

    static void set(::acme::driver * pdriver);

    virtual void exchange1();

    virtual void after_exchange();


    virtual void
    queue_message_box(::message_box *pmessagebox);

    virtual ::pointer<::message_box> pick_message_box();

    virtual void open_url(const ::scoped_string & scopedstrOpenUrl);

    virtual void list_file_enumerate(const ::scoped_string & scopedstrListFileEnumerate);

};


} // namespace acme



