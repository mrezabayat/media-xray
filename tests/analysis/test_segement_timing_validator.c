#include "analysis/segment_timing_validator.h"
#include "core/hls/hls_types.h"
#include "test_assert.h"

int main(void)
{
    HLSSegment       segments[] = {{"s1.ts", 4.0, 1}, {"s2.ts", 6.0, 2}};
    HLSMediaPlaylist p          = {segments, 2, 4.0, 1, 1};

    DiagnosticIssue* issues;
    int              count;
    validate_segment_timing(&p, &issues, &count);

    ASSERT_TRUE(count == 1);
    free(issues);
}
