#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// method for encrypting the plaintext
void encrypt(char *plaintext, int key, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) 
    {
        // check if the character is part of the alphabet
        if (isalpha(plaintext[i])) 
        {
            // check if the character is uppercase or lowercase
            if (isupper(plaintext[i]))
                ciphertext[i] = ((plaintext[i] - 'A' + key) % 26) + 'A';
            else
                ciphertext[i] = ((plaintext[i] - 'a' + key) % 26) + 'a';
        } else 
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

// method for decrypting the ciphertext
void decrypt(char *ciphertext, int key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) 
    {
        // check if the character is part of the alphabet
        if (isalpha(ciphertext[i])) 
        {
            // check if the character is uppercase or lowercase
            if (isupper(ciphertext[i]))
                plaintext[i] = ((ciphertext[i] - 'A' - key + 26) % 26) + 'A';
            else
                plaintext[i] = ((ciphertext[i] - 'a' - key + 26) % 26) + 'a';
        } else 
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main(int argc, char *argv[]) 
{
    int choice, key;
    char *plaintext = NULL, *ciphertext = NULL;
    char input_file[100], output_file[100];
    FILE *fin, *fout;
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t len;

    if (argc != 2) 
    {
        printf("Usage: %s 1 for encryption, 2 for decryption ex: .caesar 1\n", argv[0]);
        return 1;
    }

    choice = atoi(argv[1]);

    if (choice == 1) 
    {
        printf("Enter the key for encryption: ");
        scanf("%d", &key);
        printf("Enter the input plaintext file name: ");
        scanf("%s", input_file);
        printf("Enter the output ciphertext file name: ");
        scanf("%s", output_file);

        // open the input and output files
        fin = fopen(input_file, "r");
        if (fin == NULL) 
        {
            printf("Error opening input file.\n");
            return 1;
        }
        fout = fopen(output_file, "w");

        if (fout == NULL) 
        {
            printf("Error opening output file.\n");
            fclose(fin);
            return 1;
        }

        while ((len = getline(&buffer, &bufsize, fin)) != -1) 
        {
            // allocate memory for plaintext and ciphertext
            plaintext = malloc(len + 1);
            ciphertext = malloc(len + 1);

            strcpy(plaintext, buffer);              // copy the line read from the file to plaintext
            encrypt(plaintext, key, ciphertext);    // encrypt the plaintext and store the result in ciphertext
            fputs(ciphertext, fout);                // write the ciphertext to the output file

            // free the memory allocated for plaintext and ciphertext
            free(plaintext);
            free(ciphertext);
        }

        // free the memory allocated for buffer and close the input and output files
        free(buffer);
        fclose(fin);
        fclose(fout);

        printf("Encryption completed. Ciphertext written to %s.\n", output_file);
    } 
    else if (choice == 2) 
    {
        printf("Enter the key for decryption: ");
        scanf("%d", &key);
        printf("Enter the input ciphertext file name: ");
        scanf("%s", input_file);
        printf("Enter the output plaintext file name: ");
        scanf("%s", output_file);

        // open the input and output files
        fin = fopen(input_file, "r");
        if (fin == NULL) 
        {
            printf("Error opening input file.\n");
            return 1;
        }
        fout = fopen(output_file, "w");
        if (fout == NULL) 
        {
            printf("Error opening output file.\n");
            fclose(fin);
            return 1;
        }

        while ((len = getline(&buffer, &bufsize, fin)) != -1) 
        {
            // allocate memory for plaintext and ciphertext
            ciphertext = malloc(len + 1);
            plaintext = malloc(len + 1);
            strcpy(ciphertext, buffer);             // copy the line read from the file to ciphertext
            decrypt(ciphertext, key, plaintext);    // decrypt the ciphertext and store the result in plaintext
            fputs(plaintext, fout);                 // write the plaintext to the output file   

            // free the memory allocated for plaintext and ciphertext
            free(ciphertext);
            free(plaintext);
        }

        // free the memory allocated for buffer and close the input and output files
        free(buffer);
        fclose(fin);
        fclose(fout);

        printf("Decryption completed. Plaintext written to %s.\n", output_file);
    } else 
    {
        printf("Invalid choice. Please enter 1 for encryption or 2 for decryption.\n");
        return 1;
    }

    return 0;
}
