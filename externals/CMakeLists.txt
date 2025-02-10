add_subdirectory(glad/cmake)
glad_add_library(glad_gl_core_46
	LOADER
	API gl:core=4.6
	EXTENSIONS GL_NV_command_list
)

add_subdirectory(glfw)

add_subdirectory(glm)