#ifndef _OUTPUT_H_
#define _OUTPUT_H_

/* add your include and prototypes here*/

#include <stdio.h>
#include "dyn_survey.h"

/* output functions */
void print_output(short *tests, int num_tests, char **questions, int num_questions, char **likert_level_descriptions, 
    int num_likert_levels, Response *responses, int num_respondents, double **frequencies, double **scores, double *average_scores, int num_responses, int valid_respondent_count);

#endif
