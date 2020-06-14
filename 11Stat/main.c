#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

char *convert(int mode)
{
	switch (mode) {
		case 0:
			return "---";
		case 1:
			return "--x";
		case 2:
			return "-w-";
		case 3:
			return "-wx";
		case 4:
			return "r--";
		case 5:
			return "r-x";
		case 6:
			return "rw-";
		case 7:
			return "rwx";
	}
	return "invalid number";
}

char *is_dir(struct stat f)
{
	if ((f.st_mode & S_IFMT) == S_IFDIR) //if file type of file is a directory
		return "d";
	return "-";
}

int main()
{
	char fs[256];
	struct stat file;
	stat("makefile", &file);

	printf("SIZE INFO:\n");
	sprintf(fs, "%ld bytes/%lf KB/%lf MB/%lf GB/%ld bits", file.st_size, file.st_size / 1024.0, file.st_size / 1024.0 / 1024, file.st_size / 1024.0 / 1024 / 1024, file.st_size * 8);
	printf("size of the makefile is %s\n", fs);

	printf("\nMODE INFO:\n");
	int mode = file.st_mode;
	printf("mode of the makefile: %d\n", file.st_mode);

	int friendly_mode = mode % 512;
	// this gave us the last 9 bits, so we gotta do some work now
	int other = friendly_mode % 8;
	int group = (friendly_mode / 8) % 8;
	int user = (friendly_mode / 64) % 8;
	printf("ls -l form of mode of the makefile: %s%s%s%s\n", is_dir(file), convert(user), convert(group), convert(other));

	printf("\nTIME INFO:\n");
	time_t t = file.st_atime;
	printf("time of last acess: %s\n", ctime(&t));

	return 0;
}
