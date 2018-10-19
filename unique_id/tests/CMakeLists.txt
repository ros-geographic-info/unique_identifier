##############################################################################
# C++ Tests
##############################################################################

ament_add_gtest(test_${PROJECT_NAME}
                test_${PROJECT_NAME}.cpp
                second_test_${PROJECT_NAME}.cpp
)

target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})

##############################################################################
# Python Tests
##############################################################################

ament_add_nose_test(test_${PROJECT_NAME}.py ${CMAKE_CURRENT_SOURCE_DIR})