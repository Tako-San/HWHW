# SqEq - square equation solver

## Build

From `0_SqEq` directory:

```bash
mkdir build
cd build
cmake ..
cmake --build . -j`nproc`
```

## Install

From build directory:
```bash
sudo cmake --install .
```

## Run

After installation:

```bash
SqEqSolver
# doing your stuff
```

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
