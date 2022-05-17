/* This program prints the size of all files in the current directory. */
/* reference:
http://web.eecs.utk.edu/~jplank/plank/classes/cs360/360/notes/Prsize/lecture.html */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define DIRECTORY "/home/deon/srtp_demo/test_folder/"
#define MAX_SIZE 100

int main()
{
   DIR *d;            /* Return value of opendir(). */
   struct dirent *de; /* Return value of each readdir() call. */
   struct stat buf;   /* The information about each file returned by stat() */
   int exists;        /* Return value of stat on each file. */
   long total_size;   /* The total size of all files. */
   char file_name[MAX_SIZE] = {0};

   d = opendir(DIRECTORY); /* Open "." to list all the files. */
   if (d == NULL)
   {
      perror(".");
      exit(1);
   }

   total_size = 0;

   /* Run through the directory and run stat() on each file,
      keeping track of the total size of all of the files.  */

   for (de = readdir(d); de != NULL; de = readdir(d))
   {
      memset(file_name, 0, MAX_SIZE);
      strcpy(file_name, DIRECTORY);
      strcat(file_name, de->d_name);
      exists = stat(file_name, &buf);
      if (exists < 0)
      {
         fprintf(stderr, "Couldn't stat %s\n", file_name);
      }
      else
      {
         if ((strcmp(file_name, DIRECTORY ".") != 0) && (strcmp(file_name, DIRECTORY "..") != 0))
         {
            total_size += buf.st_size;
         }
      }
   }

   /* Although the closedir call isn't necessary, it will be later... */

   closedir(d);
   printf("%ld\n", total_size);
   return 0;
}