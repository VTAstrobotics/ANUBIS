#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ANUBIS_DIR="$( dirname "$SCRIPT_DIR" )"   # parent of deploy

Dest_IP="$1"

if [ -z "$Dest_IP" ]; then
  echo "Usage: $0 user@host:/path"
  echo
  echo "Description:"
  echo "  user@host:/path  The SSH destination where the ANUBIS directory"
  echo "                   will be synced. Example:"
  echo "                   ./sync.sh rover@192.168.1.50"
  exit 1
fi



Dest="$Dest_IP":/Deployments/ANUBIS

ssh "$Dest_IP" "mkdir -p /Deployments/ANUBIS"

rsync -avz --delete "$ANUBIS_DIR/" "$Dest/"