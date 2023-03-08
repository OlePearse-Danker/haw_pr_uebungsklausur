
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sDatum
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
} 
sDatum;

typedef struct ENERGY_VALUE
{
    sDatum date;
    float load;
    float production;
    float import;
}
ENERGY_VALUE;

void get_data(ENERGY_VALUE *mp, int count);
ENERGY_VALUE calculate_average(ENERGY_VALUE *mp, int count);



int main (int argc, char* argv[])
{
    ENERGY_VALUE *mp;

    if (argc < 2)
    {
        fprintf(stderr, "At least one argument required!");
        exit(EXIT_FAILURE);
    }
    
    int count = (atoi(argv[1]));
    printf("Count of energy values read from file: %d\n", count);

    mp = malloc(count * sizeof(ENERGY_VALUE));

    get_data(mp, count);
    ENERGY_VALUE averages = calculate_average(mp, count);

    printf("%02d.%02d.%04d %02d:%02d\n",
        averages.date.day,
        averages.date.month,
        averages.date.year,
        averages.date.hour,
        averages.date.minute
    );
    printf("load average: %.3f\n", averages.load);
    printf("production average: %.3f\n", averages.production);
    printf("import average: %.3f\n", averages.import);

    free(mp);
}

void get_data(ENERGY_VALUE *mp, int count)
{
    FILE *fp; 

    fp = fopen("energiewerte.txt", "r");

    const size_t BUFFER_SIZE = 1024;

    char *buf= malloc(sizeof(char) *  BUFFER_SIZE);

    if (buf == NULL) 
    {
        printf("Error reading from file! Exiting..");
        exit(EXIT_FAILURE);
    }

    fgets(buf, BUFFER_SIZE-1, fp);
    
    for (size_t i = 0; i < count; i++)
    {
        fgets(buf, BUFFER_SIZE-1, fp);

        // fprintf(stderr, "%s\n", buf);

        // mp[i].date.day = atoi(strtok(buf, "."));
        // mp[i].date.month = atoi(strtok(buf, "."));
        // mp[i].date.year = atoi(strtok(buf, " "));
        // mp[i].date.hour = atoi(strtok(buf, ":"));
        // mp[i].date.minute = atoi(strtok(buf, ";"));

        // mp[i].load = atof(strtok(buf, ";"));        
        // mp[i].production = atof(strtok(buf, ";"));        
        // mp[i].import = atof(strtok(buf, ";"));      

        sscanf(buf, "%d.%d.%d %d:%d;%f;%f;%f",
            &mp[i].date.day,
            &mp[i].date.month,
            &mp[i].date.year,
            &mp[i].date.hour,
            &mp[i].date.minute,
            &mp[i].load,
            &mp[i].production,
            &mp[i].import
        );

        // fprintf(stderr, "%f\n", mp[i].load);
    }

    fclose(fp);
    free(buf);

    return;
}

ENERGY_VALUE calculate_average(ENERGY_VALUE *mp, int count)
{
    float load_average = 0;
    float production_average = 0;
    float import_average = 0;

    for (int i = 0; i < count; i++)
    {
        load_average += mp[i].load;
        production_average += mp[i].production;
        import_average += mp[i].import;
    }
    
    load_average /= count;
    production_average /= count;
    import_average /= count;

    ENERGY_VALUE averages; 
    
    averages.date = mp[count - 1].date;

    averages.load = load_average;
    averages.production = production_average;
    averages.import = import_average;

    return averages;
}
