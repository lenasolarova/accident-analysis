#!/bin/bash

cd "$(dirname "$0")"

#creating files, clearing them
touch c.out
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
    echo "1. c source code has been compiled";
fi
cd ..

#valgrind and timing (output other than time is in .out files)
echo "2. RESULTS in py.out and c.out files"
for opt in "${OPTIONS[@]}"; do
    echo "Option: $opt"

    #running valgrind (memory checks) of c code
    echo "  a. running memory checks by valgrind"
    cd src_c
    valgrind --leak-check=full ./$C_PROG "../dopravni_nehody_-1895066464895987623.csv" "$opt" >> ../c.out 2>&1

    #running time commands on both c and py code
    echo "  b. running time command on C code"
    { time ./$C_PROG "../dopravni_nehody_-1895066464895987623.csv" "$opt"; } >> ../c.out 2>&1
    cd ..

    cd src_py
    echo "  c. running time command on python code"
    { time python3 $PY_PROG --file="../dopravni_nehody_-1895066464895987623.csv" "$opt"; } >> ../py.out 2>&1
    cd ..
done

#tests
echo "3. running pytest"
pytest -v >> ../py.out 2>&1

#non-comment lines in of code in c files (.c and .h)
echo "4. C code lines (excluding comments):"
find src_c -type f \( -name "*.c" -o -name "*.h" \) -print0 | \
    xargs -0 grep -v '^\s*//' | grep -v '^\s*$' | wc -l

#non-comment lines od code in py files (.py)
echo "5. Python code lines (excluding comments):"
find src_py -type f -name "*.py" -print0 | \
    xargs -0 grep -v '^\s*#' | grep -v '^\s*$' | wc -l

