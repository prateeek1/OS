#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#include<sys/types.h> //pid_t
int main()
{

    printf("Enter n\n");
    int n;
    scanf("%d", &n);
    int a[n];

    printf("Enter the elements of array\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int pid = fork();

    // pid_t pid;

    if (pid < 0)
    {
        printf("fork is failed\n");
        exit(1);
    }

    else if (pid == 0) // child process will execute
    {
        printf("Inside Child\n");


        int sum = 0;

        for (int i = 0; i < n; i++)
        {
            if (a[i] % 2 != 0)
                sum += a[i];
        }

        printf("%d\n", sum);
    }

    else if (pid > 0) // parent process will exexute
    {

        wait(NULL);   // or wait(&status)

        printf("Inside parent\n");


        int sum = 0;

        for (int i = 0; i < n; i++)
        {
            if (a[i] % 2 == 0)
                sum += a[i];
        }


        printf("%d\n", sum);

    }


    return 0;
}