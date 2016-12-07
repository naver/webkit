add_definitions(-DNOMINMAX -DUNICODE -D_UNICODE -D_WINDOWS -DWINVER=0x601)

include_directories("${CMAKE_BINARY_DIR}/DerivedSources/ForwardingHeaders" "${CMAKE_BINARY_DIR}/DerivedSources")
if (${MSVC_CXX_ARCHITECTURE_ID} STREQUAL "X86")
    link_directories("${CMAKE_BINARY_DIR}/lib32" "${WEBKIT_LIBRARIES_DIR}/lib32")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin32)
else ()
    link_directories("${CMAKE_BINARY_DIR}/lib64" "${WEBKIT_LIBRARIES_DIR}/lib64")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib64)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin64)
endif ()

add_definitions(
    /wd4018 /wd4068 /wd4099 /wd4100 /wd4127 /wd4138 /wd4146 /wd4180 /wd4189
    /wd4201 /wd4244 /wd4251 /wd4267 /wd4275 /wd4288 /wd4291 /wd4305 /wd4309
    /wd4344 /wd4355 /wd4389 /wd4396 /wd4456 /wd4457 /wd4458 /wd4459 /wd4481
    /wd4503 /wd4505 /wd4510 /wd4512 /wd4530 /wd4610 /wd4611 /wd4702 /wd4706
    /wd4800 /wd4819 /wd4951 /wd4952 /wd4996 /wd6011 /wd6031 /wd6211 /wd6246
    /wd6255 /wd6387
)

# Create pdb files for debugging purposes, also for Release builds
add_compile_options(/Zi /GS)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")

# We do not use exceptions
add_definitions(-D_HAS_EXCEPTIONS=0)
add_compile_options(/EHa- /EHc- /EHs- /fp:except-)

# We have some very large object files that have to be linked
add_compile_options(/analyze- /bigobj)

# Use CRT security features
add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1)

# Turn off certain link features
add_compile_options(/Gy- /openmp- /GF-)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /OPT:NOREF /OPT:NOICF")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:NOREF /OPT:NOICF")

    # To debug linking time issues, uncomment the following three lines:
    #add_compile_options(/Bv)
    #set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /VERBOSE /VERBOSE:INCR /TIME")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /VERBOSE /VERBOSE:INCR /TIME")
elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_compile_options(/Oy-)
endif ()

if (NOT ${CMAKE_GENERATOR} MATCHES "Ninja")
    link_directories("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")
    add_definitions(/MP)
