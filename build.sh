set -e -u

cd `dirname $0`

# directories.
mkdir -p bin
mkdir -p lib

# libhost.so.
if [ `uname -s` = "Darwin" ]; then
    cc -o lib/libhost.dylib -dynamiclib -I"libhost" libhost/*_all.c libhost/*_posix.c
else
    cc -o lib/libhost.so -fPIC -shared  -I"libhost" libhost/*_all.c libhost/*_posix.c
fi

# libextend.a.
cc -c -I"libextend" -I"libhost" -I"libspec" libextend/*.c
ar cr lib/libextend.a *.o
rm *.o

# libsepc.a.
cc -c -I"libextend" -I"libhost" -I"libspec" libspec/*.c
ar cr lib/libspec.a *.o
rm *.o
