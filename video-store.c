#include <stdio.h>

int main(void) 
{
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

    struct Rental rental1 = { .movieID = "M00001", .days = 1 };
    struct Rental rental2 = { .movieID = "M00002", .days = 2 };
    struct Customer customer1 = { .name = "Sendhil Kumar R", .rentals = { &rental1, &rental2 } };
    struct Movie movie1 = { .movieID = "M00001", .title = "Godfather", .code = "REGULAR" };
    struct Movie movie2 = { .movieID = "M00002", .title = "The Lord of the rings - The Fellowship of the ring", .code = "REGULAR" };
    struct Movie movie3 = { .movieID = "M00003", .title = "The Lord of the rings - The Return of the ring", .code = "REGULAR" };
    struct Movie movie4 = { .movieID = "M00004", .title = "The Lord of the rings - The Two Towers", .code = "REGULAR" };
    struct Movie movie5 = { .movieID = "M00005", .title = "Kungfu Panda", .code = "CHILDRENS" };
    struct Movie movie6 = { .movieID = "M00006", .title = "Annabelle Creation", .code = "NEW" };
    struct Movie *movies[6] = { &movie1, &movie2, &movie3, &movie4, &movie5, &movie6 };
    int i = 0;
    
    printf("Movies in the store: \n");
    int noOfMovies = sizeof(movies) / sizeof(movies[0]);
    for(i = 0; i < noOfMovies; i++)
    {
        struct Movie *movie = movies[i];
        printf("MovieID: %s, Title: %s, Code: %s\n", movie->movieID, movie->title, movie->code);
    }

    printf("Rentals for Customer: %s\n", customer1.name);
    int noOfRentals = sizeof(customer1.rentals) / sizeof(customer1.rentals[0]);
    for(i = 0; i < noOfRentals; i++)
    {
        struct Rental *rental = customer1.rentals[i];
        printf("Movie: %s, Days rented: %d\n", rental->movieID, rental->days);
    }
    
}