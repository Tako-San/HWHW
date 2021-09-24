# TxtSort

Program for sorting text files

## Build

From project dir:

```bash
mkdir build
cd build

cmake ..
cmake --build . -j`nproc`
```

## Usage

```bash
./TxtSort input_file [output_file]
```

TxtSort writes to `stdout` if output file not provided.

