#pragma once
#include "hls_types.h"

typedef enum
{
    HLS_OK = 0,
    HLS_ERR_INVALID_DURATION,
    HLS_ERR_EMPTY_PLAYLIST,
    HLS_ERR_SEQUENCE_GAP
} HLSValidationError;

HLSValidationError hls_validate_media_playlist(const HLSMediaPlaylist* playlist);
