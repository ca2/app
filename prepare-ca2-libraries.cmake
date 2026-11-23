function(ca2_add_library_preparation directory)
    file(RELATIVE_PATH relative_dir "${CMAKE_SOURCE_DIR}" "${directory}")
    if(relative_dir MATCHES "^(source|operating_system)(/|$)")
        get_property(targets DIRECTORY "${directory}" PROPERTY BUILDSYSTEM_TARGETS)
        foreach(target IN LISTS targets)
            get_target_property(type "${target}" TYPE)
            if(type MATCHES "^(STATIC|SHARED|MODULE|OBJECT)_LIBRARY$")
                # A project folder can own more than one library. Prepare it once per build.
                string(SHA256 directory_id "${relative_dir}")
                set(preparation "ca2_prepare_${directory_id}")
                if(NOT TARGET "${preparation}")
                    add_custom_target("${preparation}"
                        COMMAND "${CMAKE_COMMAND}"
                            "-DHELPER=${CA2_PREPARE_FOLDER_HELPER}"
                            "-DPROJECT_DIRECTORY=${directory}"
                            "-DPLATFORM=${CA2_PREPARE_FOLDER_PLATFORM}"
                            "-DCONFIGURATION=$<CONFIG>"
                            "-DLOCK_FILE=${CMAKE_BINARY_DIR}/ca2-prepare-folder.lock"
                            -P "${CA2_PREPARE_FOLDER_SCRIPT}"
                        WORKING_DIRECTORY "${directory}"
                        COMMENT "Preparing ${relative_dir}"
                        VERBATIM)
                endif()
                add_dependencies("${target}" "${preparation}")
            endif()
        endforeach()
    endif()

    get_property(children DIRECTORY "${directory}" PROPERTY SUBDIRECTORIES)
    foreach(child IN LISTS children)
        ca2_add_library_preparation("${child}")
    endforeach()
endfunction()

string(TOLOWER "${CMAKE_HOST_SYSTEM_PROCESSOR}" host_processor)
if(host_processor MATCHES "^(aarch64|arm64)$")
    set(helper_arch arm64)
else()
    set(helper_arch x64)
endif()
get_filename_component(legacy_helper_directory "${APPLICATION_BUILD_HELPER_BINARY}" DIRECTORY)
find_program(CA2_PREPARE_FOLDER_HELPER NAMES application_build_helper
    HINTS
        "${CMAKE_SOURCE_DIR}/operating_system/operating_system-windows/tool/bin/${helper_arch}"
        "${CMAKE_SOURCE_DIR}/tool/bin/${helper_arch}"
    PATHS "${legacy_helper_directory}" "${HOME_DIR}/code/operating_system/tool/bin/${helper_arch}"
    DOC "Windows application_build_helper used to prepare ca2 library folders")
if(NOT CA2_PREPARE_FOLDER_HELPER)
    message(FATAL_ERROR "application_build_helper was not found. Initialize the tool submodule, use tool/shell, or set CA2_PREPARE_FOLDER_HELPER.")
endif()
set(CA2_PREPARE_FOLDER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/run-prepare-folder.cmake")

string(TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" target_arch)
if(target_arch STREQUAL "arm64")
    set(CA2_PREPARE_FOLDER_PLATFORM ARM64)
elseif(target_arch MATCHES "^(x86|win32)$")
    set(CA2_PREPARE_FOLDER_PLATFORM Win32)
elseif(target_arch MATCHES "^(x64|amd64)$")
    set(CA2_PREPARE_FOLDER_PLATFORM x64)
else()
    set(CA2_PREPARE_FOLDER_PLATFORM "${PLATFORM_CONFIGURATION}")
endif()
