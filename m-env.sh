#!/bin/bash

export PATH=/opt/gcc-4.3-ls232/bin:$PATH                                                                          
export QTDIR=$PWD
export QTEDIR=$PWD
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH:/TSLIB/lib
export PATH=$QTDIR/bin:$PATH

