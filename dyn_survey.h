#ifndef _DYN_SURVEY_H_
#define _DYN_SURVEY_H_

/* add your library includes, constants and typedefs here*/


/*
 * Library includes
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Compile-time constants
 */
#define NUMBER_TESTS 3
#define NUMBER_QUESTIONS 38
#define NUMBER_LIKERT_LEVELS 6
#define NUMBER_SCORES 5
#define MAX_NUMBER_PHRASES 50
#define MAX_PHRASE_LENGTH 120
#define MAX_NUMBER_RESPONSES 50
#define MAX_WORD_LENGTH 20
#define MAX_QUESTION_LENGTH 120
#define MAX_LINE_LENGTH 3000
#define MAX_NUMBER_FILTERS 3

/* defining the structs used */
typedef struct{
    char *major;
    short canada_born; /* 1 if yes, 0 if no */
    char *birthday;
    short filter_flag; /* 1 is yes, 0 if no */
} Respondent;

typedef struct{
    Respondent *respondent;
    short *answers;
} Response;

#endif
