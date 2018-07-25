#include <stdio.h>
#include <glib.h>
#include "video_store_data_types.h"
#include "video_store_data_display.h"

void printMoviesInStore(GHashTable *movies)
{
    printf("Movies in the store: \n");
    GHashTableIter moviesIterator;
    g_hash_table_iter_init (&moviesIterator, movies);
    gpointer movieKey, movieValue;
    
    while(g_hash_table_iter_next (&moviesIterator, &movieKey, &movieValue))
    {
        struct Movie *movie = (struct Movie*)movieValue;
        printf("MovieID: %s, Title: %s, Code: %s\n", movie->movieID, movie->title, movie->code);        
    }
}

void printCustomerInfo(struct Customer *customer)
{
    int i = 0;
    printf("Rentals for Customer: %s\n", customer->name);
    int noOfRentals = sizeof(customer->rentals) / sizeof(customer->rentals[0]);
    for(i = 0; i < noOfRentals; i++)
    {
        struct Rental *rental = customer->rentals[i];
        printf("Movie: %s, Days rented: %d\n", rental->movieID, rental->days);
    }
}
