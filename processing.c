#include "processing.h"
#include "dyn_survey.h"

/* compute Likert item relative frequencies */
void compute_frequencies(double **frequencies, int num_questions, Response *responses, int num_respondents) {
    for (int i = 0; i < num_questions; i++) {
        int filtered_respondents = 0;
        /* compute absolute frequencies first */
        for (int j = 0; j < num_respondents; j++) {
            if(responses[j].respondent->filter_flag){
                frequencies[i][responses[j].answers[i]-1]++;
                filtered_respondents++;
            }
        }
        /* compute relative percentual frequencies */
        for (int k = 0; k < NUMBER_LIKERT_LEVELS; k++) {
            if (num_respondents > 0) {
                frequencies[i][k] = 100.0 * frequencies[i][k] / ((double)filtered_respondents);
            }
            else {
                frequencies[i][k] = 0;
            }
        }
    }
    return;
}


/* compute scores for each respondent returning the number of valid responses to use in later functions */
int compute_scores(double **scores, short *question_types, Response *responses, int num_respondents) {
    int valid_respondent_index = 0;
    for (int i = 0; i < num_respondents; i++) {
        if(responses[i].respondent->filter_flag){
            scores[valid_respondent_index][0] = compute_c(&responses[i], question_types);
            scores[valid_respondent_index][1] = compute_i(&responses[i], question_types);
            scores[valid_respondent_index][2] = compute_g(&responses[i], question_types);
            scores[valid_respondent_index][3] = compute_u(&responses[i], question_types);
            scores[valid_respondent_index][4] = compute_p(&responses[i], question_types);
            valid_respondent_index++;
        }
       
    }
    return valid_respondent_index;
}


/* compute Confidence score */
double compute_c(Response *response, short *question_types) {
    int sum = 0;
    for (int i=0; i<=7; i++) {
        if (question_types[i]) {
            sum += response->answers[i];
        }
        else {
            sum +=  7 - response->answers[i];
        }
    }
    return sum / 8.0;
}

/* compute Interest score */
double compute_i(Response *response, short *question_types) {
    int sum = 0;
    for (int i=8; i<=17; i++) {
        if (question_types[i]) {
            sum += response->answers[i];
        }
        else {
            sum +=  7 - response->answers[i];
        }
    }
    return sum / 10.0;
}

/* compute Gender score */
double compute_g(Response *response, short *question_types) {
    int sum = 0;
    for (int i=18; i<=27; i++) {
        if (question_types[i]) {
            sum += response->answers[i];
        }
        else {
            sum +=  7 - response->answers[i];
        }
    }
    return sum / 10.0;
}

/* compute Usefulness score */
double compute_u(Response *response, short *question_types) {
    int sum = 0;
    for (int i=28; i<=33; i++) {
        if (question_types[i]) {
            sum += response->answers[i];
        }
        else {
            sum +=  7 - response->answers[i];
        }
    }
    return sum / 6.0;
}

/* compute Professional score */
double compute_p(Response *response, short *question_types) {
    int sum = 0;
    for (int i=34; i<=37; i++) {
        if (question_types[i]) {
            sum += response->answers[i];
        }
        else {
            sum +=  7 - response->answers[i];
        }
    }
    return sum / 4.0;
}


/* Compute average scores per respondent */
void compute_average_scores(double *average_scores, double **scores, int num_respondents) {
    for (int i = 0; i < NUMBER_SCORES; i++) {
        average_scores[i] = 0.0;
        for (int j = 0; j < num_respondents; j++) {
            average_scores[i] += scores[j][i];
        }
        if (num_respondents > 0) {
            average_scores[i] /= ((double)num_respondents);
        }
    }
    return;
}