endif ()
if (NOT ${CMAKE_CXX_FLAGS} STREQUAL "")
    string(REGEX REPLACE "(/EH[a-z]+) " "\\1- " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable C++ exceptions
    string(REGEX REPLACE "/EHsc$" "/EHs- /EHc- " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable C++ exceptions
    string(REGEX REPLACE "/GR " "/GR- " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable RTTI
    string(REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Warnings are important
endif ()

foreach (flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    # Use the multithreaded static runtime library instead of the default DLL runtime.
    string(REGEX REPLACE "/MD" "/MD" ${flag_var} "${${flag_var}}")

    # No debug runtime, even in debug builds.
    if (NOT DEBUG_SUFFIX)
        string(REGEX REPLACE "/MDd" "/MD" ${flag_var} "${${flag_var}}")
        string(REGEX REPLACE "/D_DEBUG" "" ${flag_var} "${${flag_var}}")
    endif ()
endforeach ()

add_definitions(-DWIN32_POSIX -D_WINSOCKAPI_ -D__STDC_FORMAT_MACROS -DHAVE_STRUCT_TIMESPEC -DHAVE_PTHREAD_SETNAME_NP=1)

SET_AND_EXPOSE_TO_BUILD(ENABLE_ALLINONE_BUILD TRUE)
SET_AND_EXPOSE_TO_BUILD(ENABLE_CSP_NEXT TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_EXPORT_MACROS TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_SYSTEM_MALLOC TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_CAIRO_WINFONT TRUE)

SET_AND_EXPOSE_TO_BUILD(CAIRO_WIN32_STATIC_BUILD 1)
SET_AND_EXPOSE_TO_BUILD(CURL_STATICLIB 1)
SET_AND_EXPOSE_TO_BUILD(LIBXML_STATIC 1)
SET_AND_EXPOSE_TO_BUILD(LIBXSLT_STATIC 1)
SET_AND_EXPOSE_TO_BUILD(XMD_H 1)

set(ANGLE_INCLUDE_DIR ${WEBKIT_LIBRARIES_DIR}/include/ANGLE)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB")
set(WIN32_SYSTEM_LIBRARIES libcmt msvcrt msvcprt OLDNAMES Version vcruntime ucrt)

include_directories("${WEBKIT_LIBRARIES_DIR}/include/platforms" "${WEBKIT_LIBRARIES_DIR}/include/onig/androidsupport" "${WEBKIT_LIBRARIES_DIR}/include/onig/cxx")

macro(WEBKIT_CREATE_FORWARDING_HEADERS _framework)
    # On Windows, we copy the entire contents of forwarding headers.
    file(MAKE_DIRECTORY ${DERIVED_SOURCES_DIR}/ForwardingHeaders/${_framework})
    set(${_framework}_POST_BUILD_COMMAND "${CMAKE_BINARY_DIR}/DerivedSources/${_framework}/postBuild.cmd")
    foreach (_directory ${${_framework}_FORWARDING_HEADERS_DIRECTORIES})
        file(APPEND "${${_framework}_POST_BUILD_COMMAND}" "@xcopy /y /d /f \"${CMAKE_SOURCE_DIR}/Source/${_framework}/${_directory}/*.h\" \"${DERIVED_SOURCES_DIR}/ForwardingHeaders/${_framework}\" >nul 2>nul\n")
    endforeach ()
endmacro()

macro(ADD_PREFIX_HEADER _target _header)
    get_target_property(_old_compile_flags ${_target} COMPILE_FLAGS)
    if (${_old_compile_flags} STREQUAL "_old_compile_flags-NOTFOUND")
        set(_old_compile_flags "")
    endif ()
    set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "/FI\"${_header}\" ${_old_compile_flags}")
endmacro()

macro(GENERATE_WEBKIT_NATIVE_INTERFACE_SOURCES _output_source _input_files _level)
    find_source_target(${CMAKE_CURRENT_SOURCE_DIR})
    set(_target_directory "${DERIVED_SOURCES_DIR}/NativeInterfaces/${_FOUND_SOURCE_TARGET}")
    foreach (_file ${_input_files})
        get_filename_component(_name ${_file} NAME_WE)
        get_filename_component(_ext ${_file} EXT)
        get_filename_component(_absolute ${_file} ABSOLUTE)
        if (NOT "${_ext}" STREQUAL ".aidl")
            add_custom_command(
                OUTPUT ${_target_directory}/${_name}NativesBase.h ${_target_directory}/${_name}NativesStub.cpp
                       ${_target_directory}/${_name}ManagedBase.h ${_target_directory}/${_name}ManagedStub.cpp
                       ${_target_directory}/${_name}GeneratedExports.h
                MAIN_DEPENDENCY ${_file}
                DEPENDS ${ONIG_SCRIPTS_DIR}/interface-generator.py
                        ${ONIG_SCRIPTS_DIR}/lextab.py
                        ${ONIG_SCRIPTS_DIR}/parsetab.py
                COMMAND ${PYTHON_EXECUTABLE} ${ONIG_SCRIPTS_DIR}/interface-generator.py --java ${_absolute} --shared ${_target_directory} --cxx ${_target_directory}
                WORKING_DIRECTORY ${${_FOUND_SOURCE_TARGET}_DIR}
                VERBATIM)
            list(APPEND ${_output_source} ${_target_directory}/${_name}NativesStub.cpp ${_target_directory}/${_name}ManagedStub.cpp)
        endif ()
        get_property(WEBKIT_FRAMEWORK_${_level}_SOURCES GLOBAL PROPERTY WEBKIT_FRAMEWORK_${_level}_SOURCES)
        set_property(GLOBAL PROPERTY WEBKIT_FRAMEWORK_${_level}_SOURCES ${WEBKIT_FRAMEWORK_${_level}_SOURCES} ${_absolute})
    endforeach ()
    WEBKIT_WRAP_SOURCELIST(${_input_files})
endmacro()

macro(PROCESS_FRAMEWORK_LIBRARY_SOURCES _output_source _level)
    get_property(WEBKIT_FRAMEWORK_${_level}_SOURCES GLOBAL PROPERTY WEBKIT_FRAMEWORK_${_level}_SOURCES)
    set(_input_files "${WEBKIT_FRAMEWORK_${_level}_SOURCES}")
    foreach (_file ${_input_files})
        find_source_target(${_file})
        get_filename_component(_name ${_file} NAME_WE)
        get_filename_component(_directory ${_file} DIRECTORY)
        set(_target_source_file ${_directory}/${_name}.cpp)
        set(_target_header_file ${_directory}/${_name}.h)
        if (EXISTS ${_target_source_file})
            set(_no_export 0)
        else ()
            set(_no_export 1)
        endif ()
        if (NOT ${_no_export})
            set(_target_header_base ${DERIVED_SOURCES_DIR}/NativeInterfaces/${_FOUND_SOURCE_TARGET}/${_name}ManagedBase.h)
            set(_target_export_file ${DERIVED_SOURCES_DIR}/NativeInterfaces/${_FOUND_SOURCE_TARGET}/${_name}GeneratedExports.h)
            set(_output_header_file ${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}/${_name}.h)
            set(_output_header_base ${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}/${_name}ManagedBase.h)
            set(_output_export_file ${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}/${_name}GeneratedExports.h)
            add_custom_command(
                OUTPUT ${_target_header_base} ${_output_header_base} ${_output_header_file} ${_output_export_file}
                MAIN_DEPENDENCY ${_file}
                COMMAND @xcopy /y /d /f \"${_target_header_base}\" \"${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}\" >nul 2>nul\n
                COMMAND @xcopy /y /d /f \"${_target_header_file}\" \"${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}\" >nul 2>nul\n
                COMMAND @xcopy /y /d /f \"${_target_export_file}\" \"${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}\" >nul 2>nul\n
                )
            list(APPEND ${_output_source} ${_output_header_base} ${_output_header_file})
            if (NOT "${_level}" STREQUAL "INTERNAL")
                list(APPEND ${_output_source} ${_target_header_file} ${_target_source_file})
            endif ()
        endif ()
    endforeach ()
    WEBKIT_WRAP_SOURCELIST(${_input_files})
endmacro()

set(MEDIA_LIBRARY media)
set(OPENGL_LIBRARY opengl)
set(OS_LIBRARY os)
set(UTIL_LIBRARY util)
set(VIEW_LIBRARY view)
set(ONIG_LIBRARY onig)

set(ANGLE_LIBRARIES libEGL libGLESv2 libANGLE)
set(CAIRO_LIBRARIES cairo pixman)
set(CURL_LIBRARIES libcurl ssl crypto)
set(ICU_LIBRARIES icuin icuuc hyphenation)
set(IMAGE_LIBRARIES giflib jpeg png)
set(LIBXML_LIBRARIES xml2 xslt)
set(PLATFORM_LIBRARIES platforms winsock2 cutils liblog libdl)
set(PTHREAD_LIBRARIES pthread_np pthreadVC2)
set(SAFEINT_LIBRARIES safeint)
set(SQLITE_LIBRARIES sqlite)
set(ZLIB_LIBRARIES zlib)

set(WTF_SYSTEM_LIBRARIES winmm ${WIN32_SYSTEM_LIBRARIES})
set(WEBKIT_SYSTEM_LIBRARIES advapi32 atls comsuppw dwrite Iphlpapi odbc32 odbccp32 Psapi Shlwapi Userenv Usp10 Wldap32)

set(PORT Sling)
set(DEVELOPER_MODE 1)
set(JavaScriptCore_LIBRARY_TYPE SHARED)
set(WTF_LIBRARY_TYPE SHARED)
set(WebKit2_LIBRARY_TYPE STATIC)
