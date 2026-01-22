#include "hls_invariants.h"

HLSValidationError hls_validate_media_playlist(const HLSMediaPlaylist* p)
{
    if (!p || p->segment_count == 0)
        return HLS_ERR_EMPTY_PLAYLIST;

    for (int i = 0; i < p->segment_count; i++)
    {
        if (p->segments[i].duration <= 0)
            return HLS_ERR_INVALID_DURATION;

        if (i > 0 && p->segments[i].sequence != p->segments[i - 1].sequence + 1)
            return HLS_ERR_SEQUENCE_GAP;
    }

    return HLS_OK;
}
