#ifndef HELPERS_H
#define HELPERS_H

#include <set>

//栗思祺
bool isInteger(string str, bool withFeedback=true);
//栗思祺
int requestInteger(string& input);
//灏谛伦
bool verify(int choice, int lowestOption, int highestOption);
//灏谛伦
bool verifyChar(char input, char a, char b, bool ignoreCaps=true);
//灏谛伦
bool isThisCorrect(string message="Is this correct? (Y/N): ");
//栗思祺
string removeWhiteSpaces(string input);
//栗思祺
string formatMinutes(int minutes);
//栗思祺
bool file_is_empty(ifstream& pFile);
//栗思祺：
//我知道我们不应该在.h文件里声明函数，但因为函数是模板，我没办法，请查看：https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
template<typename BaseT, typename T1, typename T2>
extern BaseT* mergeArrays(const T1* arr1, size_t size1, const T2* arr2, size_t size2) {
    BaseT* result = new BaseT[size1 + size2];

    std::copy(arr1, arr1 + size1, result);
    std::copy(arr2, arr2 + size2, result + size1);

    return result;
};
//栗思祺
template<typename T>
extern bool setContains(set<T> set1, set<T> set2) {
    set<T> commonElements;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          inserter(commonElements, commonElements.begin()));
    return !commonElements.empty();
}
#endif
