#include "core/hls/hls_invariants.h"
#include "test_assert.h"

int main(void)
{
    HLSSegment segments[] = {{"seg1.ts", 4.0, 10}, {"seg2.ts", 4.0, 11}};

    HLSMediaPlaylist playlist = {.segments        = segments,
                                 .segment_count   = 2,
                                 .target_duration = 4.0,
                                 .media_sequence  = 10,
                                 .is_endlist      = 1};

    ASSERT_EQ(hls_validate_media_playlist(&playlist), HLS_OK);

    segments[1].duration = 0.0;

    ASSERT_EQ(hls_validate_media_playlist(&playlist), HLS_ERR_INVALID_DURATION);

    return 0;
}
