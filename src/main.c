#include <stdio.h>
#include <glib.h>
#include "video_store_data_types.h"
#include "video_store_data_provider.h"
#include "video_store_data_display.h"
#include "video_store.h"

void cleanup(GHashTable *movies, struct Customer *customer, char *statement)
{
    freeCustomer(customer);
    freeMovies(movies);
    free(statement);
}

int main(void) 
{
    struct Customer *customer = getCustomerData();
    GHashTable* movies = getMoviesData();
    printMoviesInStore(movies);
    printCustomerInfo(customer);
    char * statement = getStatement(movies, customer);
    cleanup(movies, customer, statement);
    puts(statement);    
}
