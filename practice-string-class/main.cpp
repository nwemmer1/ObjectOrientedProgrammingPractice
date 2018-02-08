/*
    Goal: Implement a value-semantic string class.
    Your class should support the following syntaxes:

    Nathan Wemmer
    nww8@zips.uakron.edu

    String class

*/

#include <cstring>
#include <string>
int main
{
    // Default construct
    std::string s0;

    // Construct and assign from a literal value
    std::string s1 = "hello";
    s1 = "foo";

    // Copy construct and assign
    std::string s2 = s1;
    s2 = s1; // s2 == s1

    // Move construction and assignment (optional)
    std::string s3 = std::move(s2);
    s3 = std::move(s1);

    // Compare
    s1 == s1;

    // Order
    s1 < s1; // lexicographical comparison

    // Object independence
    s2 = "bar"; // Does not change the value of s1
}
//=================================================

class ValueSemanticString
{
private:
    int length;
    char* stringEx;
public:
    ValueSemanticString(const char* s)
    : len(std::strlen(s)), str(new char[len])
    {
        std::strncpy(str, s, len);
    }

    ~ValueSemanticString()
    {
    }

    ValueSemanticString(const ValueSemanticString& s)
    :str(s.str), len(s.len)
    {
    }

    bool operator==(const ValueSemanticString& s)
    {
        if(std:strcmp(str, s.str)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    ValueSemanticString operator=(const ValueSemanticString& s)
    {
        std::strncpt(str, s.str, s.len);
        return *this;
    }

    bool operator<(const ValueSemanticString& s)
    {
        if(std::strncmp(str, s.str) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(const ValueSemanticString& s)
    {
        if(std:strncmp(str, s.str)>0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
