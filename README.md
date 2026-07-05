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

If you wish to build without NLS:
```sh
./configure --disable-nls
```

Some systems will install to a different directory by default (such as /usr/local). You can replace the `PREFIX` by passing the flag to configure:

```sh
./configure --prefix=/usr
```

Build libspacetime:
```sh
make
```

Optionally, run the tests:
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
- C standards - A lot of my work has been looking at existing implementations for [time and date functions in C](https://en.wikipedia.org/wiki/C_date_and_time_functions), and those were built upon standards. I currently lack the skills for timekeeping in general, and I knew nothing about POSIX.1 or ISO C standards before this. **I am currently just doing one function and operation at a time, and I cannot promise "similarity" to any standards. For example, glibc seems to do calculations for date and time under internal "timezone", but, as of writing, I am not there yet. Naming conventions may also differ. I would spend too much time worrying about trying to make things match as seamlessly to existing standards at this stage, that it is not worth it. So I am taking this as a learning process and will adjust things later.
- Library likely to change - see above. Also keep in mind that potentially the entire idea of timekeeping across planets, espeically if I go past Mars, could possibly be abstracted to like, any planet based on its orbit and length of day? Maybe this will end up being a "make your own planetary timekeeping" library. (Honestly, I hope not)
- Moving this into standards - I mean, it would be cool. I'll eventually come around to matching standards as best as possible, then maybe a proposal can be submitted? I don't know anything about the process.
