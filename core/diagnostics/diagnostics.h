#pragma once
#include "severity.h"

typedef struct
{
    DiagnosticSeverity severity;
    const char*        code;    // e.g. "HLS_SEGMENT_DRIFT"
    const char*        message; // human readable
} DiagnosticIssue;
