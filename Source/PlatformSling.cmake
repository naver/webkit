set(WEBINSPECTORUI_DIR "${CMAKE_SOURCE_DIR}/Source/WebInspectorUI")

if (MSVC AND NOT ${CMAKE_GENERATOR} MATCHES "Ninja")
    set(WEB_INSPECTOR_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/WebKit.resources/WebInspectorUI)
else ()
    set(WEB_INSPECTOR_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WebKit.resources/WebInspectorUI)
endif ()

# DerivedSources/JavaScriptCore/inspector/InspectorBackendCommands.js is
# expected in DerivedSources/WebInspectorUI/UserInterface/Protocol/.
add_custom_command(
    OUTPUT ${DERIVED_SOURCES_WEBINSPECTORUI_DIR}/UserInterface/Protocol/InspectorBackendCommands.js
    DEPENDS ${DERIVED_SOURCES_JAVASCRIPTCORE_DIR}/inspector/InspectorBackendCommands.js
    COMMAND ${CMAKE_COMMAND} -E copy ${DERIVED_SOURCES_JAVASCRIPTCORE_DIR}/inspector/InspectorBackendCommands.js ${DERIVED_SOURCES_WEBINSPECTORUI_DIR}/UserInterface/Protocol/InspectorBackendCommands.js
)

add_custom_target(
    web-inspector-resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${WEBINSPECTORUI_DIR}/UserInterface ${WEB_INSPECTOR_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${DERIVED_SOURCES_WEBINSPECTORUI_DIR}/UserInterface/Protocol/InspectorBackendCommands.js ${WEB_INSPECTOR_DIR}/Protocol
    COMMAND ${CMAKE_COMMAND} -E copy ${WEBINSPECTORUI_DIR}/Localizations/en.lproj/localizedStrings.js ${WEB_INSPECTOR_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${WEBKIT2_DIR}/UIProcess/InspectorServer/front-end/inspectorPageIndex.html ${WEB_INSPECTOR_DIR}
    DEPENDS JavaScriptCore WebCore ${DERIVED_SOURCES_WEBINSPECTORUI_DIR}/UserInterface/Protocol/InspectorBackendCommands.js
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
