#include <stdio.h>
#include <stdlib.h>

#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#include <string.h>
#include <errno.h>

#include <sys/stat.h>

#include <dirent.h>

#include <math.h>
char* sizes[5] = {"B","KB","MB","GB","TB"};
int dir_size(char *path)
{
	int dirsize = 0;
	DIR *dir = opendir(path);
	if (dir == NULL)
		printf("Error: %s\n", strerror(errno));
	struct dirent *dirdata;
	struct stat filedata;

	while (dirdata = readdir(dir)) {
		//file's actual path
		char filepath[256];
		strcpy(filepath, path);
		if (filepath[strlen(filepath) - 2] != '/')
			strcat(filepath, "/");
		strcat(filepath, dirdata->d_name);

		//if file is a directory
		if (dirdata->d_type == DT_DIR) {
			if (strcmp(dirdata->d_name, ".")) {
				if (strcmp(dirdata->d_name, ".."))
					dirsize += dir_size(filepath);
			}
		} else {
			stat(filepath, &filedata);
			dirsize += (int) (filedata.st_size);
		}
	}

	return dirsize;
}

void list_dir(char *path)
{
	DIR *dir = opendir(path);
	struct dirent *dirdata;

	while (dirdata = readdir(dir)) {
		//file's actual path
		char filepath[256];
		strcpy(filepath, path);
		if (filepath[strlen(filepath) - 2] != '/')
			strcat(filepath, "/");
		strcat(filepath, dirdata->d_name);

		//if file is a directory
		if (dirdata->d_type == DT_DIR) {
			if (strcmp(dirdata->d_name, ".")) {
				if (strcmp(dirdata->d_name, "..")) {
					printf("\t%s%s%s\n", ANSI_GREEN, filepath, ANSI_RESET);
					list_dir(filepath);
				}
			}
		}
	}
}

void file_dir(char *path,char *basepath)
{
	DIR *dir = opendir(path);
	struct dirent *dirdata;
	struct stat filedata;

	while (dirdata = readdir(dir)) {
		//file's actual path
		char filepath[256];
		strcpy(filepath, path);
		if (filepath[strlen(filepath) - 2] != '/')
			strcat(filepath, "/");
		strcat(filepath, dirdata->d_name);

		//if file is a directory
		if (dirdata->d_type == DT_DIR) {
			if (strcmp(dirdata->d_name, ".")) {
				if (strcmp(dirdata->d_name, ".."))
					file_dir(filepath,basepath);
			}
		} else {
			stat(filepath, &filedata);
            char size[15];
            int dare = log(filedata.st_size)/log(1024);

            char loc = 0;
            while(basepath[loc]!=path[loc]&&path[loc]!=0) loc++;
            char permstr[10];
            permstr[9] = 0;
            for(int i = 0;i<3;i++){
                if((int)pow(2,8-i*3)&(int)filedata.st_mode) permstr[i*3] = 'r';
                else permstr[i*3] = '-';
                if((int)pow(2,8-i*3-1)&(int)filedata.st_mode) permstr[i*3+1] = 'w';
                else permstr[i*3+1] = '-';
                if((int)pow(2,8-i*3-2)&(int)filedata.st_mode) permstr[i*3+2] = 'x';
                else permstr[i*3+2] = '-';            
            }
			printf("\t%s/%s %.1f%s %s\n",path+loc,dirdata->d_name, filedata.st_size/pow(1024,dare),sizes[dare],permstr);
                
		}
	}
}

int main(int argc, char *argv[])
{
	/**********   get directory path   ***********/
	char dirname[256];
	if (argc == 1) {
		printf("Specify directory: ");
		scanf("%s", dirname);
	} else
		strcpy(dirname, argv[1]);

	int dirsize = dir_size(dirname);
	printf("\nTotal Directory Size: %d bytes/%lf KB\n", dirsize, dirsize / 1024.);

	printf("\nDirectories:\n");
	printf("\t%s.%s\n", ANSI_GREEN, ANSI_RESET);
	printf("\t%s..%s\n", ANSI_GREEN, ANSI_RESET);
	list_dir(dirname);
	printf("Regular files:\n");
	file_dir(dirname,dirname);

	return 0;
}
