#include <bits/stdc++.h>

using namespace std;

void printArray(int A[], int length)
{
    for (int i = 0; i < 5; i++)
    {
        cout << *A + i << endl;
    }
    // int n = sizeof(A) / sizeof(A[0]);
    // cout << "In print function the size is " << n << endl;
}

void printVector(vector<int> A)
{
    // for (int i = 0; i < 5; i++){
    //     cout << *A + i << endl;
    // }
    // int n = sizeof(A) / sizeof(A[0]);
    // cout << "In print function the size is " << n << endl;
    A[0] = 69;
}




vector <string> getDuoComb(string proteinList){
    vector<string> proteingDuoComb;
    for (int i = 0; i < proteinList.size(); i++)
    {
        for (int j = 0; j < proteinList.size(); j++)
        {
            string temp = "";
            temp.push_back(proteinList[i]);
            temp.push_back(proteinList[j]);
            // cout << "The temp is " << temp << endl;
            proteingDuoComb.push_back(temp);
        }
    }

    return proteingDuoComb;
}

map <string, int> getKSpacedCombFrequency(string left, string right, vector<string> duoComb, int k){
    map <string, int > M; //here the values of duoComb will be stored
    for( int i = 0; i < duoComb.size(); i++){
        M.insert(pair<string, int>(duoComb[i], 0));

        for(int j = 0; j < left.size() - 1 - k - 1; j++){
            if(duoComb[i][0] == left[j] && duoComb[i][1] == left[j + 1 + k]){
                M[duoComb[i]]++;
            }
        }
        for(int j = 0; j < right.size() - 1 - k - 1; j++){
            if(duoComb[i][0] == right[j] && duoComb[i][1] == right[j + 1 + k]){
                M[duoComb[i]]++;
            }
        }
    }

    return M;
}


/////
int main()
{

    map<string, int> M;
    string proteinList = "ARC";
    M = getKSpacedCombFrequency("AAAR", "AAAR", getDuoComb(proteinList), 1);

    map< string, int>::iterator itr;
    for(itr = M.begin(); itr != M.end(); itr++){
        cout << "The key = " << itr->first << " value = " << itr->second << endl;
    }
}