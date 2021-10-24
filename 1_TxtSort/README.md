# TxtSort

Program for sorting text files

## Build

To build this project you have to install Tako's String Library and Tako's Logging Library
from HWHW/TSL and HWHW/Trace directories.
After that in HWHW/1_TxtSort:

```bash
mkdir build
cd build

cmake ..
cmake --build . -j`nproc`
```

## Usage

```bash
./onegin input_file [output_file]
```

`onegin` writes to `stdout` if output file not provided.

## Docs

To build documentation use `BUILD_DOC` option.
From build directory:

```bash
cmake -DBUILD_DOC=ON ..
cmake --build .
cd docs/latex
make -j`nproc`
```

after that open refman.pdf file.
