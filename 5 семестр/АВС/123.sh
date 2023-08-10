#!/bin/bash

echo "Date:     $(date)"
echo "Username: $(whoami)"
echo "Hostname: $(hostname)"


PROC_INFO=$(lscpu)
PROC_MODEL=$(echo "$PROC_INFO" | sed -n 's/^Model name: *\(.*\)/\1/p')
PROC_ARCH=$(echo "$PROC_INFO" | sed -n 's/^Architecture: *\(.*\)/\1/p')
PROC_FREQ=$(echo "$PROC_MODEL" | awk '{ print $NF }')
PROC_CORES=$(echo "$PROC_INFO" | sed -n 's/^CPU(s): *\(.*\)/\1/p')
PROC_THREADS_PER_CORE=$(echo "$PROC_INFO" | sed -n 's/^Thread(s) per core: *\(.*\)/\1/p')
echo
echo "CPU:"
echo "    MODEL:           " $PROC_MODEL
echo "    ARCHITECTURE:     $PROC_ARCH"
echo "    FREQUENCY:        $PROC_FREQ"
echo "    CORES:            $PROC_CORES"
echo "    THREADS PER CORE: $PROC_THREADS_PER_CORE"


RAM_INFO=$(free -h)
RAM_TOTAL=$(echo "$RAM_INFO" | awk '/^Mem:/ { print $2 }')
RAM_AVAIL=$(echo "$RAM_INFO" | awk '/^Mem:/ { print $NF }')
echo
echo "RAM:"
echo "    TOTAL:     $RAM_TOTAL"
echo "    AVAILABLE: $RAM_AVAIL"


HD_INFO=$(df -h | grep '/$')
HD_TOTAL=$(echo "$HD_INFO" | awk '{print $2}')
HD_AVAIL=$(echo "$HD_INFO" | awk '{print $4}')
HD_MOUNTED=$(echo "$HD_INFO" | awk '{print $1}')
HD_SWAP_TOTAL=$(echo "$RAM_INFO" | awk '/^Swap:/ { print $2 }')
HD_SWAP_AVAIL=$(echo "$RAM_INFO" | awk '/^Swap:/ { print $NF }')
echo
echo "FILESYSTEM:"
echo "    TOTAL:          $HD_TOTAL"
echo "    AVAILABLE:      $HD_AVAIL"
echo "    MOUNTED:        $HD_MOUNTED"
echo "    SWAP TOTAL:     $HD_SWAP_TOTAL"
echo "    SWAP AVAILABLE: $HD_SWAP_AVAIL"


echo
echo "INTERNET INTERFACES (name,ipv4,mac):"
# NET_INFO=$(lshw -c network 2> /dev/null)
NET_INFO=$(ifconfig)
INTERFACE_NAMES=$(echo "$NET_INFO" | awk '$1~/[^:]*?:/ {print $1}')
TEMP_FILE=$(mktemp)
for NAME in $INTERFACE_NAMES; do
    NAME=${NAME/:/}
    INTERFACE_INFO=$(ifconfig $NAME)
    IP=$(echo "$INTERFACE_INFO" | sed -n 's|inet \([0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\).*$|\1|p')
    MAC=$(echo "$INTERFACE_INFO" | sed -n -E 's|ether ([[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}).*$|\1|p')
    echo "$NAME, $IP, $MAC" >> $TEMP_FILE
done
column -t -s, $TEMP_FILE
rm $TEMP_FILE
