#include <iostream>
#include <string>
#include <vector>

using namespace std;



bool isPal(string s, int l, int h) {
    while (l <= h) {
        if (s[l++] != s[h--])
            return false;
    }
    return true;
}

void PalUtil(int ind, string s, vector<string>& curParition, vector<vector<string>>& result) {
    if (ind == s.size()) {
        result.push_back(curParition);
        return;
    }

    for (int i = ind; i < s.size(); i++) {
        if (isPal(s, ind, i)) {
            curParition.push_back(s.substr(ind, i - ind + 1));
            PalUtil(i + 1, s, curParition, result);
            curParition.pop_back();
        }
    }
}

void printMinNumberOfCuts(vector<vector<string>> result) {
    vector<string> minPartition;
    int minSize = INT_MAX;
    for (auto i : result) {
        if (i.size() < minSize) {
            minPartition.clear();
            for (auto j : i) {
                minPartition.push_back(j);
            }
        }
    }

    int ctr = 31;
    for (auto i : minPartition) {
        //cout << i << " ";
        if (ctr == 37)
            ctr = 91;
        cout <<"\033["<<ctr<<"m"<<i<<"\033[0m|";
        ctr++;
    }

    cout << "\n\n Minimum Number Of Cuts\033[91m(recursive) :\033[0m" << minPartition.size() - 1 << endl;
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> curPartition;
    PalUtil(0, s, curPartition, result);
    
    //for (auto i : result) {
    //    for (auto j : i) {
    //        cout << j << " ";
    //    }
    //    cout << endl;
    //}
    
    printMinNumberOfCuts(result);
    return result;

}

//-------------------------
int palindromePartition(string str) {
    int length = str.length();
    int* cut = new int[length];
    bool** isPalindrome = new bool* [length];

    for (int i = 0; i < length; i++) {
        isPalindrome[i] = new bool[length];    //Dynamically create 2d boolean array with intial values of "False"
        for (int j = 0; j < length; j++) {
            isPalindrome[i][j] = false;
        }
    }

    /*for (int i = 0; i < length; i++)
    {
        isPalindrome[i][i] = true; //Set the diagonal of the matrix "True" single letter case palindrome [done on line 93 now]
    }*/

    for (int i = 0; i < length; i++)
    {
        int minCut = i;
        for (int j = 0; j <= i; j++)
        {
            if (str[i] == str[j] && (i - j < 2 || isPalindrome[j + 1][i - 1]))
            {
                //cout << "i=" << i << " j=" << j<<endl; debug 
                isPalindrome[j][i] = true;
                minCut = min(minCut, j == 0 ? 0 : (cut[j - 1] + 1));
            }
        }
        cut[i] = minCut;
    }
    return cut[length - 1];
}
void displayOutput() {
    
}

int main()
{
    string s = "ababxyutab";
    cout << " String input :"<<s<<endl;
    cout << "\n String Partitioning :";
    partition(s);
    cout << endl;
    cout << " Minimum number of cuts\033[93m(dynamic) :\033[0m" << palindromePartition(s)<<endl;
}

