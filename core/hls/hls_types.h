#pragma once
#include <stdint.h>

typedef struct
{
    char*   uri;
    double  duration; // seconds
    int64_t sequence; // EXT-X-MEDIA-SEQUENCE + index
} HLSSegment;

typedef struct
{
    HLSSegment* segments;
    int         segment_count;

    double  target_duration;
    int64_t media_sequence;
    int     is_endlist;
} HLSMediaPlaylist;

typedef struct
{
    char* uri;
    int   bandwidth;
    int   width;
    int   height;
} HLSVariant;

typedef struct
{
    HLSVariant* variants;
    int         variant_count;
} HLSMasterPlaylist;
