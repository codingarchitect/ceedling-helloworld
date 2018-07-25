#ifndef VIDEO_STORE_DATA_DISPLAY_H
#define VIDEO_STORE_DATA_DISPLAY_H

#include <stdio.h>
#include <glib.h>
#include "video-store-data-types.h"

void printMoviesInStore(GHashTable *movies);
void printCustomerInfo(struct Customer *customer);

#endif // VIDEO_STORE_DATA_DISPLAY_H