function(_setup_gcc_options target)
    target_compile_options(${target} PRIVATE
        # generic warnings
        "-W"
        "-Wall"
        "-Werror"
        "-Wextra"
        "-Wpedantic"
        # custom warnings
        "-Walloca"
        "-Wformat-security"
        "-Wshadow"
        "-Wvla"
        "-Wno-language-extension-token"
    )
endfunction()

function(_setup_clang_options target)
    target_compile_options(${target} PRIVATE
        # generic warnings
        "-W"
        "-Wall"
        "-Werror"
        "-Wextra"
        "-Wpedantic"
        # custom warnings
        "-Walloca"
        "-Wformat-security"
        "-Wshadow"
        "-Wvla"
        "-Wno-language-extension-token"
    )
endfunction()

function(_set_compilers_options target)
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		_set_msvc_options(${target} OPTIONS ${ARGN})
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        _set_gcc_options(${target} OPTIONS ${ARGN})
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		_setup_clang_options(${target} OPTIONS ${ARGN})
	else()
		message(FATAL_ERROR "unsupported compiler ${CMAKE_CXX_COMPILER_ID}")
	endif()
endfunction()
