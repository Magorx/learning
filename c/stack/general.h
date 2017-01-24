#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#define ERR_RETURN(err_code)                                       \
    do {                                                           \
        printf("ERROR [%s]: file [%s], function [%s], line [%d]\n",\
            #err_code, __FILE__, __FUNCTION__, __LINE__);          \
        return err_code;                                           \
    } while (0);

enum GENERAL_ERRORS {
    ERR_ARG1 = -5,
    ERR_ARG2,
    ERR_ARG3,
};

extern const int POISON_int;
extern const int TRUE;
extern const int FALSE;

int randint(int num);

#endif // GENERAL_H_INCLUDED
