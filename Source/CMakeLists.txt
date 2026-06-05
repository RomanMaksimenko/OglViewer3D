
add_executable(OGL3dViewer
    main.cpp )

target_include_directories(OGL3dViewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(OGL3dViewer PRIVATE Qt6::Core UI Controller Document Math Model)

# Добавим необходимые Qt dll рядом с исполняемым файлом
find_program(WINDEPLOYQT_BIN windeployqt6
    HINTS "${QT_BIN_DIR}"
)

if(WINDEPLOYQT_BIN)
    add_custom_command(TARGET OGL3dViewer POST_BUILD
        COMMAND "${WINDEPLOYQT_BIN}"
        --no-translations
        --compiler-runtime
        "$<TARGET_FILE:OGL3dViewer>"
    )
else()
 message(FATAL_ERROR "Could not find windeployqt6.exe in ${QT_BIN_DIR}")
endif()
