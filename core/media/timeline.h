#pragma once
#include "media_types.h"

typedef struct
{
    MediaStream* streams;
    int          stream_count;
} MediaTimeline;
