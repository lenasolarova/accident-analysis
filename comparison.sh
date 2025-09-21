#!/bin/bash

cd "$(dirname "$0")"

#creating files, clearing them
tocuh c.out
touch py.out

> c.out
> py.out

C_PROG="main"
C_SRC="*.c"
PY_PROG="main.py"

OPTIONS=("alcohol" "days" "seatbelt")

#compilation
cd src_c
if gcc $C_SRC -o $C_PROG; then
    echo "c source code has been compiled";
fi
cd ..

#valgrind and timing (output other than time is in .out files)
for opt in "${OPTIONS[@]}"; do
    echo "Option: $opt"

    #running valgrind (memory checks) of c code
    cd src_c
    echo "valgrind taking its time - results in c.out"
    valgrind --leak-check=full ./$C_PROG "$opt" >> ../c.out 2>&1

    #running time commands on both c and py code
    echo "time spent in c execution"
    time ./$C_PROG "$opt" >> ../c.out 2>&1
    cd ..

    cd src_py
    echo "time spent in python execution"
    time python3 $PY_PROG "$opt" >> ../py.out 2>&1
    cd ..
done

#non-comment lines in of code in c files (.c and .h)
echo "C code lines (excluding comments):"
find src_c -type f \( -name "*.c" -o -name "*.h" \) -print0 | \
    xargs -0 grep -v '^\s*//' | grep -v '^\s*$' | wc -l

#non-comment lines od code in py files (.py)
echo "Python code lines (excluding comments):"
find src_py -type f -name "*.py" -print0 | \
    xargs -0 grep -v '^\s*#' | grep -v '^\s*$' | wc -l

