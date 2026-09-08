#!/bin/bash

# disable CPU scaling (get rid of warning thrown by google benchmark
sudo cpupower frequency-set --governor performance > /dev/null

build/apps/weighted_popcnt | tee output.txt

# enable CPU scaling again
sudo cpupower frequency-set --governor powersave > /dev/null

