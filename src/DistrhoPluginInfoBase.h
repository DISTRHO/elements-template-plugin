
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: korg35lpf.dsp
// Name: Korg35LPF
// Description: 
// Author: Christopher Arndt
// Copyright: 
// License: MIT-style STK-4.3 license
// Version: 
//------------------------------------------------------------------------------





#pragma once

#define DISTRHO_PLUGIN_NUM_INPUTS      1
#define DISTRHO_PLUGIN_NUM_OUTPUTS     1

enum Parameters {
    // inputs
    kParameter_cutoff,
    kParameter_q,
    
    // outputs
    
    // terminator
    kParameterCount
};

enum Programs {
    kProgramCount
};

enum States {
    kStateCount
};

static constexpr const char* kParameterNames[2] = {
    // inputs
    "Cutoff frequency",
    "Q",
    
    // ouputs
    
};

static constexpr const struct { float def, min, max; } kParameterRanges[2] = {
    // inputs
    { 20000.0, 20.0, 20000.0 },
    { 1.0, 0.5, 10.0 },
    
    // ouputs
    
};

static constexpr const char* kParameterSymbols[2] = {
    // inputs
    "cutoff",
    "q",
    
    // ouputs
    
};

static constexpr const char* kParameterUnits[2] = {
    // inputs
    "hz",
    "",
    
    // ouputs
    
};


