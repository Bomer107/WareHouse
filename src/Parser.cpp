#include "../include/executeLine.h"

void parseString(string &line, vector<string> &command)
{
    int s_index {};
    int e_index {};
    string word{};
    bool comment = (line[0] == '#');
    while(!comment && e_index != -1)
    {
        e_index = line.find(' ', s_index);
        word = line.substr(s_index, e_index - s_index);
        s_index = e_index + 1;
        if( word[0] == '#')
            comment = true;
        else
            if( word != "")
                command.push_back(word);
    }
}