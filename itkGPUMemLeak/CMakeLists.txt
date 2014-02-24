cmake_minimum_required(VERSION 2.8)

project(itkGPUMemBug)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(gpuDiscreteGaussianImageFilter MACOSX_BUNDLE gpuDiscreteGaussianFilterTest.cxx)
target_link_libraries(gpuDiscreteGaussianImageFilter  ${ITK_LIBRARIES})
