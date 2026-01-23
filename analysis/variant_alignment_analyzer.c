#include "variant_alignment_analyzer.h"
#include <stdlib.h>

void validate_variant_alignment(const HLSMasterPlaylist* master,
                                DiagnosticIssue**        out_issues,
                                int*                     out_count)
{
    if (!master || master->variant_count < 2)
    {
        *out_count  = 0;
        *out_issues = NULL;
        return;
    }

    int              capacity = 4;
    DiagnosticIssue* issues   = malloc(sizeof(DiagnosticIssue) * capacity);
    int              count    = 0;

    for (int i = 0; i < master->variant_count - 1; i++)
    {
        if (master->variants[i].bandwidth != master->variants[i + 1].bandwidth)
        {
            if (count >= capacity)
            {
                capacity *= 2;
                issues = realloc(issues, sizeof(DiagnosticIssue) * capacity);
            }
            issues[count++] =
                (DiagnosticIssue){.severity = SEVERITY_WARNING,
                                  .code     = "VARIANT_MISMATCH_BANDWIDTH",
                                  .message  = "Adjacent variants have mismatched bandwidth"};
        }
    }

    *out_issues = issues;
    *out_count  = count;
}
