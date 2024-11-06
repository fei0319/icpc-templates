#!/bin/bash

tr -d '[:space:]' < "$1" | md5sum
