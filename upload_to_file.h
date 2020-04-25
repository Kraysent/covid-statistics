#pragma once

#include <iostream>

#define UPLOAD_TO_FILE_2_ARGS(filename, globalSituationArray, field1, field2, delimeter, print_headers) \
{ \
    std::ofstream upload_to_file_variable_stream(filename); \
    if (print_headers == true) upload_to_file_variable_stream << #field1 << delimeter \
                                                              << #field2 << endl; \
    for (const auto& upload_to_file_variable_s : globalSituationArray) { \
        upload_to_file_variable_stream << upload_to_file_variable_s.field1 << delimeter \
                                       << upload_to_file_variable_s.field2 << endl; \
    } \
    upload_to_file_variable_stream.close(); \
}

#define UPLOAD_TO_FILE_3_ARGS(filename, globalSituationArray, field1, field2, field3, delimeter, print_headers) \
{ \
    std::ofstream upload_to_file_variable_stream(filename); \
    if (print_headers == true) upload_to_file_variable_stream << #field1 << delimeter \
                                                              << #field2 << delimeter \
                                                              << #field3 << endl; \
    for (const auto& upload_to_file_variable_s : globalSituationArray) { \
        upload_to_file_variable_stream << upload_to_file_variable_s.field1 << delimeter \
                                       << upload_to_file_variable_s.field2 << delimeter \
                                       << upload_to_file_variable_s.field3 << endl; \
    } \
    upload_to_file_variable_stream.close(); \
}

#define UPLOAD_TO_FILE_4_ARGS(filename, globalSituationArray, field1, field2, field3, field4, delimeter, print_headers) \
{ \
    std::ofstream upload_to_file_variable_stream(filename); \
    if (print_headers == true) upload_to_file_variable_stream << #field1 << delimeter \
                                                              << #field2 << delimeter \
                                                              << #field3 << delimeter \
                                                              << #field4 << endl; \
    for (const auto& upload_to_file_variable_s : globalSituationArray) { \
        upload_to_file_variable_stream << upload_to_file_variable_s.field1 << delimeter \
                                       << upload_to_file_variable_s.field2 << delimeter \
                                       << upload_to_file_variable_s.field3 << delimeter \
                                       << upload_to_file_variable_s.field4 << endl; \
    } \
    upload_to_file_variable_stream.close(); \
}

#define UPLOAD_TO_FILE_5_ARGS(filename, globalSituationArray, field1, field2, field3, field4, field5, delimeter, print_headers) \
{ \
    std::ofstream upload_to_file_variable_stream(filename); \
    if (print_headers == true) upload_to_file_variable_stream << #field1 << delimeter \
                                                              << #field2 << delimeter \
                                                              << #field3 << delimeter \
                                                              << #field4 << delimeter \
                                                              << #field5 << endl; \
    for (const auto& upload_to_file_variable_s : globalSituationArray) { \
        upload_to_file_variable_stream << upload_to_file_variable_s.field1 << delimeter \
                                       << upload_to_file_variable_s.field2 << delimeter \
                                       << upload_to_file_variable_s.field3 << delimeter \
                                       << upload_to_file_variable_s.field4 << delimeter \
                                       << upload_to_file_variable_s.field5 << endl; \
    } \
    upload_to_file_variable_stream.close(); \
}
