## Overview

`BinaryCode` is a small C++ library for working with binary linear codes. It provides data types and algorithms to construct generator matrices, convert to row-reduced echelon and systematic forms, build `BinaryCode` objects from generator matrices, and compute weight distributions.

## Key components

1. `BinaryCodeWord` — represents a binary codeword (bitset-like).
2. `BinaryCodeGenMat` — represents a binary generator matrix; supports element access, printing, RREF and systematic transformations.
3. `BinaryCode` — constructs a code from a generator matrix and exposes:
    1. code length and dimension,
    2. RREF and systematic forms,
    3. weight distribution queries,
    4. automorphism group computation (placeholder in current implementation).

## Build

1. Create a build directory and configure with CMake:
    - `mkdir build && cmake -S . -B build`
2. Build:
    - `cmake --build build`

The project uses CMake; the `BinaryCodeGenMat` dependency is expected to be available as a CMake target `BinaryCodeGenMat::binarycodegenmat` or provided as a subproject/fetchable external.

## Example

See `examples/bc_basic_usage.cpp` for a concise example that:
1. creates `BinaryCodeWord` instances,
2. builds a `BinaryCodeGenMat` and constructs `BinaryCode`,
3. prints length, dimension, RREF and systematic rows,
4. computes weight distributions for example generator matrices.

## Notes

1. The `compute_automorphism_group()` implementation is currently a placeholder.
2. If CMake errors report a missing CMake target `BinaryCodeGenMat::binarycodegenmat`, ensure the dependency is provided via `find_package`, `add_subdirectory`, or FetchContent before linking.