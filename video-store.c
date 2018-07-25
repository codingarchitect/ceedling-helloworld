#include <stdio.h>
#include <glib.h>
#include "video-store-data-types.h"
#include "video-store-data-provider.h"

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

char* getStatement(GHashTable *movies, struct Customer *customer)
{
    int i = 0;    
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    double thisAmount = 0;
    char * result = (char*)malloc(4096);
    sprintf(result, "Rental Record for %s\n", customer->name);
    int noOfRentals = sizeof(customer->rentals) / sizeof(customer->rentals[0]);
    for (i = 0; i < noOfRentals; i++) {
        struct Rental *rental = customer->rentals[i];
        struct Movie *movie = g_hash_table_lookup(movies, rental->movieID);
        // determine amount for each movie
        if (strcmp(movie->code, "REGULAR") == 0)
        {
            thisAmount = 2;
            if (rental->days > 2) {
                thisAmount += (rental->days - 2) * 1.5;
            }
        } 
        else if (strcmp(movie->code, "NEW") == 0)
        {
            thisAmount = rental->days * 3;
        }
        else if (strcmp(movie->code, "CHILDRENS") == 0)
        {
            thisAmount = 1.5;
            if (rental->days > 3) {
                thisAmount += (rental->days - 3) * 1.5;
            }
        }

        //add frequent renter points
        frequentRenterPoints++;
        // add bonus for a two day new release rental
        if(strcmp(movie->code, "NEW") == 0 && rental->days > 2) frequentRenterPoints++;
  
        //print figures for this rental
        char movieLineBuffer[500];
        sprintf(movieLineBuffer, "\t%s\t%f\n", movie->title, thisAmount);
        strcat(result, movieLineBuffer);
        totalAmount += thisAmount;
    }
    
    // add footer lines
    char amountOwedBuffer[500];
    sprintf(amountOwedBuffer, "Amount owed is %f\n", totalAmount);
    strcat(result, amountOwedBuffer);
    char frequentRenterPointsBuffer[500];
    sprintf(frequentRenterPointsBuffer, "You earned %d frequent renter points\n", frequentRenterPoints);
    strcat(result, frequentRenterPointsBuffer);
    return result;
}

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