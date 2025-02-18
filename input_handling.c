#include "input_handling.h"
#include "dyn_survey.h"

/* tokenize a line and store it in a string array of phrases */
int tokenize_line(char *line, char **phrases, char *delimiter) {

    int num_phrases = 0;
    char *token;
    
    /* get the first token from line */
    token = strtok(line, delimiter);
    
    /* for every token in line, store it */
    while (token) {
        strncpy(phrases[num_phrases], token, MAX_PHRASE_LENGTH);
        num_phrases++;

        /* get the next token from line or reach end of line */
        token = strtok(NULL, delimiter);
    } 
    return num_phrases;          
}


/* store test configuration to only run specified tests */
int process_tests(char **phrases, int num_phrases, short *tests) {
    /* for every phrase in phrases, convert it to a bit and store it  */
    for (int i = 0; i < num_phrases; i++) {
        if (phrases[i][0] == '1') {
            tests[i] = 1;
        }
        else {
            tests[i] = 0;
        }
    }
    return num_phrases;          
}

/* store survey questions */
int process_questions(char **phrases, int num_phrases, char **questions) {

    /* for every phrase in phrases, store it as a question  */
    for (int i = 0; i < num_phrases; i++) {
        strncpy(questions[i], phrases[i], MAX_QUESTION_LENGTH);
    }
    return num_phrases;          
}


/* store survey question types (direct or reverse) */
void process_question_types(char **phrases, int num_phrases, short *question_types) {

    /* for every phrase in phrases, convert it to a bit and store it  */
    for (int i = 0; i < num_phrases; i++) {
        if (strcmp(phrases[i], "Direct") == 0) {
            question_types[i] = 1;
        }
        else {
            question_types[i] = 0;
        }
    }   
    return;     
}


/* store possible answers - Likert levels */
int process_likert_level_descriptions(char **phrases, int num_phrases, char **likert_level_descriptions) {

    /* for every phrase in phrases, store it as a possible Likert answer  */
    for (int i = 0; i < num_phrases; i++) {
        strncpy(likert_level_descriptions[i], phrases[i], MAX_WORD_LENGTH);
    }
    return num_phrases;          
}

int process_num_responses(char **phrases){
    return atoi(phrases[0]);
}
/* stores next survey response */
void process_response(char **phrases, int num_phrases, short *question_types, Response *responses, int num_respondents) {

    Response *cur_response = &responses[num_respondents];
    for (int i = 0; i < num_phrases; i++) {
        if (i == 0){
            strncpy(cur_response->respondent->major, phrases[i], MAX_PHRASE_LENGTH);
        }
        else if(i == 1){
            if(strcmp(phrases[i], "yes") == 0){
                cur_response->respondent->canada_born = 1;
            }
        }
        else if(i == 2){
            strncpy(cur_response->respondent->birthday, phrases[i], MAX_PHRASE_LENGTH);
        }
        else{
            short scale = convert_response_to_scale(phrases[i], question_types[i]);
            cur_response->answers[i-3] = scale;
        }
    }
    return;     
}

/* convert Likert item to numerical scale */
short convert_response_to_scale(char *token, short direct_scale) {
    short scale;
    if (strcmp(token, "fully disagree") == 0) {
        scale = 1;
    }
    else if (strcmp(token, "disagree") == 0) {
        scale = 2;
    }
    else if (strcmp(token, "partially disagree") == 0) {
        scale = 3;
    }
    else if (strcmp(token, "partially agree") == 0) {
        scale = 4;
    }
    else if (strcmp(token, "agree") == 0) {
        scale = 5;
    }
    else {
        scale = 6;
    }

    return scale;
}

/* stores filters */
void process_filters(char **phrases, int num_phrases, char **filters){
    for(int i = 0; i < num_phrases; i++){
        strncpy(filters[i], phrases[i], MAX_PHRASE_LENGTH);
    }
    return;
}

/* filters the responses by setting to filter flag to false if appropriate */
void filter_responses(char **filters, Response *responses, int num_responses){
    for(int j = 0; j < num_responses; j++){
        if(strcmp(filters[0], "0") == 0){
            if(strcmp(filters[1], responses[j].respondent->major) != 0){
                responses[j].respondent->filter_flag = 0;
            }
        }
        else if(strcmp(filters[0], "1") == 0){
            if(strcmp(filters[1], "yes")==0 ){
                if(responses[j].respondent->canada_born != 1){
                    responses[j].respondent->filter_flag = 0;
                }
            }
            else{
                if(responses[j].respondent->canada_born != 0){
                    responses[j].respondent->filter_flag = 0;
                }
            }
        }
        else{
            int birthyear = 0;
            int birthmonth = 0;
            sscanf(responses[j].respondent->birthday, "%4d-%4d", &birthyear, &birthmonth);
            int age = 2024 - birthyear;
            if(birthmonth > 10){
                age--;
            }
            int lower_bound = atoi(filters[1]);
            int upper_bound = atoi(filters[2]);
            if(lower_bound > age || upper_bound < age){
                responses[j].respondent->filter_flag = 0;
            }
        } 
    }

    


}