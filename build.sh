set -e -u

cd `dirname $0`

# create library directories.
mkdir -p bin
mkdir -p lib

# build the libraries:
if [ `uname -s` = "Darwin" ]; then
    cc -o lib/libhost.dylib -dynamiclib -I"libhost" libhost/*_all.c libhost/*_posix.c
else
    cc -o lib/libhost.so -fPIC -shared  -I"libhost" libhost/*_all.c libhost/*_posix.c
fi

cc -c -I"libextend" -I"libhost" -I"libspec" libextend/*.c
ar cr lib/libextend.a *.o
rm *.o

cc -c -I"libextend" -I"libhost" -I"libspec" libspec/*.c
ar cr lib/libspec.a *.o
rm *.o