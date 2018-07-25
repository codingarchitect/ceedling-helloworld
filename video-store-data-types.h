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
