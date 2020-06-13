#include <stdio.h>
#include <stdlib.h> //to use system()
#include <string.h> //to use strcpy() and strcat()

int main()
{

    char runCommand[] = "traceroute "; //use tracert for windows OS, traceroute -4 for ipV4 in windows
    char trailCommand[] = " > trace.txt";


    printf("\nEnter the domainname.com or IP address of the server\n");

    char domain[100];
    scanf("%s", domain);

    strcat(runCommand, domain);
    strcat(runCommand, trailCommand);
    system(runCommand);


    printf("\n Opening trace.txt....\n");
    system("vi trace.txt"); //replace vi with start in Windows OS.
    
    return 0;
}
