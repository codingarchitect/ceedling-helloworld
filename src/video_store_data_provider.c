#include <stdio.h>
#include <glib.h>
#include "video_store_data_types.h"

struct Customer* getCustomerData() 
{
    struct Rental *rental1, *rental2;
    struct Customer* customer;

    rental1 = (struct Rental *) malloc(sizeof(struct Rental));
    rental2 = (struct Rental *) malloc(sizeof(struct Rental));
    customer = (struct Customer *) malloc(sizeof(struct Customer));

    *rental1 = (struct Rental){ .movieID = "M00001", .days = 1 };
    *rental2 = (struct Rental){ .movieID = "M00002", .days = 2 };

    *customer = (struct Customer){ .name = "Sendhil Kumar R", .rentals = { rental1, rental2 } };
    return customer;
}

void freeCustomer(struct Customer *customer) 
{
    int i;
    int noOfRentals = sizeof(customer->rentals) / sizeof(customer->rentals[0]);
    for (i = 0; i < noOfRentals; i++) 
    {
        struct Rental *rental = customer->rentals[i];
        free(rental);
    }
    free(customer);
}

void freeMovies(GHashTable *movies) 
{
    GHashTableIter moviesIterator;
    g_hash_table_iter_init (&moviesIterator, movies);
    gpointer movieKey, movieValue;
    
    while(g_hash_table_iter_next (&moviesIterator, &movieKey, &movieValue))
    {
        struct Movie *movie = (struct Movie*)movieValue;
        free(movie);
    }
    g_hash_table_destroy(movies);
}

GHashTable* getMoviesData()
{
    struct Movie *movie1, *movie2, *movie3, *movie4, *movie5, *movie6;

    movie1 = (struct Movie *) malloc(sizeof(struct Movie));
    movie2 = (struct Movie *) malloc(sizeof(struct Movie));
    movie3 = (struct Movie *) malloc(sizeof(struct Movie));
    movie4 = (struct Movie *) malloc(sizeof(struct Movie));
    movie5 = (struct Movie *) malloc(sizeof(struct Movie));
    movie6 = (struct Movie *) malloc(sizeof(struct Movie));

    *movie1 = (struct Movie){ .movieID = "M00001", .title = "Godfather", .code = "REGULAR" };
    *movie2 = (struct Movie){ .movieID = "M00002", .title = "The Lord of the rings - The Fellowship of the ring", .code = "REGULAR" };
    *movie3 = (struct Movie){ .movieID = "M00003", .title = "The Lord of the rings - The Return of the ring", .code = "REGULAR" };
    *movie4 = (struct Movie){ .movieID = "M00004", .title = "The Lord of the rings - The Two Towers", .code = "REGULAR" };
    *movie5 = (struct Movie){ .movieID = "M00005", .title = "Kungfu Panda", .code = "CHILDRENS" };
    *movie6 = (struct Movie){ .movieID = "M00006", .title = "Annabelle Creation", .code = "NEW" };
    // struct Movie *movies[6] = { &movie1, &movie2, &movie3, &movie4, &movie5, &movie6 };
    GHashTable* movies = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(movies, movie1->movieID, movie1);
    g_hash_table_insert(movies, movie2->movieID, movie2);
    g_hash_table_insert(movies, movie3->movieID, movie3);
    g_hash_table_insert(movies, movie4->movieID, movie4);
    g_hash_table_insert(movies, movie5->movieID, movie5);
    g_hash_table_insert(movies, movie6->movieID, movie6);
    return movies;
} 
