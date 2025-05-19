#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif


typedef struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
    struct Product *next;
} Product;


void pressAnyKeyToContinue();
void mainMenu();
void productManagementMenu(Product **list);
void addProduct(Product **list);
void searchProduct(Product *list);
void modifyProduct(Product *list);
void deleteProduct(Product **list);
void generateReport(Product *list);
void displayList(Product *list);
void deleteAtBeginning(Product **list);
void deleteAtEnd(Product **list);
void deleteInMiddle(Product **list);
void deleteMenu(Product **list);
void displayHeader();
void displayFooter();

// Main function
int main() {
    int run;
    printf("\nThis project is created by: Souhail RABII & Mohamed-amine JAMAIE, press '1' to run the project: ");
    scanf("%d", &run);
    if (run == 1) {
        displayHeader();
        mainMenu();
    }
    return 0;
}

void pressAnyKeyToContinue() {
    printf("\n\t\t\t\t\t\tPress any key to continue...");
    getchar();
    getchar(); 
}

// header
void displayHeader() {
    system(CLEAR);
    printf("\033[1;31m"); 
    printf("\n\t\t\t\t\t\t\t  ╔██╗    ██╗ ╔███████╗ ██╗      ██████╗   ██████╗  ███╗   ███╗ ███████╗\n");
    printf("\t\t\t\t\t\t\t  ║██║    ██║ ║██╔════╝ ██║     ██╔════█  ██╔═══██╗ ████╗ ████║ ██╔════╝\n");
    printf("\t\t\t\t\t\t\t  ║██║ █╗ ██║ ║█████╗   ██║     ██║       ██║   ██║ ██╔████╔██║ █████╗  \n");
    printf("\t\t\t\t\t\t\t  ║██║███╗██║ ║██╔══╝   ██║     ██║    █  ██║   ██║ ██║╚██╔╝██║ ██╔══╝  \n");
    printf("\t\t\t\t\t\t\t   ╚███╔███╔╝ ║███████╗ ███████╗ ██████╝  ╚██████╔╝ ██║ ╚═╝ ██║ ███████╗\n");
    printf("\t\t\t\t\t\t\t    ╚══╝╚══╝  ╚═══════╝ ╚══════╝ ╚════╝    ╚═════╝  ╚═╝     ╚═╝ ╚══════╝\n\n");
    printf("\033[0m");
    
    printf("\033[1;36m");
    printf("\t\t\t\t\t\t======================================================================\n");
    printf("\t\t\t\t\t\t      |||||||||||  Product Inventory Management System  ||||||||||\n");
    printf("\t\t\t\t\t\t======================================================================\n");
    printf("\033[0m"); 
}

// footer
void displayFooter() {
    system(CLEAR);
    printf("\033[0;32m");
    printf("\n\n\t\t\t\t\t\t :) Program terminated successfully!!\n\n\n");
    printf("\033[0m");
    
    printf("\033[0;31m"); 
    printf("\n\t\t\t\t\t\t\t████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗    ██╗   ██╗ ██████╗ ██╗   ██╗\n");
    printf("\t\t\t\t\t\t\t╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝    ╚██╗ ██╔╝██╔═══██╗██║   ██║\n");
    printf("\t\t\t\t\t\t\t   ██║   ███████║███████║██╔██╗ ██║█████╔╝      ╚████╔╝ ██║   ██║██║   ██║\n");
    printf("\t\t\t\t\t\t\t   ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗       ╚██╔╝  ██║   ██║██║   ██║\n");
    printf("\t\t\t\t\t\t\t   ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗       ██║   ╚██████╔╝╚██████╔╝\n");
    printf("\t\t\t\t\t\t\t   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝       ╚═╝    ╚═════╝  ╚═════╝ \n\n");
    printf("\033[0m");
}

// Main menu
void mainMenu() {
    Product *productList = NULL;
    int choice;

    do {
        system(CLEAR);
        displayHeader();
        
        printf("\033[1;33m"); 
        printf("\t\t\t\t\t\t1. launch the program\n");
        printf("\t\t\t\t\t\t2. Exit\n");
        printf("\033[0m"); 
        printf("\033[1;36m");
        printf("\t\t\t\t\t\t======================================================================\n");
        printf("\033[0m");
        printf("\t\t\t\t\t\t * Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                productManagementMenu(&productList);
                break;
            case 2:
                displayFooter();
                break;
            default:
                printf("\033[0;31m"); 
                printf("\n\t\t\t\t\t\t\t :( Invalid choice. Please try again!\n");
                printf("\033[0m"); 
                pressAnyKeyToContinue();
        }
    } while(choice != 2);

    // Free memory 
    Product *temp;
    while(productList != NULL) {
        temp = productList;
        productList = productList->next;
        free(temp);
    }
}

