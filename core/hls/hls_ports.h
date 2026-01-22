#pragma once
#include "hls_types.h"

typedef struct
{
    HLSMasterPlaylist* (*parse_master)(const char* text);
    HLSMediaPlaylist* (*parse_media)(const char* text);
} HLSParserPort;
