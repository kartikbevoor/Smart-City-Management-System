#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define floors 5
#define blocks 10

struct Car  // Structure to store details of car
{
    char registration_number[20];
    char model[50];
    int floor;
    int block;
};

int arr[floors][blocks] = {0};

void insert_car();
void search_car();
void remove_car();
void print_all_cars();
void custom_parking();
void update();
void overnight_parking();
int main()
{
    int choice;
    update();
    while (1)
    {

        printf("\nParking Management System\n");
        printf("1. Insert Car\n");
        printf("2. Search Car\n");
        printf("3. Remove Car\n");
        printf("4. Print all cars\n");
        printf("5.Custom Parking\n");
        printf("6.Overnight Parking\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert_car();
            update();
            break;
        case 2:
            search_car();
            break;
        case 3:
            remove_car();
            update();
            break;
        case 4:
            print_all_cars();
            break;
        case 5:
            custom_parking();
            update();
            break;
        case 6:
            overnight_parking();
            update();
            break;
        case 7:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void insert_car() // Function to insert car in the parking
{
    FILE *file = fopen("parking.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Car car;
    printf("Enter registration number: ");
    scanf("%s", car.registration_number);
    printf("Enter car model: ");
    scanf("%s", car.model);
    int foundSpace = 0;
    for (int i = 0; i < floors && !foundSpace; ++i)
    {
        for (int j = 0; j < blocks && !foundSpace; ++j)
        {
            if (arr[i][j] == 0)
            {
                car.floor = i;
                car.block = j;
                arr[i][j] = 1;
                foundSpace = 1;
            }
        }
    }

    fprintf(file, "%s %s %d %d\n", car.registration_number, car.model, car.floor, car.block);

    fclose(file);

    printf("Car successfully parked on Floor %d, Block %d.\n", car.floor + 1, car.block + 1);
}

void search_car() // Function to search car
{
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char regNo[20];
    printf("Enter registration number to search: ");
    scanf("%s", regNo);

    struct Car car;
    int found = 0;

    while (fscanf(file, "%s %s %d %d", car.registration_number, car.model, &car.floor, &car.block) != EOF)
    {
        if (strcmp(regNo, car.registration_number) == 0)
        {
            found = 1;
            printf("Car found!\n");
            printf("Registration Number: %s\n", car.registration_number);
            printf("Car Model: %s\n", car.model);
            printf("Parked on Floor %d, Block %d\n", car.floor + 1, car.block + 1);
            break;
        }
    }

    if (!found)
    {
        printf("Car not found.\n");
    }

    fclose(file);
}

void remove_car()  // Function to remove car
{
    FILE *inputFile = fopen("parking.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file for writing.\n");
        fclose(inputFile);
        return;
    }

    char regNo[20];
    printf("Enter registration number to remove: ");
    scanf("%s", regNo);

    struct Car car;
    int found = 0;

    while (fscanf(inputFile, "%s %s %d %d", car.registration_number, car.model, &car.floor, &car.block) != EOF)
    {
        if (strcmp(regNo, car.registration_number) == 0)
        {
            found = 1;
            printf("Car removed from Floor %d, Block %d\n", car.floor + 1, car.block + 1);
            arr[car.floor][car.block] = 0;
        }
        else
        {
            fprintf(tempFile, "%s %s %d %d\n", car.registration_number, car.model, car.floor, car.block);
        }
    }

    if (!found)
    {
        printf("Car not found.\n");
    }

    fclose(inputFile);
    fclose(tempFile);
    remove("parking.txt");
    rename("temp.txt", "parking.txt");
}

void print_all_cars() // Function to print all cars
{
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    struct Car car;

    printf("\nAll Cars in the Parking Lot:\n");

    while (fscanf(file, "%s %s %d %d", car.registration_number, car.model, &car.floor, &car.block) != EOF)
    {
        printf("Registration Number: %s\n", car.registration_number);
        printf("Car Model: %s\n", car.model);
        printf("Parked on Floor %d, Block %d\n", car.floor + 1, car.block + 1);
        printf("\n");
    }

    fclose(file);
}
void custom_parking() // Function for custom parking
{
    printf("\nEmpty Parking Spaces:\n");

    for (int i = 0; i < floors; ++i)
    {
        for (int j = 0; j < blocks; ++j)
        {
            if (arr[i][j] == 0)
            {
                printf("Floor %d, Block %d\n", i + 1, j + 1);
            }
        }
    }

    int selectedFloor, block;

    printf("\nEnter the floor number where you want to park: ");
    scanf("%d", &selectedFloor);

    if (selectedFloor < 1 || selectedFloor > floors)
    {
        printf("Invalid floor number. Please try again.\n");
        return;
    }

    printf("Enter the block number where you want to park on Floor %d: ", selectedFloor);
    scanf("%d", &block);

    if (block < 1 || block > blocks)
    {
        printf("Invalid block number. Please try again.\n");
        return;
    }

    if (arr[selectedFloor - 1][block - 1] == 1)
    {
        printf("Selected parking space is already occupied. Please choose another space.\n");
        return;
    }

    struct Car car;
    printf("Enter registration number: ");
    scanf("%s", car.registration_number);
    printf("Enter car model: ");
    scanf("%s", car.model);

    car.floor = selectedFloor - 1;
    car.block = block - 1;
    arr[car.floor][car.block] = 1;

    FILE *file = fopen("parking.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s %s %d %d\n", car.registration_number, car.model, car.floor, car.block);

    fclose(file);

    printf("Car successfully parked on Floor %d, Block %d.\n", car.floor + 1, car.block + 1);
}
void update() // Function to uodate
{
    FILE *f=fopen("parking.txt", "r");
    struct Car car;
    while (fscanf(f, "%s %s %d %d", car.registration_number, car.model, &car.floor, &car.block) != EOF)
    {
        arr[car.floor][car.block]=1;
    }
    printf("Parking Layout, 1 represents a car is parked 0 represents empty space\n");
    for(int i=0;i<floors;i++)
    {
        printf("\n");
        for(int j=0;j<blocks;j++)
        {
            printf("%d\t",arr[i][j]);
        }
    }

    printf("\n\n\nUpdated Empty Parking Spaces:\n");
    for (int i = 0; i < floors; ++i)
    {
        for (int j = 0; j < blocks; ++j)
        {
            if (arr[i][j] == 0)
            {
                printf("Floor %d, Block %d\n", i + 1, j + 1);
            }
        }
    }
    fclose(f);
}
void overnight_parking()  // Function for over night parking
{
    if (floors >= 5)
    {
        printf("\nEmpty Parking Spaces on 5th Floor for Overnight Parking:\n");

        for (int j = 0; j < blocks; ++j)
        {
            if (arr[4][j] == 0)
            {
                printf("Block %d\n", j + 1);
            }
        }

        int block;
        printf("\nEnter the block number where you want to park on 5th Floor: ");
        scanf("%d", &block);

        if (block < 1 || block > blocks)
        {
            printf("Invalid block number. Please try again.\n");
            return;
        }

        if (arr[4][block - 1] == 1)
        {
            printf("Selected block is occupied, please choose another block\n");
            return;
        }

        struct Car car;
        printf("Enter registration number: ");
        scanf("%s", car.registration_number);
        printf("Enter car model: ");
        scanf("%s", car.model);

        car.floor = 4;
        car.block = block - 1;
        arr[car.floor][car.block] = 1;

        FILE *file = fopen("parking.txt", "a");
        if (file == NULL)
        {
            printf("Error opening file for writing.\n");
            return;
        }

        fprintf(file, "%s %s %d %d\n", car.registration_number, car.model, car.floor, car.block);

        fclose(file);

        printf("Car  parked on 5th Floor, Block %d.\n", car.block + 1);
    }
    else
    {
        printf("Overnight parking not available.\n");
    }
}
