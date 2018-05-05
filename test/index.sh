#!/bin/bash

cd `dirname $0`;

TEST_BUILD_DIR=./build
TEST_SRC_DIR=./src
LIB_SRC_DIR=../lib
THIRDPARTY_LIB=../thirdparty/*/lib

[ -d $TEST_BUILD_DIR ] && rm -rf $TEST_BUILD_DIR

mkdir $TEST_BUILD_DIR

function runTestFile() {
    echo "[run test file] $TEST_SRC_DIR/$1"
    g++ -std=c++11 $THIRDPARTY_LIB/**.cc $LIB_SRC_DIR/**.cc  $TEST_SRC_DIR/$1 -I$LIB_SRC_DIR -I$THIRDPARTY_LIB -o $TEST_BUILD_DIR/$1.test
    $TEST_BUILD_DIR/$1.test
}

runTestFile base.cc
