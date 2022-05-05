// #include <stdio.h>
// #include <dirent.h>

// int main (int argc, char *argv[])
// {
// 	struct dirent *pDirent;
// 	DIR *pDir;

// 	// Ensure correct argument count.

// 	if (argc != 2) {
// 		printf ("Usage: testprog <dirname>\n");
// 		return 1;
// 	}

// 	// Ensure we can open directory.

// 	pDir = opendir (argv[1]);
// 	if (pDir == NULL) {
// 		printf ("Cannot open directory '%s'\n", argv[1]);
// 		return 1;
// 	}

// 	// Process each entry.

// 	while ((pDirent = readdir(pDir)) != NULL) {
// 		printf ("[%s]\n", pDirent->d_name);
// 	}

// 	// Close directory and exit.

// 	closedir (pDir);
// 	return 0;
// }



// #include <stdio.h>
// #include <dirent.h>
// #include <string.h>

// int main()
// {
//     DIR *dir;
//     struct dirent *dp;
//     char * file_name;
//     dir = opendir(".");
//     while ((dp=readdir(dir)) != NULL) {
//         printf("debug: %s\n", dp->d_name);
//         if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
//         {
//             // do nothing (straight logic)
//         } else {
//             file_name = dp->d_name; // use it
//             printf("file_name: \"%s\"\n",file_name);
//         }
//     }
//     closedir(dir);
//     return 0;
// }
