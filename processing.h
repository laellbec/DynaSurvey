#ifndef _PROCESSING_H_
#define _PROCESSING_H_

/* add your include and prototypes here*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dyn_survey.h"

/* processing functions */
void compute_frequencies(double **frequencies, int num_questions, Response *responses, int num_respondents);
int compute_scores(double **scores, short *question_types, Response *responses, int num_respondents);
void compute_average_scores(double *average_scores, double **scores, int num_respondents);
double compute_c(Response *response, short *question_types);
double compute_i(Response *response, short *question_types);
double compute_g(Response *response, short *question_types);
double compute_u(Response *response, short *question_types);
double compute_p(Response *response, short *question_types);



#endif
