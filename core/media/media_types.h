#pragma once
#include <stdint.h>

typedef struct
{
    int64_t pts;
    int64_t dts;
    int64_t duration;
    int     is_keyframe;
} MediaFrame;

typedef struct
{
    MediaFrame* frames;
    int         frame_count;
    int         stream_index;
} MediaStream;
