#!/bin/bash

set -e

faustpp -X-vec -X-lv -X1 -X-vs -X8 -a faustpp-template/DistrhoPluginInfoBase.h korg35lpf.dsp -o DistrhoPluginInfoBase.h
faustpp -X-vec -X-lv -X1 -X-vs -X8 -a faustpp-template/PluginDSP.cpp korg35lpf.dsp -o PluginDSP.cpp
