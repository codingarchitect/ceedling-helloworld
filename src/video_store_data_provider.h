#ifndef VIDEO_STORE_DATA_PROVIDERS_H
#define VIDEO_STORE_DATA_PROVIDERS_H

#include <stdio.h>
#include <glib.h>
#include "video_store_data_types.h"

struct Customer* getCustomerData();
void freeCustomer(struct Customer *customer);
GHashTable* getMoviesData();
void freeMovies(GHashTable *movies);
#endif // VIDEO_STORE_DATA_PROVIDERS_H