// Product management menu
void productManagementMenu(Product **list) {
    int choice;

    do {
        system(CLEAR);
        displayHeader();
        
        printf("\033[1;33m"); 
        printf("\n\t\t\t\t\t\t1. Add a new product\n");
        printf("\t\t\t\t\t\t2. Search for a product\n");
        printf("\t\t\t\t\t\t3. Modify a product\n");
        printf("\t\t\t\t\t\t4. Delete a product\n");
        printf("\t\t\t\t\t\t5. Generate a Report \n");
        printf("\t\t\t\t\t\t6. Return to main menu\n");
        printf("\033[0m"); 
        printf("\033[1;36m"); 
        printf("\t\t\t\t\t\t======================================================================\n");
        printf("\033[0m");
        printf("\t\t\t\t\t\t * Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addProduct(list);
                break;
            case 2:
                searchProduct(*list);
                break;
            case 3:
                modifyProduct(*list);
                break;
            case 4:
                deleteProduct(list);
                break;
            case 5:
                generateReport(*list);
                break;
            case 6:
                printf("\033[0;32m");
                printf("\n\t\t\t\t\t\t\t Returning to main menu...\n");
                printf("\033[0m");
                pressAnyKeyToContinue();
                break;
            default:
                printf("\033[0;31m");
                printf("\n\t\t\t\t\t\t\t :( Invalid choice. Please try again!\n");
                printf("\033[0m");
                pressAnyKeyToContinue();
        }
    } while(choice != 6);
}

// Add product
void addProduct(Product **list) {
    system(CLEAR);
    displayHeader();
    
    Product *newProduct = (Product*)malloc(sizeof(Product));

    printf("\033[1;35m"); 
    printf("\n\t\t\t\t\t\t\t      * Add a New Product * \n");
    printf("\033[0m"); 
    
    printf("\t\t\t\t\t\tProduct ID: ");
    scanf("%d", &newProduct->id);

    // Check if ID exists
    Product *temp = *list;
    while(temp != NULL) {
        if(temp->id == newProduct->id) {
            printf("\033[0;31m");
            printf("\n\t\t\t\t\t\t\t :( A product with this ID already exists!\n");
            printf("\033[0m");
            free(newProduct);
            pressAnyKeyToContinue();
            return;
        }
        temp = temp->next;
    }

    printf("\t\t\t\t\t\tProduct name: ");
    scanf(" %[^\n]", newProduct->name);
    printf("\t\t\t\t\t\tQuantity in stock: ");
    scanf("%d", &newProduct->quantity);
    printf("\t\t\t\t\t\tPrice (USD): ");
    scanf("%f", &newProduct->price);

    newProduct->next = *list;
    *list = newProduct;

    printf("\033[0;32m");
    printf("\n\t\t\t\t\t\t\t :) Product added successfully!\n");
    printf("\033[0m");
    pressAnyKeyToContinue();
}

