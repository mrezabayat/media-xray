#pragma once
#include "core/diagnostics/diagnostics.h"
#include "core/hls/hls_types.h"

void validate_segment_timing(const HLSMediaPlaylist* playlist,
                             DiagnosticIssue**       out_issues,
                             int*                    out_count);
