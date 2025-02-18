#include "input_handling.h"
#include "processing.h"
#include "output.h"
#include "dyn_survey.h"
#include "emalloc.h"
/*
 * Main program and functions
 */

/* main function: handles input, processes data, prints output */
int main(int argc, char *argv[]){
    if (argc != 1) {
            printf("Usage: %s\n", argv[0]);
            printf("Should receive no parameters\n");
            printf("Read from the stdin instead\n");
            exit(1);
    }

    /* declaration and initialization of local variables */

    int num_phrases = 0;
    char **phrases = (char **)emalloc(MAX_NUMBER_PHRASES * sizeof(char *));
    for (int i = 0; i<MAX_NUMBER_PHRASES; i++){
        phrases[i] = (char *)emalloc(MAX_PHRASE_LENGTH * sizeof(char));
    }

    int num_tests = 0;
    short *tests = (short *)emalloc(NUMBER_TESTS*sizeof(short));

    int num_questions = 0;
    char **questions = (char **)emalloc(NUMBER_QUESTIONS * sizeof(char *));
    for (int i = 0; i<NUMBER_QUESTIONS; i++){
        questions[i] = (char *)emalloc(MAX_QUESTION_LENGTH * sizeof(char));
    }

    short *question_types = (short *)emalloc(NUMBER_QUESTIONS * sizeof(short));
    
    int num_likert_levels = 0;
    char **likert_level_descriptions = (char **)emalloc(NUMBER_LIKERT_LEVELS * sizeof(char *));
    for (int i = 0; i<NUMBER_LIKERT_LEVELS; i++){
        likert_level_descriptions[i] = (char *)emalloc(MAX_WORD_LENGTH * sizeof(char ));
    }

    int num_responses = 0;
    int num_respondents = 0;

    Response *responses = (Response *)emalloc(MAX_NUMBER_RESPONSES * sizeof(Response));
    for (int i = 0; i<MAX_NUMBER_RESPONSES; i++){
        responses[i].respondent = (Respondent *)emalloc(sizeof(Respondent));
        responses[i].respondent->major = (char *)emalloc((MAX_PHRASE_LENGTH)*sizeof(char));
        responses[i].respondent->canada_born = 0; // initialized to false 
        responses[i].respondent->birthday = (char *)emalloc(MAX_PHRASE_LENGTH*sizeof(char));
        responses[i].respondent->filter_flag = 1; // initialized to true
        responses[i].answers = (short *)emalloc(NUMBER_QUESTIONS*sizeof(short));
        for (int j = 0; j<NUMBER_QUESTIONS; j++){
            responses[i].answers[j] = 0;
        }
    }

    double **scores = (double **)emalloc(MAX_NUMBER_RESPONSES * sizeof(double *));
    for(int i = 0; i<MAX_NUMBER_RESPONSES; i++){
        scores[i] = (double *)emalloc(NUMBER_SCORES * sizeof(double));
        for(int j = 0; j< NUMBER_SCORES; j++){
            scores[i][j] = 0.0;
        }
    }

    double *average_scores = (double *)emalloc(NUMBER_SCORES * sizeof(double));

    double **frequencies = (double **)emalloc(NUMBER_QUESTIONS * sizeof(double *));
    for (int i = 0; i<NUMBER_QUESTIONS; i++){
        frequencies[i] = (double *)emalloc(NUMBER_LIKERT_LEVELS * sizeof(double));
        for(int j = 0; j<NUMBER_LIKERT_LEVELS; j++){
            frequencies[i][j] = 0.0;
        }
    }

    char **filters = (char **)emalloc(MAX_NUMBER_FILTERS *sizeof(char *));
    for (int i = 0; i < MAX_NUMBER_FILTERS; i++){
        filters[i] = (char *)emalloc(MAX_PHRASE_LENGTH * sizeof(char));
    }

    char *line = (char *)emalloc(MAX_LINE_LENGTH * sizeof(char));

    char *delimiter = (char *)malloc(3 * sizeof(char));

    int phase = 0;
    

    /* Read the input lines and process them */
    while ( fgets(line, sizeof(char) * MAX_LINE_LENGTH, stdin) ) {
        if (line[0] == '#') {
            continue;
        }
        switch (phase) {
        case 0:
            strncpy(delimiter, ",\n", 3);
            num_phrases = tokenize_line(line, phrases, delimiter);
            num_tests = process_tests(phrases, num_phrases, tests);
            phase++;
            break;
        case 1:
            strncpy(delimiter, ";\n", 3);
            num_phrases = tokenize_line(line, phrases, delimiter);
            num_questions = process_questions(phrases, num_phrases, questions);
            phase++;
            break;
        case 2:
            num_phrases = tokenize_line(line, phrases, delimiter);
            process_question_types(phrases, num_phrases, 
                question_types);
            phase++;
            break;
        case 3:
            strncpy(delimiter, ",\n", 3);
            num_phrases = tokenize_line(line, phrases, delimiter);
            num_likert_levels = process_likert_level_descriptions(phrases, 
                num_phrases, likert_level_descriptions);
            phase++;
            break;
        case 4:
            strncpy(delimiter, "\n", 3);
            num_phrases = tokenize_line(line, phrases, delimiter);
            num_responses = process_num_responses(phrases);
            phase++;
            break;
        case 5:
            strncpy(delimiter, ",\n", 3);
            num_phrases = tokenize_line(line, phrases, delimiter);
            process_response(phrases, num_phrases, question_types, 
                responses, num_respondents);
            num_respondents++;
            if(num_respondents == num_responses){
                phase++;
            }
            break;
        case 6:
            num_phrases = tokenize_line(line, phrases, delimiter);
            process_filters(phrases, num_phrases, filters);
            filter_responses(filters, responses, num_responses);
            break;

        }
    }

    /* survey data processing */

    
    compute_frequencies(frequencies, num_questions, responses, num_respondents);

    int valid_responses = compute_scores(scores, question_types, responses, num_respondents);

    compute_average_scores(average_scores, scores, valid_responses);
    



    /* print results */
    
    print_output(tests, num_tests, questions, num_questions, 
        likert_level_descriptions, num_likert_levels, 
        responses, num_respondents, 
        frequencies, scores, average_scores, num_responses, valid_responses);

/* free dynamically allocated memory */
    for (int i = 0; i < MAX_NUMBER_PHRASES; i++) {
        if (phrases[i] != NULL) {
            free(phrases[i]);
        }
    }
    free(phrases);
    free(tests);

    for (int i = 0; i < NUMBER_QUESTIONS; i++) {
        if (questions[i] != NULL) {
            free(questions[i]);
        }
    }
    free(questions);
    free(question_types);

    for (int i = 0; i < NUMBER_LIKERT_LEVELS; i++) {
        if (likert_level_descriptions[i] != NULL) {
            free(likert_level_descriptions[i]);
        }
    }
    free(likert_level_descriptions);

    for (int i = 0; i < MAX_NUMBER_RESPONSES; i++) {
        if (responses[i].respondent != NULL) {
            free(responses[i].respondent->major);
            free(responses[i].respondent->birthday);
            free(responses[i].respondent);
            free(responses[i].answers);
        }
        
    }
    free(responses);

    for (int i = 0; i < MAX_NUMBER_RESPONSES; i++) {
        if (scores[i] != NULL) {
            free(scores[i]);
        }
    }
    free(scores);
    free(average_scores);

    for (int i = 0; i < NUMBER_QUESTIONS; i++) {
        if (frequencies[i] != NULL) {
            free(frequencies[i]);
        }
    }
    free(frequencies);

    for (int i = 0; i < MAX_NUMBER_FILTERS; i++) {
        if (filters[i] != NULL) {
            free(filters[i]);
        }
    }
    free(filters);
    free(line);
    free(delimiter);

    exit(0);
}


