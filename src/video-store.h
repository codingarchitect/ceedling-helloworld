#ifndef VIDEO_STORE_H
#define VIDEO_STORE_H
#include <glib.h>
#include "video-store-data-types.h"
#include "video-store-data-provider.h"

char* getStatement(GHashTable *movies, struct Customer *customer);

#endif // VIDEO_STORE_H
