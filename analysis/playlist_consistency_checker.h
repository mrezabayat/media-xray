#pragma once
#include "core/diagnostics/diagnostics.h"
#include "core/hls/hls_types.h"

/**
 * Validate that a media playlist is consistent.
 * Checks for:
 *  - Segment sequence gaps
 *  - Missing segments
 *  - Endlist inconsistencies
 *
 * @param playlist Pointer to a valid HLSMediaPlaylist
 * @param out_issues Pointer to an array of DiagnosticIssue* (allocated inside)
 * @param out_count Number of issues found
 */
void validate_playlist_consistency(const HLSMediaPlaylist* playlist,
                                   DiagnosticIssue**       out_issues,
                                   int*                    out_count);
