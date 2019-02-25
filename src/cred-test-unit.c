/**
 *  CREDENTIAL ADT : automatated unit test driver
 *
 *  COMP220: Assignment 3
 *  Author:  Joseph Fall
 *  Date:    Feb. 1, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "credential.h"

/*
* Run a single test case
* Report on failed test
* Return 0 if test successful, 1 otherwise
*/

int run_test(int result, int expected, char* msg) 
{
   if (result != expected)
   {
      printf("\nTest failed: %s \n\tFunction returned %d but expected %d\n", msg, result, expected);
      return(1);
   }
   return(0);
}

/*
 * Run a series of unit tests cases.
 * Report on failed tests.
 */
void main()
{
   int i;
   int failed_test_counter = 0;
   printf("Unit Test Suite for Credential ADT operations...\n");
   
   // Test 1: Constructor
   Credential c = credCreate("BSc.", "UBC", "Bob");
   printf("1");
   failed_test_counter += run_test(strcmp(c.name, "BSc."), 0, "Constructor fails to set credential name.");
   failed_test_counter += run_test(strcmp(c.issuer, "UBC"), 0, "Constructor fails to set credential issuer.");
   failed_test_counter += run_test(strcmp(c.receiver, "Bob"), 0, "Constructor fails to set credential receiver.");
   printf(".");
   
   
   // Test 2: Serialize the credential
   printf("2");
   int slen = credSerialLen(c);
   printf("\nAllocating bytes to serialize credential: %d\n", slen);
   char buf[slen+1];
   buf[0] = '\0';
   credSerialize(c, buf);
   failed_test_counter += run_test(strlen(buf)<=slen, true, "Serialized Credential exceeds expected length.");
   printf("\nSerialized Credential: %s\n\n", buf);
   
   // Test 3: Destructor
   printf("3");
   credDelete(&c);
   printf(".");

   printf("\n\nUnit Test Suite Complete: ");
   if (failed_test_counter == 0) printf("ALL TESTS PASSED\n");
   else printf("FAILED %d TESTS\n", failed_test_counter);
   
}