#ifndef _INPUT_HANDLING_H_
#define _INPUT_HANDLING_H_

/* add your include and prototypes here*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dyn_survey.h"


/* input handling functions */
int tokenize_line(char *line, char **phrases, char *delimiter);
int process_tests(char **phrases, int num_phrases, short *tests);
int process_questions(char **phrases, int num_phrases, char **questions);
void process_question_types(char **phrases, int num_phrases, short *question_types);
int process_likert_level_descriptions(char **phrases,  int num_phrases, char **likert_level_descriptions);
void process_response(char **phrases, int num_phrases, short *question_types, Response *responses, int num_respondents);
int process_num_responses(char **phrases);
short convert_response_to_scale(char *token, short direct_scale);
void process_filters(char **phrases, int num_phrases, char **filters);
void filter_responses(char **filters, Response *responses, int num_responses);
#endif
