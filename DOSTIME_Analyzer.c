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
