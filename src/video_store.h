#ifndef VIDEO_STORE_H
#define VIDEO_STORE_H
#include <glib.h>
#include "video_store_data_types.h"
#include "video_store_data_provider.h"

char* getStatement(GHashTable *movies, struct Customer *customer);

#endif // VIDEO_STORE_H
