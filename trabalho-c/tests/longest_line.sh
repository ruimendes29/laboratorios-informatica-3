#!/bin/bash

MAX_LINE=$(awk ' { if ( length > x ) { x = length; y = $0 } }END{ print y }' "$1")

echo "$MAX_LINE"

echo "$MAX_LINE" | wc
