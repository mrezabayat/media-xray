#include "segment_timing_validator.h"
#include <stdio.h>
#include <stdlib.h>

void validate_segment_timing(const HLSMediaPlaylist* playlist,
                             DiagnosticIssue**       out_issues,
                             int*                    out_count)
{
    if (!playlist || !playlist->segments)
    {
        *out_count  = 0;
        *out_issues = NULL;
        return;
    }

    int              capacity = 4;
    DiagnosticIssue* issues   = malloc(sizeof(DiagnosticIssue) * capacity);
    int              count    = 0;

    double cumulative = 0.0;
    for (int i = 0; i < playlist->segment_count; i++)
    {
        HLSSegment seg = playlist->segments[i];

        if (seg.duration <= 0)
        {
            if (count >= capacity)
            {
                capacity *= 2;
                issues = realloc(issues, sizeof(DiagnosticIssue) * capacity);
            }
            issues[count++] = (DiagnosticIssue){.severity = SEVERITY_ERROR,
                                                .code     = "SEGMENT_INVALID_DURATION",
                                                .message  = "Segment duration <= 0"};
        }

        cumulative += seg.duration;
        if (seg.duration > playlist->target_duration * 1.05)
        {
            if (count >= capacity)
            {
                capacity *= 2;
                issues = realloc(issues, sizeof(DiagnosticIssue) * capacity);
            }
            issues[count++] = (DiagnosticIssue){.severity = SEVERITY_WARNING,
                                                .code     = "SEGMENT_LONG_DURATION",
                                                .message  = "Segment duration exceeds target +5%"};
        }
    }

    *out_issues = issues;
    *out_count  = count;
}