// Search product
void searchProduct(Product *list) {
    system(CLEAR);
    displayHeader();
    
    if(list == NULL) {
        printf("\033[0;31m"); 
        printf("\n\t\t\t\t\t\t\t :( The product list is empty!\n");
        printf("\033[0m"); 
        pressAnyKeyToContinue();
        return;
    }

    int choice;
    printf("\033[1;35m"); 
    printf("\n\t\t\t\t\t\t\t      * Search for a Product * \n");
    printf("\033[0m");  
    
    printf("\t\t\t\t\t\t1. By ID\n");
    printf("\t\t\t\t\t\t2. By name\n");
    printf("\t\t\t\t\t\t3. Return\n");
    printf("\t\t\t\t\t\t * Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 3) return;

    system(CLEAR);
    displayHeader();
    
    printf("\033[1;35m");  
    printf("\n\t\t\t\t\t\t\t      * Search Results * \n");
    printf("\033[0m");  
    
    printf("\t\t\t\t\t\t------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t| %-10s | %-20s | %-10s | %-10s |\n", "ID", "Product Name", "Quantity", "Price");
    printf("\t\t\t\t\t\t------------------------------------------------------------\n");

    int found = 0;
    Product *temp = list;

    if(choice == 1) {
        int id;
        printf("\t\t\t\t\t\tEnter ID to search: ");
        scanf("%d", &id);

        while(temp != NULL) {
            if(temp->id == id) {
                printf("\t\t\t\t\t\t| %-10d | %-20s | %-10d | %-10.2f |\n",
                       temp->id, temp->name, temp->quantity, temp->price);
                found = 1;
                break;
            }
            temp = temp->next;
        }
    }
    else if(choice == 2) {
        char name[50];
        printf("\t\t\t\t\t\tEnter name to search: ");
        scanf(" %[^\n]", name);

        while(temp != NULL) {
            if(strstr(temp->name, name) != NULL) {
                printf("\t\t\t\t\t\t| %-10d | %-20s | %-10d | %-10.2f |\n",
                       temp->id, temp->name, temp->quantity, temp->price);
                found = 1;
            }
            temp = temp->next;
        }
    }

    if(!found) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( No products found!\n");
        printf("\033[0m");  
    }

    printf("\t\t\t\t\t\t------------------------------------------------------------\n");
    pressAnyKeyToContinue();
}

// Modify a product
void modifyProduct(Product *list) {
    system(CLEAR);
    displayHeader();
    
    if(list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The product list is empty!\n");
        printf("\033[0m");  
        pressAnyKeyToContinue();
        return;
    }

    int id;
    printf("\033[1;35m");  
    printf("\n\t\t\t\t\t\t\t      * Modify a Product * \n");
    printf("\033[0m");  
    
    printf("\t\t\t\t\t\tEnter product ID to modify: ");
    scanf("%d", &id);

    Product *temp = list;
    while(temp != NULL) {
        if(temp->id == id) {
            printf("\033[1;34m");  
            printf("\n\t\t\t\t\t\t\t      * Product Found: * \n");
            printf("\033[0m");  
            
            printf("\t\t\t\t\t\tProduct ID | Product Name | Quantity in Stock | Price |\n");
            printf("\t\t\t\t\t\t%-10d | %-11s | %-17d | %.2f USD |\n",
                   temp->id, temp->name, temp->quantity, temp->price);

            printf("\033[1;33m");  
            printf("\n\t\t\t\t\t\tEnter new information:\n");
            printf("\033[0m");  
            
            printf("\t\t\t\t\t\tNew name: ");
            scanf(" %[^\n]", temp->name);
            printf("\t\t\t\t\t\tNew quantity: ");
            scanf("%d", &temp->quantity);
            printf("\t\t\t\t\t\tNew price: ");
            scanf("%f", &temp->price);

            printf("\033[0;32m");  
            printf("\n\t\t\t\t\t\t\t :) Product modified successfully!\n");
            printf("\033[0m");  
            pressAnyKeyToContinue();
            return;
        }
        temp = temp->next;
    }

    printf("\033[0;31m");  
    printf("\n\t\t\t\t\t\t\t :( Product with ID %d not found!\n", id);
    printf("\033[0m");  
    pressAnyKeyToContinue();
}

// Delete a product
void deleteProduct(Product **list) {
    system(CLEAR);
    displayHeader();
    
    if(*list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The product list is empty!\n");
        printf("\033[0m");  
        pressAnyKeyToContinue();
        return;
    }

    deleteMenu(list);
}

// Generate report
void generateReport(Product *list) {
    system(CLEAR);
    displayHeader();
    
    if(list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The product list is empty!\n");
        printf("\033[0m");  
        pressAnyKeyToContinue();
        return;
    }

    printf("\033[1;35m");  
    printf("\n\t\t\t\t\t\t\t      * Product Inventory Report * \n");
    printf("\033[0m");  
    
    printf("\t\t\t\t\t\t------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t| %-10s | %-20s | %-10s | %-10s |\n", "ID", "Product Name", "Quantity", "Price");
    printf("\t\t\t\t\t\t------------------------------------------------------------\n");

    Product *temp = list;
    while(temp != NULL) {
        printf("\t\t\t\t\t\t| %-10d | %-20s | %-10d | %-10.2f |\n",
               temp->id, temp->name, temp->quantity, temp->price);
        temp = temp->next;
    }
    printf("\t\t\t\t\t\t------------------------------------------------------------\n");

    printf("\n\t\t\t\t\t\tWould you like to save this report to a file? (y/n): ");
    char choice;
    scanf(" %c", &choice);

    if(choice == 'y' || choice == 'Y') {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char filename[50];
        strftime(filename, sizeof(filename), "inventory_report_%Y-%m-%d_%H-%M-%S.txt", t);

        FILE *file = fopen(filename, "w");
        if(file == NULL) {
            printf("\033[0;31m");  
            printf("\n\t\t\t\t\t\t\t :( Error creating file!\n");
            printf("\033[0m");  
        } else {
            fprintf(file, "Product Inventory Report - Generated on %s\n\n", asctime(t));
            fprintf(file, "------------------------------------------------------------\n");
            fprintf(file, "| %-10s | %-20s | %-10s | %-10s |\n", "ID", "Product Name", "Quantity", "Price");
            fprintf(file, "------------------------------------------------------------\n");

            temp = list;
            while(temp != NULL) {
                fprintf(file, "| %-10d | %-20s | %-10d | %-10.2f |\n",
                       temp->id, temp->name, temp->quantity, temp->price);
                temp = temp->next;
            }
            fprintf(file, "------------------------------------------------------------\n");
            fclose(file);

            printf("\033[0;32m");  
            printf("\n\t\t\t\t\t\t\t :) Report saved to %s\n", filename);
            printf("\033[0m");  
        }
    }

    pressAnyKeyToContinue();
}

// Display product list
void displayList(Product *list) {
    if(list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The product list is empty!\n");
        printf("\033[0m");  
        return;
    }

    printf("\033[1;35m");  
    printf("\n\t\t\t\t\t\t\t      * Product List * \n");
    printf("\033[0m");  
    
    printf("\t\t\t\t\t\tProduct ID | Product Name | Quantity in Stock | Price |\n");
    printf("\t\t\t\t\t\t----------------------------------------------------\n");

    Product *temp = list;
    while(temp != NULL) {
        printf("\t\t\t\t\t\t%-10d | %-11s | %-17d | %.2f USD |\n",
               temp->id, temp->name, temp->quantity, temp->price);
        temp = temp->next;
    }
}

// Delete from beginning
void deleteAtBeginning(Product **list) {
    if(*list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The list is already empty!\n");
        printf("\033[0m");  
        return;
    }

    Product *temp = *list;
    *list = (*list)->next;
    printf("\033[0;32m");  
    printf("\n\t\t\t\t\t\t\t :) Product deleted: %s (ID: %d)\n", temp->name, temp->id);
    printf("\033[0m");  
    free(temp);
    pressAnyKeyToContinue();
}

// Delete from end
void deleteAtEnd(Product **list) {
    if(*list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The list is already empty!\n");
        printf("\033[0m");  
        return;
    }

    if((*list)->next == NULL) {
        printf("\033[0;32m");  
        printf("\n\t\t\t\t\t\t\t :) Product deleted: %s (ID: %d)\n", (*list)->name, (*list)->id);
        printf("\033[0m");  
        free(*list);
        *list = NULL;
        pressAnyKeyToContinue();
        return;
    }

    Product *temp = *list;
    Product *previous = NULL;

    while(temp->next != NULL) {
        previous = temp;
        temp = temp->next;
    }

    previous->next = NULL;
    printf("\033[0;32m");  
    printf("\n\t\t\t\t\t\t\t :) Product deleted: %s (ID: %d)\n", temp->name, temp->id);
    printf("\033[0m");  
    free(temp);
    pressAnyKeyToContinue();
}

// Delete from middle
void deleteInMiddle(Product **list) {
    if(*list == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( The list is already empty!\n");
        printf("\033[0m");  
        return;
    }

    int id;
    printf("\t\t\t\t\t\tEnter product ID to delete: ");
    scanf("%d", &id);

    Product *temp = *list;
    Product *previous = NULL;

    while(temp != NULL && temp->id != id) {
        previous = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("\033[0;31m");  
        printf("\n\t\t\t\t\t\t\t :( Product with ID %d not found!\n", id);
        printf("\033[0m");  
        pressAnyKeyToContinue();
        return;
    }

    if(previous == NULL) {
        *list = temp->next;
    } else {
        previous->next = temp->next;
    }

    printf("\033[0;32m");  
    printf("\n\t\t\t\t\t\t\t :) Product deleted: %s (ID: %d)\n", temp->name, temp->id);
    printf("\033[0m");  
    free(temp);
    pressAnyKeyToContinue();
}

// Deletion menu
void deleteMenu(Product **list) {
    int choice;

    do {
        system(CLEAR);
        displayHeader();
        displayList(*list);

        printf("\033[1;33m");  
        printf("\n\t\t\t\t\t\tDelete Options:\n");
        printf("\t\t\t\t\t\t1. Delete from beginning\n");
        printf("\t\t\t\t\t\t2. Delete from end\n");
        printf("\t\t\t\t\t\t3. Delete from middle\n");
        printf("\t\t\t\t\t\t4. Return\n");
        printf("\033[0m");  
        printf("\t\t\t\t\t\t * Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                deleteAtBeginning(list);
                break;
            case 2:
                deleteAtEnd(list);
                break;
            case 3:
                deleteInMiddle(list);
                break;
            case 4:
                printf("\033[0;32m");  
                printf("\n\t\t\t\t\t\t\t Returning to previous menu...\n");
                printf("\033[0m");  
                pressAnyKeyToContinue();
                break;
            default:
                printf("\033[0;31m");  
                printf("\n\t\t\t\t\t\t\t :( Invalid choice. Please try again!\n");
                printf("\033[0m");  
                pressAnyKeyToContinue();
        }
    } while(choice != 4);
}
