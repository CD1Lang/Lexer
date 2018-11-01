#include "lexer_conf.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

    lab_retarget_print(stderr);
    lab_retarget_error(stderr);

    size_t file_count           = argc - 1;
    char** file_names           = NULL;
    size_t* file_name_sizes     = NULL;
    char** file_contents        = NULL;
    size_t* file_contents_sizes = NULL;

    if(argc > 1) {
        FILE* cur_file = NULL;
        file_names          = (char**)malloc(sizeof(char*)  * file_count);
        file_name_sizes     = (size_t*)malloc(sizeof(size_t) * file_count);
        file_contents       = (char**)malloc(sizeof(char*)  * file_count);
        file_contents_sizes = (size_t*)malloc(sizeof(size_t) * file_count);

        if(file_names==NULL) {
            lab_errorln("Failed to allocate file name buffer!");
            free(file_names);
            free(file_name_sizes);
            free(file_contents);
            free(file_contents_sizes);
            return 1;
        } else if(file_name_sizes==NULL) {
            lab_errorln("Failed to allocate file name size buffer!");
            free(file_names);
            free(file_name_sizes);
            free(file_contents);
            free(file_contents_sizes);
            return 1;
        } else if(file_contents==NULL) {
            lab_errorln("Failed to allocate file contents buffer!");
            free(file_names);
            free(file_name_sizes);
            free(file_contents);
            free(file_contents_sizes);
            return 1;
        } else if(file_contents_sizes==NULL) {
            lab_errorln("Failed to allocate file contents size buffer!");
            free(file_names);
            free(file_name_sizes);
            free(file_contents);
            free(file_contents_sizes);
            return 1;
        }

        for(int i = 1; i < argc; i++) {

            file_name_sizes[i-1] = strlen(argv[i])+1;
            file_names[i-1] = (char*)malloc(file_name_sizes[i-1]);
            if(file_names[i-1]==NULL) {
                lab_errorln("Failed to allocate file name for file: \"%s\"!", argv[i]);
                for(int j = 0; j < file_count; j++) {
                    free(file_names[j]);
                    free(file_contents[j]);
                }
                free(file_names);
                free(file_name_sizes);
                free(file_contents);
                free(file_contents_sizes);
                return 1;
            }

            file_names[i-1][file_name_sizes[i-1]-1] = '\0';
            memcpy(file_names[i-1], argv[i], file_name_sizes[i-1]-1);

            cur_file = fopen(argv[i], "r");

            if(cur_file==NULL) {
                lab_errorln("Failed to openfile: \"%s\"!", argv[i]);
                for(int j = 0; j < file_count; j++) {
                    free(file_names[j]);
                    free(file_contents[j]);
                }
                free(file_names);
                free(file_name_sizes);
                free(file_contents);
                free(file_contents_sizes);
                return 1;
            }

            fseek(cur_file, 0, SEEK_END);
            file_contents_sizes[i-1] = ftell(cur_file)+1;
            fseek(cur_file, 0, SEEK_SET);
            file_contents[i-1] = (char*)malloc(file_contents_sizes[i-1]);

            if(file_contents[i-1]==NULL) {
                lab_errorln("Failed to allocate file buffer for file: \"%s\"!", argv[i]);
                for(int j = 0; j < file_count; j++) {
                    free(file_names[j]);
                    free(file_contents[j]);
                }
                free(file_names);
                free(file_name_sizes);
                free(file_contents);
                free(file_contents_sizes);
                return 1;
            }

            file_contents[i-1][file_contents_sizes[i-1]-1] = '\0';

            fread(file_contents[i-1], 1, file_contents_sizes[i-1], cur_file);
            fclose(cur_file);
        }
    }
    else {
        lab_errorln("No input files!");
        return 1;
    }


    lab_lexer_token_container_t tokens;


    for(size_t i = 0; i < file_count; i++) {
        lab_lexer_token_container_init(&tokens);

        cdo_lex_string(file_contents[i], file_contents_sizes[i] - 1, &tokens);

        for(size_t j = 0; j < tokens.count; j++) {
            cdo_pipe_token(&tokens.tokens[j]);
        }

        lab_lexer_token_container_free(&tokens);
    }



    for(int j = 0; j < file_count; j++) {
        free(file_names[j]);
        free(file_contents[j]);
    }
    free(file_names);
    free(file_name_sizes);
    free(file_contents);
    free(file_contents_sizes);


    return 0;

}