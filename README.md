# libspacetime: timekeeping beyond Earth

libspacetime is a cross-platform C library for date and time operations across multiple planets. while matching the current standards and specifications for date and time functions as best as possible. The goal was initially to be a library to support Thomas Gangale's proposed [Darian calendar for Mars](https://en.wikipedia.org/wiki/Darian_calendar), but in the future may expand to other proposed timekeeping systems.

# Building and Installation
## Requirements
To build, you will need:
- A C compiler
- The following standard C library functions:
  - `fmod` (for floating precision)
  - `memcpy`
  - `snprintf`
  - `strlen`
  - `strncasecmp`
  - `time`
- The following types:
  - `time_t`
  - `wchar_t`
- autoconf
- automake
- make
- libtool

For locale support:
- gettext

The following language pack bases if you wish to run the testsuite cases for testing different locales (optional):
- English (US)
- English (GB)
- Hungarian
- Lithuanian
- Spanish (ES)

## Configuration and Build
First, run `autogen.sh`:
```
./autogen.sh
```

Then run the resulting `configure` file.
```sh
./configure
```

You can pass the following flags to `configure`: the ones of note are:
- `--disable-docs`: Disable building documentation 
- `--disable-nls`: Disable National Language Support
- `--disable-programs`: Disable building programs 
- `--disable-tests`: Disable running tests 

Some systems will install to a different directory by default (such as /usr/local). You can replace the `PREFIX` by passing the flag to configure:

```sh
./configure --prefix=/usr
```

Build libspacetime:
```sh
make
```

Optionally, run the tests, if enabled in configure:
```sh
make check
```

## Installation
Install the library (you may need to run as root):
```sh
make install
```

If installing to a different prefix, make sure to clarify to make:
```sh
make PREFIX=/usr install
```

# Supported Systems
Ideally, libspacetime will be able to work on as many systems as possible.

However, there are some challenges to this, most notably the use of double-precision floats and large numbers for time calculations in relation to Earth time.

| Platform             | Status             |
| -------------------- | ------------------ |
| Linux i386           | Untested |
| Linux amd64 (glibc)  | :white_check_mark: |
| Linux amd64 (musl)   | :white_check_mark: |
| Linux arm64          | :white_check_mark: |
| Linux riscv64        | :white_check_mark: |
| macOS arm64          | :white_check_mark: |
| Windows              | Untested |


# Important Notes
- The Darian calendar is not "standard" by any means. The timekeeping method of MSD does appear to be used by NASA, but the calendar itself is not recognized officially. Same goes for any other "planetary systems".

- Library likely to change - see above. Also keep in mind that potentially the entire idea of timekeeping across planets, espeically if going past Mars, could perhaps be abstracted to any planet based on its orbit and length of day?

- Moving this into standards - it would be cool. A goal of libspacetime is to match standards as much as possible.

- Read the documentation for more general info, including AI usage and disclosure.
