/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "lottery.h"

static char* filename;
static char separator;
static int* drawing;
static bool draw=false;

bool init_lottery(char* csv_file, char csv_separator)
{
    FILE* file= fopen(csv_file, "r");
    if(file ==NULL)return false;
    filename = csv_file;
    separator = csv_separator;
    draw = false;
    fclose(file);
    return true;
}
bool get_tip(int tip_number, int* tip)
{
    FILE* file= fopen(filename, "r");
    char input[MAX_LINE_LEN] = {0};
    int count = 0;
    if(tip_number < 0 || file == 0)
    {
        fclose(file);
        return false;
    }
    char* outp = fgets(input, MAX_LINE_LEN, file);
    while(outp != NULL && count < tip_number)
    {
        outp = fgets(input, MAX_LINE_LEN, file);
        count++;
        if(outp != input)
        {
            fclose(file);
            return false;
        }
    }
    if(ftell(file) == EOF)
    {
        fclose(file);
        return false;
    }
    int pos = 0;
    while(input[pos] != separator && pos < UUID_LEN)
    {
        pos++;
    }

    int insertionpos = 0;
    int f = 0;
    while(insertionpos < 6)
    {
        pos++;
        if(input[pos]<= '9' && input[pos]>= '0')
        {
            f = f*10+ (input[pos] - '0');
        }
        else
        {
            tip[insertionpos] = f;
            f = 0;
            insertionpos++;
        }
    }
    fclose(file);
    return true;
}
bool set_drawing(int* array)
{
    draw = true;
    drawing = array;
    return false;
}
int get_tip_result(int tip_number)
{
    if(!draw )return -1;
    int tip[6];
    if(!get_tip(tip_number, tip))return -2;
    int count = 0;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if(tip[i] == drawing[j])count++;
        }
    }
    return count;
}
int get_right_tips_count(int right_digits_count){
    if(!draw || right_digits_count < 0 || right_digits_count > TIP_SIZE)return -1;
    int b = 0;
    int count = 0;
    int x = 0;
    while(x != -2 && x != -1)
    {
        x = get_tip_result(b);
        if(x == right_digits_count)count++;
        b++;
    }
    return count;
}
