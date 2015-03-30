#pragma once

void initialize_ecc (void);
int check_syndrome (void);
void decode_data (unsigned char data[], int nbytes);
void encode_data (unsigned char msg[], int nbytes, unsigned char dst[]);
