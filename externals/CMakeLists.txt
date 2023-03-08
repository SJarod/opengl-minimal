# glad
add_subdirectory(glad/cmake)
# glad settings for opengl
glad_add_library(glad_gl_core_46
	LOADER
	API gl:core=4.6
	EXTENSIONS GL_NV_command_list
)

# glfw
add_subdirectory(glfw)