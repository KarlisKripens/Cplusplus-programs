#include "stdio.h"
#include "stdlib.h"
int main()
{
	FILE* inFile;
	FILE* outFile;
	inFile = fopen("komanda.in", "r");
	outFile = fopen("komanda.out", "w+");
	unsigned arr[10000][3];
	int i = 0;
	int j,jj;
	bool isParent;
	unsigned root = 0;
	unsigned rootChildWomen = 0;
	unsigned rootChildMen = 0;
    while(fscanf(inFile, "%u %u %u", &arr[i][0], &arr[i][1], &arr[i][2]) != EOF)
    {
        if(!arr[i][0]) break;
        isParent = false;
        for(j = 0;j<=i;j++)
        {
            if(arr[i][0] == arr[j][1] || arr[i][0] == arr[j][2])
            {
                isParent = true;
                break;
            }
        }
        if(!isParent)
        {
            root = arr[i][0];
            rootChildWomen = arr[i][1];
            rootChildMen = arr[i][2];
        }
        i++;
    }
    unsigned arrOrdered[i*2];
    int k = 0;
    arrOrdered[k] = root;
    arrOrdered[++k] = '\0';
    int checkFrom = k + 1;
    if(rootChildWomen) arrOrdered[++k] = rootChildWomen;
    if(rootChildMen) arrOrdered[++k] = rootChildMen;
    arrOrdered[++k] = '\0';
    int checkTo = k;
    int countLevels = 0;
    while(arrOrdered[k] != arrOrdered[k-1]){
        for(j = checkFrom;j <= checkTo;j++)
        {
            if(arrOrdered[j] != '\0')
            {
                for(jj = 0;jj <= i;jj++)
                {
                    if(arrOrdered[j] == arr[jj][0])
                    {
                        if(arr[jj][1]) arrOrdered[++k] = arr[jj][1];
                        if(arr[jj][2]) arrOrdered[++k] = arr[jj][2];
                        break;
                    }
                }
            }
        }
        arrOrdered[++k] = '\0';
        checkFrom = checkTo + 1;
        checkTo = k;
        countLevels++;
    }
    bool first = true;
    for(j = k-1; j>=0 ;j--)
    {
        if(!first && arrOrdered[j] == '\0')
        {
            for(jj = j + 1;jj < checkTo;jj++)
            {
                /*printf(" %u",arrOrdered[jj]);*/
                fprintf(outFile," %u",arrOrdered[jj]);
            }
        }
        if(arrOrdered[j] == '\0')
        {
            checkTo = j;
            if(first)
                first = false;
            else
                /*printf("\n");*/
                fprintf(outFile,"\n");

            /*printf("%u:",countLevels);*/
            fprintf(outFile,"%u:",countLevels);
            countLevels--;
        }
    }
    /*printf(" %u",arrOrdered[0]);*/
    fprintf(outFile," %u",arrOrdered[0]);
    fclose(inFile);
    fclose(outFile);
	return 0;
}
