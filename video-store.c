#include <stdio.h>
#include <glib.h>

struct Rental 
{
    char movieID[7];
    int days;
};

struct Customer
{
    char name[100];
    struct Rental *rentals[2];
};

struct Movie
{
    char movieID[7];
    char title[100];
    char code[20];
};

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

void freeRentals(struct Customer *customer) 
{

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

int main(void) 
{
    struct Customer customer1 = *getCustomerData();
    GHashTable* movies = getMoviesData();
    int i = 0;
    
    printf("Movies in the store: \n");
    int noOfMovies = g_hash_table_size(movies);
    GHashTableIter moviesIterator;
    g_hash_table_iter_init (&moviesIterator, movies);
    gpointer movieKey, movieValue;
    
    while(g_hash_table_iter_next (&moviesIterator, &movieKey, &movieValue))
    {
        struct Movie *movie = (struct Movie*)movieValue;
        printf("MovieID: %s, Title: %s, Code: %s\n", movie->movieID, movie->title, movie->code);        
    }

    printf("Rentals for Customer: %s\n", customer1.name);
    int noOfRentals = sizeof(customer1.rentals) / sizeof(customer1.rentals[0]);
    for(i = 0; i < noOfRentals; i++)
    {
        struct Rental *rental = customer1.rentals[i];
        printf("Movie: %s, Days rented: %d\n", rental->movieID, rental->days);
    }

    double totalAmount = 0;
    int frequentRenterPoints = 0;
    double thisAmount = 0;
    char result[4096];
    sprintf(result, "Rental Record for %s\n", customer1.name);
    noOfRentals = sizeof(customer1.rentals) / sizeof(customer1.rentals[0]);
    for (i = 0; i < noOfRentals; i++) {
        struct Rental *rental = customer1.rentals[i];
        struct Movie *movie = g_hash_table_lookup(movies, rental->movieID);
        printf("MovieID: %s, Title: %s, Code: %s\n", movie->movieID, movie->title, movie->code);
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
    puts(result);
}