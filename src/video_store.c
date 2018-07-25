#include <stdio.h>
#include <glib.h>
#include "video_store_data_types.h"
#include "video_store_data_provider.h"
#include "video_store.h"

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
