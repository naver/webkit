list(APPEND JavaScriptCore_INCLUDE_DIRECTORIES
    "${WTF_DIR}"
    "${WTF_DIR}/wtf/sling"
)

set(JavaScriptCore_LIBRARIES
    PUBLIC ${JavaScriptCore_LIBRARIES}
)

list(APPEND JavaScriptCore_LIBRARIES
    PRIVATE ${PTHREAD_LIBRARIES}
    PRIVATE ${WTF_SYSTEM_LIBRARIES}
)
