#!/bin/sh

libtoolize

# in a chroot env, -i may not work?
autoreconf
automake --add-missing
