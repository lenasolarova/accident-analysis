# Readme for the language comparison project

## Chosen languages
I have chosen to work with Python an C because of their vast differences - more on this topic is included in the **report** part of this project.

### Python
To run the python script, it is recommended to enter into a virtual environment,
there you can install the requirements using ```pip install -r requirements.txt``` and finally run the file using the CLI (see ```python main.py --help``` for all options). The options are:
* ```python main.py alcohol``` to print percentage of accidents directly caused by alcohol
* ```python main.py days``` to print percentage of accidents for all days of the week
* ```python main.py seatbelt``` to print a table intended to show a relationship between drivers under the influence who do not use a seatbelt and their resulting injury

### C
To run the C code, simply run it using ```./main <argument>```. You can again, find the arguments by running ```./main --help``` but the arguments are the same in both C and Python case:
* ```./main.py alcohol```
* ```./main.py days```
* ```./main.py seatbelt```