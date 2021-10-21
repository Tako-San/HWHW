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

After building project do:

```bash
cd docs/latex
make -j`nproc`
```

and open refmain.pdf file.
