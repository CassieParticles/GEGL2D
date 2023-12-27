list(APPEND ENGINESOURCES "Engine/Animation.cpp" "Engine/Animation.h")		#Add the source files to a list
list(APPEND ENGINESOURCES "Engine/BaseLevel.cpp" "Engine/BaseLevel.h")
list(APPEND ENGINESOURCES "Engine/Collision.cpp" "Engine/Collision.h")
list(APPEND ENGINESOURCES "Engine/FileManager.cpp" "Engine/FileManager.h")
list(APPEND ENGINESOURCES "Engine/Input.cpp" "Engine/Input.h")
list(APPEND ENGINESOURCES "Engine/LevelManager.cpp" "Engine/LevelManager.h")
list(APPEND ENGINESOURCES "Engine/MathsFunctions.cpp" "Engine/MathsFunctions.h")
list(APPEND ENGINESOURCES "Engine/Program.cpp" "Engine/Program.h")
list(APPEND ENGINESOURCES "Engine/TextureManager.cpp" "Engine/TextureManager.h")
list(APPEND ENGINESOURCES "Engine/Timer.cpp" "Engine/Timer.h")
list(APPEND ENGINESOURCES "Engine/Window.cpp" "Engine/Window.h")

list(APPEND ENGINESOURCES "Engine/GameObjects/GameObjects.h")	#Add the game obejcts to the ENGINESOURCES
list(APPEND ENGINESOURCES "Engine/GameObjects/TextureSquare.cpp")

list(APPEND GUISOURCES "Engine/GUI.h")											#Add the files for the GUI		
list(APPEND GUISOURCES "Engine/GUIFD.h")
list(APPEND GUISOURCES "Engine/GUI/Font.cpp" "Engine/GUI/Font.h")
list(APPEND GUISOURCES "Engine/GUI/GUIBase.cpp" "Engine/GUI/GUIBase.h")					
list(APPEND GUISOURCES "Engine/GUI/GUIButton.cpp" "Engine/GUI/GUIButton.h")
list(APPEND GUISOURCES "Engine/GUI/GUIColourRect.cpp" "Engine/GUI/GUIColourRect.h")
list(APPEND GUISOURCES "Engine/GUI/GUIManager.cpp" "Engine/GUI/GUIManager.h")		
list(APPEND GUISOURCES "Engine/GUI/GUIText.cpp" "Engine/GUI/GUIText.h")
list(APPEND GUISOURCES "Engine/GUI/GUITextBox.cpp" "Engine/GUI/GUITextBox.h")
list(APPEND GUISOURCES "Engine/GUI/GUITextureRect.cpp" "Engine/GUI/GUITextureRect.h")
list(APPEND GUISOURCES "Engine/GUI/GUIToggleButton.cpp" "Engine/GUI/GUIToggleButton.h")


add_library(GEGL2D ${ENGINESOURCES} ${GUISOURCES})

target_include_directories(GEGL2D PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

#Add all the header files needed
target_include_directories(GEGL2D PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/bin/includes")	

#Add GLFW library (compiled .lib file)
add_library(GLFW STATIC IMPORTED GLOBAL)
set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/bin/GLFW/lib/glfw3.lib")

#Add FreeType library (compiled .lib file)
add_library(FreeType STATIC IMPORTED GLOBAL)
set_property(TARGET FreeType PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/bin/FreeType/freetyped.lib")

#Add GLAD library (uncompiled .c file)
add_library(GLAD "${CMAKE_CURRENT_LIST_DIR}/bin/GLAD/src/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_CURRENT_LIST_DIR}/bin/includes")

#add OpenAL libraries
add_library(OpenAL STATIC IMPORTED GLOBAL)
set_property(TARGET OpenAL PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/bin/OpenAL/common.lib")
set_property(TARGET OpenAL PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/bin/OpenAL/ex-common.lib")
set_property(TARGET OpenAL PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/bin/OpenAL/OpenAL32.lib")


target_link_libraries(GEGL2D GLFW)
target_link_libraries(GEGL2D GLAD)
target_link_libraries(GEGL2D FreeType)
target_link_libraries(GEGL2D OpenAL)

#Add GLM files (not compiled as a library cause it's all header files)
target_include_directories(GEGL2D PUBLIC "${CMAKE_CURRENT_LIST_DIR}/bin/glm")

add_custom_target(copyEngineShaders ALL 
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/Engine/Shaders" "${CMAKE_BINARY_DIR}/Engine/Shaders"
COMMENT "Copy engine shaders to output file" VERBATIM)


add_custom_target(copySaveFiles ALL 
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/saves" "${CMAKE_BINARY_DIR}/saves"	#Copy directory		
COMMAND ${CMAKE_COMMAND} -E rm "${CMAKE_BINARY_DIR}/saves/savesInstructions.txt"					#Delete text file instructions
COMMENT "Copy save file structure to output file" VERBATIM											#Comment
)

add_dependencies(GEGL2D copyEngineShaders)
add_dependencies(GEGL2D copySaveFiles)