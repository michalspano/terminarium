#!/bin/sh

: '
This script is used to upload the code to the Wio Terminal board
and open the serial monitor. Further feature description can be found
here: https://git.chalmers.se/courses/dit113/2023/group-15/terminarium/-/issues/27
[internal issue #27]. Accessible to group members only.
The script is supposed to be run from the src directory:
    ./sh/terminarium.sh [port] [+options]
'

# Function to log the messages in a readable format
logger() {
    CYAN='\033[0;36m'; NC='\033[0m'     # colors
    echo "${CYAN}[$(date +%T)]${NC} $1" # print the message
}

# Function to show the usage of the script
usage() {
    echo "Usage: terminarium.sh [port] [+options]"
    echo "  port: the port where the Arduino board is connected to"
    echo "  options:"
    echo "    --list-ports, -lp: list all the available ports"
    echo "    --help, -h: show the usage"
    exit 0
}

# Define the port (passed as a parameter), the board (static), and the sketch (static)
PORT="$1"
BOARD="Seeeduino:samd:seeed_wio_terminal"
SRC_DIR="wio/terminarium"

# Show usage in case the user passes --help or -h or no arguments
# Should be checked before the arduino-cli is checked, so that the user can 
# see the usage even if the arduino-cli is not installed
if [[ "$1" == "--help" || "$1" == "-h" || "$#" -eq 0 ]]; then usage; fi

# Verify that the arduino-cli is installed
if ! command -v arduino-cli &> /dev/null; then
    echo "arduino-cli could not be found"; exit 1
fi

logger "Arduino CLI found"; sleep 0.5

# List current ports if the user passes --list-ports or -lp
# Arduino-cli is needed, hence the order of the if statements
if [[ "$1" == "--list-ports" || "$1" == "-lp" ]]; then
    arduino-cli board list; exit 0
fi

logger "Instantiating the upload process";  sleep 0.5
logger "Port selected: $PORT";              sleep 0.5
logger "Board selected: $BOARD";            sleep 0.5
logger "Sketch selected: $SRC_DIR";         sleep 0.5

arduino-cli upload -p "$PORT" --fqbn "$BOARD" "$SRC_DIR"

logger "Upload to the board completed";     sleep 0.5
logger "Opening serial monitor at $PORT";   sleep 0.5

# Sleep for one second to let the board boot up
# Then open the serial monitor
sleep 1; 
cat $PORT