# Stack

Implementation of protected polymorphic stack.

## Build

From project dir:

```bash
mkdir build
cd build

cmake ..
cmake --build . -j`nproc`
```

## Usage

To use stack of concrete type you have to define it, and element print function at first.
For example:
```c++
define_stack(int);
void stk_print_elem(int)(const int *elem_ptr)
{
  printf("%d", *elem_ptr);
}
```

