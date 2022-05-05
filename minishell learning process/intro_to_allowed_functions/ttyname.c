// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     char *term;

//     term = ttyname(0);
//     printf("This is terminal %s\n",term);

//     return(0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main()
// {
//     char *term;
//     FILE *tout;

//     /* obtain terminal name and open */
//     term = ttyname(0);
//     tout = fopen(term,"w");
//     if( tout==NULL )
//     {
//         fprintf(stderr,"Unable to open %s\n",term);
//         exit(1);
//     }

//     /* send text to the terminal */
//     fprintf(tout,"Hello, terminal %s\n",term);

//     /* close */
//     fclose(tout);

//     return(0);
// }



 #include <unistd.h>       /* See NOTES */
 #include <stdio.h>
int main()
{
	int i;
    i = ttyslot();
	printf("%d \n", i);
}