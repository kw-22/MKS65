#include <stdio.h>
#include <stdlib.h>

int my_strlen(char *s)
{
	int ans = 0;
	while (*s) {
		ans++;
		s++;
	}
	return ans;
}

char *my_strcpy(char *dest, char *source)
{
	int offset = 0;

	//copy each char
	while (source[offset]) {
		dest[offset] = source[offset];
		offset++;
	}
	//add terminating null
	dest[offset] = '\0';
	return dest;
}

char *my_strncpy(char *dest, char *source, int n)
{
	int i;

	//copy n bytes
	for (i = 0; i < n && source[i] != '\0'; i++) dest[i] = source[i];
	return dest;
}

char *my_strcat(char *dest, char *source)
{
	//grab the null terminator
	char* start = dest;
	while (*dest)
		dest++;

	//now add the things in source
	while (*source) {
		*dest = *source;
		dest++;
		source++;
	}
	return start;
}

char *my_strncat(char *dest, char *source, int n)
{
	//grab the null terminator
	char* start = dest;
	while (*dest)
		dest ++;

	//now add the things in source, but this time stop after n
	while (*source && n) {
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	return start;
}

int my_strcmp(char *s1, char *s2)
{
	//compare byte by byte
	while (*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	//return difference if they're different
	return *s1 - *s2;
}

char *my_strchr(char *s, char c)
{
	while (*s) { //while still in the string
		if (*s == c) return s;
		s++;
	}
	//if we're looking for null char
	if (c == '\0') return s;
	//if char not found
	return '\0';
}

char *my_strstr(char *s1, char *s2) {
	char *s1_init = s1;
	char *s2_init = s2;
	while (*s1) {
		//if chars are different, move to next char in s1
		if (*s1 != *s2) {
			s1++;
			s1_init = s1;
			s2 = s2_init;
		} else {
			s1++;
			s2++;
			if (!*s2) return s1_init;
		}
		if (!*s1) return 0x0;
	}
	return 0x0; //gets rid of warning
}
