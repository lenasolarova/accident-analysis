# Readme for the language comparison project

## Chosen languages
I have chosen to work with Python an C because of their vast differences - more on this topic is included in the **report** part of this project.

### Python
To run the python script, it is recommended to enter into a virtual environment,
there you can install the requirements using ```pip install -r requirements.txt``` and finally run the file using the CLI (see ```python main.py --help``` for all options). The options are:
* ```python main.py file="../dopravni_nehody_-1895066464895987623.csv" alcohol``` to print percentage of accidents directly caused by alcohol
* ```python main.py file="../dopravni_nehody_-1895066464895987623.csv" days``` to print percentage of accidents for all days of the week
* ```python main.py file="../dopravni_nehody_-1895066464895987623.csv" seatbelt``` to print a table intended to show a relationship between drivers under the influence who do not use a seatbelt and their resulting injury

### C
To run the C code, simply run it from the *src_c* directory using ```./main <path to csv file> <argument>```. You can again, find the arguments by running ```./main --help``` but the arguments are the same in both C and Python case:
* ```./main.py "../dopravni_nehody_-1895066464895987623.csv" alcohol```
* ```./main.py "../dopravni_nehody_-1895066464895987623.csv" days```
* ```./main.py "../dopravni_nehody_-1895066464895987623.csv" seatbelt```

## Comparison
To generate out files for both C and python code, you can run ```./comparison.sh``` which will compile the C code, run valgrind (memory checks) on it, run time command, tests and finally calculate number of lines of code. Similarly for python code, it will also run time command, run tests with pytest and calculate lines of code.