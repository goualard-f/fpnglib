# FPNGlib

The *Floating-Point Number Generator Library* is a small C library to generate and manipulate floating-point numbers with definite properties and constraints in the context of numerical software testing.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

The FPNGlib is built and tested on a Linux system with the GNU C Compiler. It should be compilable with minimal modifications on other platforms provided a sufficiently recent C compiler supporting
the ISO/IEC 9899:1999 (C99) standard is available.

### Installing

FPNGlib uses the autotools for configuration, compilation and deployment. The standard procedure is therefore:

```
./configure
make
make install
```

You may need to use `sudo` with `make install` since the default
installation directories are under `/usr/local/`.


## Running the tests

To test the library before installing it, just run `make check` from the base directory.


## Contributing

Please read [CONTRIBUTING.md]() for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **Frédéric Goualard** - *Initial work* - [goualard-f](https://gitlab.univ-nantes.fr/goualard-f)

See also the list of [contributors](https://gitlab.univ-nantes.fr/goualard-f/fpnglib/project_members) who participated in this project.

## License

This project is licensed under the GNU Lesser General Public License v. 3.0 - see the [.gnu-lgpl-v3.0.md](gnu-lgpl-v3.0.md) file for details
