#include "playlist_consistency_checker.h"
#include <stdlib.h>

void validate_playlist_consistency(const HLSMediaPlaylist* playlist,
                                   DiagnosticIssue**       out_issues,
                                   int*                    out_count)
{
    if (!playlist || !playlist->segments)
    {
        *out_issues = NULL;
        *out_count  = 0;
        return;
    }

    int              capacity = 4;
    DiagnosticIssue* issues   = malloc(sizeof(DiagnosticIssue) * capacity);
    int              count    = 0;

    for (int i = 1; i < playlist->segment_count; i++)
    {
        int64_t expected_seq = playlist->segments[i - 1].sequence + 1;
        if (playlist->segments[i].sequence != expected_seq)
        {
            if (count >= capacity)
            {
                capacity *= 2;
                issues = realloc(issues, sizeof(DiagnosticIssue) * capacity);
            }
            issues[count++] = (DiagnosticIssue){.severity = SEVERITY_ERROR,
                                                .code     = "SEGMENT_SEQUENCE_GAP",
                                                .message  = "Gap in segment sequence detected"};
        }
    }

    *out_issues = issues;
    *out_count  = count;
}
