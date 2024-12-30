cmake_minimum_required(VERSION 3.21)

enable_testing()

############# Bitreader gtest
add_executable(bitreader_gtest bitreader_gtest.cpp bitwriter_gtest.cpp)
target_link_libraries(bitreader_gtest bitreadercpp)
target_link_libraries(bitreader_gtest GTest::gtest_main)
set_target_properties(bitreader_gtest PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
add_custom_command(TARGET bitreader_gtest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:bitreader_gtest> $<TARGET_RUNTIME_DLLS:bitreader_gtest>
        COMMAND_EXPAND_LISTS
      )
add_test(AllTestsBitreader bitreader_gtest)

############## Common gtest
add_executable(common_gtest
        shared_buffer_gtest.cpp
        memory_byte_source_gtest.cpp
        file_byte_source_gtest.cpp
        gtest_common_gtest.cpp
        gtest_common.hpp)

target_link_libraries(common_gtest bitreadercpp)
target_link_libraries(common_gtest GTest::gtest_main)
set_target_properties(common_gtest PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
add_custom_command(TARGET common_gtest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:common_gtest> $<TARGET_RUNTIME_DLLS:common_gtest>
        COMMAND_EXPAND_LISTS
      )

include(GoogleTest)
add_test(AllTestsCommon common_gtest)
