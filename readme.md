## UAI Programming Language

[![Test Status](https://github.com/KennedyTedesco/uai-lang/workflows/main/badge.svg)](https://github.com/KennedyTedesco/uai-lang/actions)

**_(A working in progress)._**

UAI is a C-like scripting language.

Goals of this project: 

- Learn C and memory;
- Learn how to write a compiler and a stack virtual machine to run bytecodes;
- It doesn't intend to be the safest implementation, as this requires a lot of c knowledge (and, you know, achieving a secure code with C is not that trivial).

TODO:

- [x] Lexer
- [ ] Parser
- [ ] Compiler (Bytecode generation)
- [ ] VM

Future scope:

- [ ] Unicode support for strings (a hard one :P)

### Compiling

This project uses [Meson](https://mesonbuild.com/Quick-guide.html) (CMake is good, but Meson, besides its powerful, is more friendly with newcomers).

So, the first thing you need to do after cloning this repo is:

```bash
$ meson builddir
```

It will generate the `buildir`, then you can run the tests:

```bash
$ meson test -C builddir/ -v 
```

Testing using Valgrind (a tool to find memory leaks):

```bash
$ meson test -C builddir/ -v --wrap='valgrind --leak-check=full'
```

### Contributing

Feel free to send pull requests and/or tips. =D
