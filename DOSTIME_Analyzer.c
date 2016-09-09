/* -
 * Copyright (c) 2006-2017 All rights reserved.
 *    Department of Computer Hacking and Information Security
 *                Sejong Univerity
 *
 * This code is contributed by Ki-Woong Park
 * at Sejong University Dept. Information Security
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *  
 *  Author : Ki-Woong Park  Sejong University
 *  E-mail : woongbak@sejong.ac.kr
 */

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define LENGTH 250

void dumpcode(unsigned char *buff, int len);
void printchar(unsigned char c);
int unix2dostime (int year, int month, int day, int hour, int min, int sec);
int isLittleEndian();
void dos2unixtime(int dostime);
int LittleEndian_to_BigEndian(int num);
unsigned int extract_hex(const char *src);


int main()
{
	char input_buffer[251];
	int count = 0;
	unsigned int before_endian = 0;
	unsigned int after_endian = 0;

	printf("This program is intended to translate 8 Hex values into human-readable time format.\n\n");
	printf("Input (8 Hex Value): ");
	
	count = input_string(input_buffer);
	
	if(count != 8) return -1;

	before_endian = extract_hex(input_buffer);

	if(isLittleEndian())
	{
		after_endian = LittleEndian_to_BigEndian(before_endian);
	}
	else
	{
		after_endian = before_endian;
	}

	dos2unixtime(after_endian);
	printf("%x\n", unix2dostime (2013, 3, 27, 12, 0, 0));

	getchar();
	return 0;

}

int input_string(char * s)
{
	char *t = 0;
	int size = 0;
	int len;
	do
	{
		s[LENGTH-2] = 0;
		fgets(s, LENGTH, stdin);
		len = strlen(s);
		size += len;
		t = realloc(t, size);
		strcat(t, s);
	} while(len == LENGTH-1 && s[LENGTH-2] != '\n');
	return len-1;
}



int isLittleEndian()
{
   unsigned num = 0xABCD; 
   return (*((unsigned char*)&num) == 0xCD);
}



int unix2dostime (int year, int month, int day, int hour, int min, int sec)
{
  return ((year-1980) << 25
	  | (month) << 21
	  | day << 16
	  | hour << 11
	  | min << 5
	  | sec >> 1);
}



int LittleEndian_to_BigEndian(int num)
{
	return ((num>>24)&0xff) | // move byte 3 to byte 0
           ((num<<8)&0xff0000) | // move byte 1 to byte 2
           ((num>>8)&0xff00) | // move byte 2 to byte 1
           ((num<<24)&0xff000000); // byte 0 to byte 3
}

unsigned int extract_hex(const char *src)
{
	int errno;
    char hex_low[4 + 1] = { 0 };
    char hex_high[4 + 1] = { 0 };
    unsigned int val;
	unsigned long val2;

    if (strlen(src) < 8)
        return -1;

    memcpy(hex_low, src+4, 4);
    memcpy(hex_high, src, 4);

    if (strspn(hex_low,"0123456789AaBbCcDdEeFf") < 4)
        return -1;
    if (strspn(hex_high,"0123456789AaBbCcDdEeFf") < 4)
        return -1;

    val = strtol(hex_high, NULL, 16) << 16;
    val += strtol(hex_low, NULL, 16);

	return val;
}