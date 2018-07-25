#include <stdio.h>
#include <glib.h>
#include "video-store-data-types.h"
#include "video-store-data-provider.h"
#include "video-store-data-display.h"
#include "video-store.h"

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
