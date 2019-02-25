/**
 *  Credential ADT : public interface
 *      A single credential issued from one party to another
 * 
 *  COMP220: Assignment 3
 *  Author:  Joseph Fall
 *  Date:    Feb. 1, 2019
 */
 
/*******************
 * PRIVATE TYPE DECLARATIONS
 ********************/
typedef struct  {
    char* name;      // name of the credential
    char* issuer;    // username of the entity issueing this credential
    char* receiver;  // username of the entity receiving this credential
    time_t timestamp; // timestamp for this credential (issue date)
    // Other important information for future versions:
    // unique id, credential type, level, designations, number of credits, area of study, etc.
    // institutional digital signature, contact info, etc.
} Credential;


/*********************
 *  PUBLIC INTERFACE
 *********************/
/*
 * Constructor - return a new, timestamped credential with a unique id
 * POST: credential is created with a DEEP COPY of parameter data
 */
Credential credCreate(char* name, char* issuer, char* reciever);

/*
 * Destructor - remove all data and free all memory associated with the credential 
 * POST: credential is no longer valid
 */
 void credDelete( Credential *credential ); 

/*
 * Print a text representation of this credential on STDOUT
 */
void credPrint( const Credential credential); 

/*
 * Compute and return buffer size required to hold serialized credential
 */
int credSerialLen(const Credential credential);

/*
 * Generate a serialzied text representation of this credential, store in buffer as a C-string
 * PRE: capacity of buffer is at least credSerialLen(list)+1 in length
 */
void credSerialize(const Credential credential, char* buffer);
