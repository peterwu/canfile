add_custom_target(
    angular_build
    COMMAND ng build --configuration production
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building Angular project in production mode..."
)

add_custom_target(
    copy_web_assets
    DEPENDS angular_build
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/dist/web/browser
        ${PROJECT_WEB_ASSETS_DIR}
    COMMENT
        "Copying built Angular assets to deployment folder."
)

add_custom_target (web
    DEPENDS copy_web_assets
)
