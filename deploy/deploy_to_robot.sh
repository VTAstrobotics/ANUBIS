#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ANUBIS_DIR="$( dirname "$SCRIPT_DIR" )"   # parent of deploy

rsync -avz --delete "$ANUBIS_DIR" /