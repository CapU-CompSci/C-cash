/**
 *  Credential ADT : private implementation / algorithms
 *      A single credential issued from one party to another
 * 
 *  COMP220: Assignment 3
 *  Author:  Joseph Fall
 *  Date:    Feb. 1, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <assert.h>

#include "credential.h"

// max characters in an int converted to string rep. (not really appropriate, but can't find in std. lib.)
#define INT_LEN 10

/***********************
 * CREDENTIAL record private implementation details
 *   --> storage for a single C-cred transaction
 ***********************/
// Definitions used for serializing Credential recrods
const char* CRED_SERIAL_FORMAT = "<%s:%s:%s:%s>";   // format for serialized records
const int CRED_SERIAL_DELIMS = 5;                   // number of delimiter characters used to serialize a record
const int TIMESTAMP_BUFFER_LEN = 80;

/*
 * Constructor - return a new, timestamped credential with a unique id
 * POST: credential is created with a DEEP COPY of parameter data
 */
Credential credCreate(char* name, char* issuer, char* reciever) {
    char* n = calloc(strlen(name)+1, sizeof(char));
    strcpy(n, name);
    char* i = calloc(strlen(issuer)+1, sizeof(char));
    strcpy(i, issuer);
    char* r = calloc(strlen(reciever)+1, sizeof(char));
    strcpy(r, reciever);
    time_t t = time(NULL);
    Credential c = {n, i, r, t};
    return c;
}

/*
 * Destructor - remove all data and free all memory associated with the credential 
 * POST: credential is no longer valid
 */
 void credDelete( Credential *c ) {
    free(c->name);
    c->name = NULL;
    free(c->issuer);
    c->issuer = NULL;
    free(c->receiver);
    c->receiver = NULL;
}

// Helper function
void _serializeTimestamp(time_t timestamp, char* buf, int len) {
    const char* fmt = "%x (%X)";
    strftime(buf, len, fmt, localtime( &timestamp ));

   // CODE FOR READING A FORMATTED DATE/TIME back into a timestamp
   //struct tm timestruct;
   //strptime (formatted_datetime, fmt, &timestruct);
   //assert(mktime(&timestruct) == r.timestamp);

}

/*
 * Print a text representation of this credential on STDOUT
 */
void credPrint(const Credential c) {
    char formatted_datetime[TIMESTAMP_BUFFER_LEN];
    _serializeTimestamp(c.timestamp, formatted_datetime, TIMESTAMP_BUFFER_LEN);
    printf("   <%s issued \"%s\" to %s> at %s \n", c.issuer, c.name, c.receiver, formatted_datetime);
}

/*
 * Compute and return buffer size required to hold serialized credential
 */
int credSerialLen(const Credential c) {
   return strlen(c.name) + strlen(c.issuer) + strlen(c.receiver) + TIMESTAMP_BUFFER_LEN + CRED_SERIAL_DELIMS;  // max. char length of serialized record
}

/*
 * Generate a serialzied text representation of this credential, store in buffer as a C-string
 * PRE: capacity of buffer is at least credSerialLen(c)+1 in length
 */
void credSerialize(const Credential c, char* buffer) {
    char formatted_datetime[TIMESTAMP_BUFFER_LEN];
    _serializeTimestamp(c.timestamp, formatted_datetime, TIMESTAMP_BUFFER_LEN);
   sprintf(buffer, CRED_SERIAL_FORMAT, c.issuer, c.name, c.receiver, formatted_datetime);
}

