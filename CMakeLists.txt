cmake_minimum_required(VERSION 3.10)
project(C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++11" ) # -fext-numeric-literals

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

set(SOURCE_FILES
        src/main.cpp
        src/Model.cpp
        src/Mesh.cpp
        src/Render.cpp
        src/Poseestimator.cu
        include/Model.h
        include/Mesh.h
        include/Render.h
        include/PoseParameters.h
        include/FileSystem.h
        )
set(HEADER_PATH include)

# boost
find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#SFML
#find_package(SFML REQUIRED system window graphics network audio)
#include_directories(${SFML_INCLUDE_DIR})

#GLEW
find_package(GLEW REQUIRED STATIC)
include_directories(${GLEW_INCLUDE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#SOIL
#find_package(SOIL REQUIRED)
#include_directories(${SOIL_INCLUDE_DIR})

#GLM
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

#OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#Eigen
find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3)
include_directories( ${EIGEN3_INCLUDE_DIRS})

#ImageMagick
find_package( ImageMagick COMPONENTS Magick++ MagickWand MagickCore REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})
link_directories(${ImageMagick_INCLUDE_DIRS})

#GLFW3
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# assimp
find_package(assimp REQUIRED)

# CUDA
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda-8.0)
find_package(CUDA QUIET REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -DDEBUG -G -Xcompiler -g -gencode=arch=compute_61,code=sm_61 --use_fast_math)
# preprocessor define: source directory
ADD_DEFINITIONS(-DTSDF_CUDA_SOURCE_DIR=${PROJECT_SOURCE_DIR})
# compile cuda stuff separately, mainly because of std++11, but also because of pcl which is incompatible
#CUDA_ADD_LIBRARY(CUDA src/CUDA.cu STATIC )
#cuda_add_executable(Test_C
#        src/CUDA.cu )

#SDFormat
find_package(SDFormat REQUIRED)
include_directories(${SDFormat_INCLUDE_DIRS})
link_directories(${SDFormat_LIBRARY_DIRS})

#PCL
find_package(PCL 1.7 REQUIRED COMPONENTS common io visualization)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


#add_executable(C ${SOURCE_FILES})
cuda_add_executable(C ${SOURCE_FILES})
include_directories(${HEADER_PATH})
target_link_libraries(C ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES} ${TARGET_LIB} ${SDFormat_LIBRARIES} ${CUDA_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLFW3_LIBRARY} ${ImageMagick_LIBRARIES} ${OpenCV_LIBS} ${GLM_LIBRARY} ${SOIL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${SFML_LIBRARIES} ${BOOST_LIBRARIES} boost_system boost_filesystem
        sfml-graphics sfml-window sfml-system SOIL glfw)
