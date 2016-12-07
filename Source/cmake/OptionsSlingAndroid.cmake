set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})

include_directories("${CMAKE_BINARY_DIR}/DerivedSources/ForwardingHeaders" "${CMAKE_BINARY_DIR}/DerivedSources")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Map,webkit.map")

add_definitions(-DHAVE_ANDROID_OS -D__STDINT_LIMITS -D__STDC_FORMAT_MACROS)

link_directories("${LIBRARY_OUTPUT_PATH}" "${WEBKIT_LIBRARIES_DIR}/libs/${ANDROID_NDK_ABI_NAME}")

SET_AND_EXPOSE_TO_BUILD(USE_FREETYPE TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_HARFBUZZ TRUE)

SET_AND_EXPOSE_TO_BUILD(CURL_STATICLIB 1)
SET_AND_EXPOSE_TO_BUILD(LIBXML_STATIC 1)
SET_AND_EXPOSE_TO_BUILD(LIBXSLT_STATIC 1)
SET_AND_EXPOSE_TO_BUILD(XMD_H 1)

set(ANGLE_INCLUDE_DIR "${THIRDPARTY_DIR}/ANGLE")

include_directories("${WEBKIT_LIBRARIES_DIR}/include/onig/androidjni" "${WEBKIT_LIBRARIES_DIR}/include/onig/androidsupport")

macro(ADD_PREFIX_HEADER _target _header)
    get_target_property(_old_compile_flags ${_target} COMPILE_FLAGS)
    if (${_old_compile_flags} STREQUAL "_old_compile_flags-NOTFOUND")
        set(_old_compile_flags "")
    endif ()
    set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "-include ${_header} ${_old_compile_flags}")
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
                       ${_target_directory}/${_name}GeneratedExports.h
                MAIN_DEPENDENCY ${_file}
                DEPENDS ${ONIG_SCRIPTS_DIR}/interface-generator.py
                        ${ONIG_SCRIPTS_DIR}/lextab.py
                        ${ONIG_SCRIPTS_DIR}/parsetab.py
                COMMAND ${PYTHON_EXECUTABLE} ${ONIG_SCRIPTS_DIR}/interface-generator.py --java ${_absolute} --shared ${_target_directory} --androidjni ${_target_directory}
                WORKING_DIRECTORY ${${_FOUND_SOURCE_TARGET}_DIR}
                VERBATIM)
            list(APPEND ${_output_source} ${_target_directory}/${_name}NativesStub.cpp)
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
        get_filename_component(_ext ${_file} EXT)
        set(_target_export_file ${DERIVED_SOURCES_DIR}/NativeInterfaces/${_FOUND_SOURCE_TARGET}/${_name}GeneratedExports.h)
        set(_output_export_file ${WEBKITLIB_LIBRARY_HEADERS_${_level}_DIR}/${_name}GeneratedExports.h)
        if (NOT "${_ext}" STREQUAL ".aidl")
            set(EXPORT_COMMAND cp -u ${_target_export_file} ${_output_export_file})
        else ()
            set(EXPORT_COMMAND echo // ${_file} > ${_output_export_file})
        endif ()
        add_custom_command(
            OUTPUT ${_output_export_file}
            MAIN_DEPENDENCY ${_file}
            COMMAND ${EXPORT_COMMAND}
            COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Tools/sling/copy-java.py ${_file} ${CMAKE_CURRENT_BINARY_DIR}/android/src
            )
    endforeach ()
    list(APPEND ${_output_source} ${_input_files})
    WEBKIT_WRAP_SOURCELIST(${_input_files})
endmacro()

set(ONIG_LIBRARY onig)

set(ANGLE_LIBRARIES EGL GLESv2)
set(CAIRO_LIBRARIES cairo pixman fontconfig freetype2 harfbuzz)
set(CURL_LIBRARIES curl ssl crypto)
set(ICU_LIBRARIES icuin icuuc icudt hyphenation)
set(IMAGE_LIBRARIES giflib jpeg-turbo png)
set(LIBXML_LIBRARIES xml2 xslt)
set(PLATFORM_LIBRARIES cutils)
set(PTHREAD_LIBRARIES pthread_np)
set(SAFEINT_LIBRARIES safeint)
set(SQLITE_LIBRARIES sqlite)
set(ZLIB_LIBRARIES z)

set(WTF_SYSTEM_LIBRARIES log dl)
set(WEBKIT_SYSTEM_LIBRARIES ${WTF_SYSTEM_LIBRARIES})

set(PORT Sling)
set(DEVELOPER_MODE 0)
set(JavaScriptCore_LIBRARY_TYPE STATIC)
set(WTF_LIBRARY_TYPE STATIC)
set(WebKit2_LIBRARY_TYPE SHARED)
