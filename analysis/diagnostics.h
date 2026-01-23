#pragma once
#include "core/diagnostics/diagnostics.h"
#include "core/hls/hls_types.h"

typedef void (*SegmentTimingValidator)(const HLSMediaPlaylist* playlist,
                                       DiagnosticIssue**       out_issues,
                                       int*                    out_count);
