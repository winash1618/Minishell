
#include "sample.h"
struct sample g_m;

int count;
int main()
{
	g_m.a = 2;
	

	count = 1;
	printf("%d %d \n", count, g_m.a);
	func();
	free(g_m.s);
	return (0);

}

// int main()
// {
//     char **str;
//     str = (char **)malloc(sizeof(char *) * 5);

//     char *s1;
//     char *s2;
//     char *s3;
//     char *s4;
//     s1 = (char *)malloc(sizeof(char) * 10);
//     s2 = (char *)malloc(sizeof(char) * 10);
//     s3 = (char *)malloc(sizeof(char) * 10);
//     s4 = (char *)malloc(sizeof(char) * 10);
//     int i = 0;
//     while(i< 9)
//     {
//         s1[i] = 'a';
//         s2[i] = 'a';
//         s3[i] = 'a';
//         s4[i] = 'a';
//         i++;
//     }
//     s1[i] = '\0';
//     s2[i] = '\0';
//     s3[i] = '\0';
//     s4[i] = '\0';
//     *str = s1;
//     str++;
//     *str = s2;
//     str++;
//     *str = s3;
//     str++;
//     *str = s4;
//     str++;
//     *str = NULL;

//     return(0);
// }

