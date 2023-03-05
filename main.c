#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

// ---------------------
// Aufgabe 2.1
// ---------------------
typedef struct sDatum
{
    int Tag, Monat, Jahr, Stunde, Minute;
}
sDatum;

typedef struct tEnergiewert
{
    sDatum dat; // Energiewert structure contains member, which is from another structure type
    float Last;
    float Erzeugung;
    float Importe;
}
tEnergiewert;

void print_overview(tEnergiewert *mp, int energy_values);
tEnergiewert calculate_average(tEnergiewert *mp, int energy_values);

int main (int argc, char* argv[])
{
    FILE* fp;				//File-Pointer für vorliegende CSV-Datei

    char *buf = malloc(sizeof(char) * 1024);
    // if (buf == NULL) exit(EXIT_FAILURE);
    
    tEnergiewert *mp;       //Struct-Pointer zur einfachen Speicherung der Zeilen aus CSV-Datei

    system("clear");

    // -------------------
    // Aufgabe 2.2
    // -------------------

    for (int i = 0; i < argc; i++)  
    {
        printf("Parameter [%d] = \"%s\"\n", i, argv[i]);        
    }

    // Conversion of the command line argument (char) into an integer for further use
    if (argc < 2)
    {
        fprintf(stderr, "At least 1 argument is required!/n");
        exit(EXIT_FAILURE);
    }
    int energy_values = atoi(argv[1]);
    printf("Anzahl der Energiewerte, die aus der Datei ausgelesen werden sollen: %d\n", energy_values);

    // allocating necessary memory
    mp = malloc(energy_values * sizeof(tEnergiewert));

    //printing memory adress (to make sure it worked)
    printf("%p\n", mp);

    // Initalizing struct to 0
    // tEnergiewert x = {};
    
    // -------------
    // Aufgabe 2.3
    // -------------

    //open file
	fp = fopen("energiewerte.txt", "r");

    if (fp == NULL) 
    {
        printf("File Error!Exiting\n");
        exit(0);
	}

    fgets(buf, strlen(buf)-1, fp);

	//loop-reading leftover lines
	for (int i = 0; i < energy_values; i++)
	{
		fgets(buf, strlen(buf)-1, fp);
		if (buf == NULL)
		{
			printf("error reading file!\n");
			exit(0);
		}

		//Speichern der durch ; getrennten Elemente in Struct-array per Pointer
		mp[i].dat.Tag = atoi(strtok(buf, "."));
        mp[i].dat.Monat = atoi(strtok(NULL, "."));
        mp[i].dat.Jahr = atoi(strtok(NULL, " "));
        mp[i].dat.Stunde = atoi(strtok(NULL, ":"));
        mp[i].dat.Minute = atoi(strtok(NULL, ";"));

		mp[i].Last = atof(strtok(NULL, ";"));
		mp[i].Erzeugung = atof(strtok(NULL, ";"));
		mp[i].Importe = atof(strtok(NULL, ";"));
	}

    // function to print the overview
    print_overview(mp, energy_values);
 
    // -------------
    // Aufgabe 2.4
    // ------------- 

    // Calculating average for Last,Erzeugung und Importe
    calculate_average(mp, energy_values);

    // freeing allocated memory
    free(mp);
    free(buf);

    

    // printf("Datum       |   Last (MW) |   Erzeugung (MW)  |   Importe (MW)\n");

    // tEnergiewert firstValue = {01,01,2021,00,00, 1079.997, 409.589, 724.782}; 

    // printf("%d.%d.%d %d.%d", firstValue.dat.Tag, firstValue.dat.Monat, firstValue.dat.Jahr, firstValue.dat.Stunde, firstValue.dat.Minute);

    // printf("|%13.3f|%19.3f|%10.3f\n", firstValue.Last, firstValue.Erzeugung, firstValue.Importe);


    return 0;

}


// function definitions
void print_overview(tEnergiewert* mp, int energy_values)
{
	//Ausgabe Abkürzung, Gewichtung, Note
	printf("Datum\t\tLast\t\tErzeugung\t\tImporte\n");

	//print-loop
	for (int i = 0; i < energy_values; i++)
	{   
        printf("%d.%d.%d %d.%d", mp[i].dat.Tag, mp[i].dat.Monat, mp[i].dat.Jahr, mp[i].dat.Stunde, mp[i].dat.Minute); 
		printf("|%13.3f|%13.3f|%13.3f\n", mp[i].Last, mp[i].Erzeugung, mp[i].Importe);
		printf("\n");
	}

}

tEnergiewert calculate_average(tEnergiewert* mp, int energy_values)
{
    float result = 0;
    float average_Last = 0; 

    for (int i = 0; i < energy_values; i++)
    {
        result += mp[i].Last;
    }

    average_Last = result/ energy_values;

    result = 0;
    float average_Erzeugung = 0; 
    for (int i = 0; i < energy_values; i++)
    {
        result += mp[i].Erzeugung;
    }
    
    average_Erzeugung = result/ energy_values;

    result = 0;
    float average_Importe = 0; 
    for (int i = 0; i < energy_values; i++)
    {
        result += mp[i].Importe;
    }
    
    average_Importe = result/ energy_values;

    // tEnergiewert averages = {mp[energy_values].dat.Tag, mp[energy_values].dat.Monat, mp[energy_values].dat.Jahr, mp[energy_values].dat.Stunde, mp[energy_values].dat.Minute, average_Last, average_Erzeugung, average_Importe};

    // printf("%d.%d.%d %d.%d", averages.dat.Tag, averages.dat.Monat, averages.dat.Jahr, averages.dat.Stunde, averages.dat.Minute); 

    printf("|%13.3f|%13.3f|%13.3f\n", average_Last, average_Erzeugung, average_Importe);

    // --------------------------------------------
    // Printing to check if values stored correctly
    // --------------------------------------------
    // for (int i = (energy_values - 1); i < energy_values; i++)   // only way I can get it to print 
	// {   
    //     printf("%d.%d.%d %d.%d", mp[i].dat.Tag, mp[i].dat.Monat, mp[i].dat.Jahr, mp[i].dat.Stunde, mp[i].dat.Minute); 
	// 	printf("\n");
	// }
    tEnergiewert averages;

    // Copy one entire struct -> Datum wird auch komplett rüberkopiert
    averages = mp[energy_values]; 

    averages.Last = average_Last;
    averages.Erzeugung = average_Erzeugung;
    averages.Importe = average_Importe;

    return averages;



    printf("%d.%d.%d %d.%d", mp[energy_values].dat.Tag, mp[energy_values].dat.Monat, mp[energy_values].dat.Jahr, mp[energy_values].dat.Stunde, mp[energy_values].dat.Minute); 
    
} 

