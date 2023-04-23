#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int check_letters(string text);
int check_words(string text);
int check_sentence(string text);

int main(void)
{

    string text = get_string("Enter your text: ");

    float letters = check_letters(text);
    float words = check_words(text);
    float sentence = check_sentence(text);
    float avg_L = 0;
    float avg_S = 0;

    avg_L = letters / words * 100;
    avg_S = sentence / words * 100;

    int index = round(0.0588 * avg_L - 0.296 * avg_S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

}

int check_letters(string text)
{
    int i;
    int letter = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
        else
        {
            continue;
        }
    }

    return letter;

}


int check_words(string text)
{
    int i;
    int word = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            word++;
        }
        else
        {
            continue;
        }
    }

    return word + 1;

}


int check_sentence(string text)
{
    int i;
    int sentence = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
        else
        {
            continue;
        }
    }

    return sentence;

}