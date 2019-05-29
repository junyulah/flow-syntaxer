#!/bin/bash

cd `dirname $0`
cd ..

PROJECT_NAME=$1
if [ ! -d projects/$PROJECT_NAME ]; then
    echo "[clone project] $PROJECT_NAME"
    git clone git@github.com:LoveKino/$PROJECT_NAME.git thirdparty/$PROJECT_NAME
fi
