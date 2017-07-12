#include "stdio.h"
#include "stdlib.h"

struct komentari
{
    char koments[31];
    komentari *next;
    komentari *previous;
};


struct virsraksti
{
    int id;
    char nosaukums[201];
    komentari* norade;
};

int main()
{
    FILE* inFile;
    FILE* outFile;
    int rakstuSkaits;
    int mainigais;
    inFile = fopen("raksti.in", "r");
    outFile = fopen("raksti.out", "w+");
    if (fscanf(inFile, "%d", &rakstuSkaits)!=EOF)
    {
        virsraksti* masivs[rakstuSkaits];
        for (int i = 0; i < rakstuSkaits; i++)
        {
                masivs[i]= new virsraksti;
                masivs[i]->norade=0;
                fscanf(inFile,"%d \"%[ a-zA-Z]\"", &masivs[i]->id, masivs[i]->nosaukums);

        }
        while(fscanf(inFile,"%d ", &mainigais)!=EOF)
        {
            for (int i = 0; i < rakstuSkaits; i++)
            {
                if (mainigais == masivs[i]->id)
                {
                    if (masivs[i]->norade == 0)
                    {
                        masivs[i]->norade = new komentari;
                        masivs[i]->norade->next=0;
                        masivs[i]->norade->previous=0;

                    }
                    else
                    {
                        masivs[i]->norade->next= new komentari;
                        masivs[i]->norade->next->next=0;
                        masivs[i]->norade->next->previous = masivs[i]->norade;
                        masivs[i]->norade = masivs[i]->norade->next;
                    }
                    fscanf(inFile, "%s", masivs[i]->norade->koments);
                    break;
                }
            }
        }
        virsraksti*tmp;
        for (int i=0; i < rakstuSkaits-1;)
        {
            if (masivs[i]->id > masivs[i+1]->id){
                tmp = masivs[i];
                masivs[i] = masivs[i+1];
                masivs[i+1] = tmp;
                  i--;if(i<0)i=0;
            }else{
                i++;
            }

        }
        for (int i=0; i < rakstuSkaits; i++)
        {
            fprintf(outFile, "%s\n", masivs[i]->nosaukums);
            if (masivs[i]->norade==0) fprintf(outFile, "-");
            while (masivs[i]->norade != 0 )
            {
                fprintf(outFile, "%s ", masivs[i]->norade->koments);
                if (masivs[i]->norade->previous != 0)
                {
                    masivs[i]->norade= masivs[i]->norade->previous;
                    delete masivs[i]->norade->next;
                }
                else
                {
                    delete masivs[i]->norade;
                    masivs[i]->norade=0;
                }
            }
            fprintf(outFile, "\n");

        }
        for (int i=0; i<rakstuSkaits; i++)
        {
                delete masivs[i];
        }
    }

    fclose(inFile);
	fclose(outFile);
    return 0;

}
