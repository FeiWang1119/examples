# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

project(sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(bubbleSort bubblesort.cpp)
add_executable(bucketSort bucketsort.cpp)
add_executable(heapSort heapsort.cpp)
add_executable(insertionSort insertionsort.cpp)
add_executable(mergeSort mergesort.cpp)
add_executable(quickSort quicksort.cpp)
add_executable(radixSort radixsort.cpp)
add_executable(selectionSort selectionsort.cpp)
