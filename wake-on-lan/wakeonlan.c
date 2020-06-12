#include <stdio.h>
#include <stdlib.h>	//to use system()
#include <string.h> //to use strcpy()

int main()
{
	char command[10][27];
	char wols[] = "wakeonlan ";

	for(int i = 0; i<10; i++)
	{
		for(int j = 0; j<10; j++)
			command[i][j] = wols[j];
		
	}

	FILE* fp = fopen("mac-list.txt", "r");

	for(int l = 0; l<10; l++)
	{
		char mac[17];
		fscanf(fp, "%s", mac);
		for(int m = 10; m<27; m++)
		{
			command[l][m] = mac[m-10];
		}
	}

	fclose(fp);
	
	for(int k = 0; k<10; k++)
	{
		char runCommand[27];
		for(int n = 0; n<27; n++){ runCommand[n] = command[k][n]; }
		system(runCommand);
		printf("%s\n", runCommand);
	}
	
	return 0;
}