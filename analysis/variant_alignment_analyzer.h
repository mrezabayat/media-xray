#pragma once
#include "core/diagnostics/diagnostics.h"
#include "core/hls/hls_types.h"

void validate_variant_alignment(const HLSMasterPlaylist* master,
                                DiagnosticIssue**        out_issues,
                                int*                     out_count);
