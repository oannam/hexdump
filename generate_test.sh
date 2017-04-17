#!/bin/bash

dd bs=$1 count=1 < /dev/urandom > $2
