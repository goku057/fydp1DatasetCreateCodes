#include<bits/stdc++.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include<iostream>  
#include <unistd.h>
// #include <stdlib.h>

using namespace std;

//declaring prototypes
vector <string> getDuoComb(string proteinList);
int getProteinNumber(string proteinList, char c);

//dnt change the proteinList in this code the list is string proteinList = "ARNDCEQGHILKMFPSTWYV";
// char protien[] = {'A', 'R', 'N', 'D', 'C', 'E', 'Q', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};

// void print(char letter, string feature1, string feature2,string feature3, int feature4, string feature5, char output){
//     cout << letter << "," << feature1 << "," << feature2 << "," << feature3 << "," << feature4 << "," << feature5 << "," << output << endl;
// }

void creatingHeaderForCSVFile(string fileName, string proteinList){
    int featureSize = 824;
    int proteinFeatureStartColumn = 4;
    int proteinFeatureEndColumn = 23;
    int proteinConsecutiveStartColumn = 24;
    int proteinConsecutiveEndColumn = 423;
    int protein1SpacedStartColumn = 424;
    int protein1SpacedEndColumn = 823;
    
    vector <string> duoComb = getDuoComb(proteinList);
    ofstream fw;
    fw.open(fileName);
    // fw << "letter,feature1,feature2,feature3,feature4,feature5,feature6,output\n";
    for (int i = 0; i < featureSize; i++)
    {
        if(i >= proteinFeatureStartColumn && i <= proteinFeatureEndColumn){
            fw << "f" << i << "(" << proteinList[i - proteinFeatureStartColumn]<<"),";
        }
        else if(i >= proteinConsecutiveStartColumn && i <= proteinConsecutiveEndColumn){
            fw << "f" << i << "(" << duoComb[i - proteinConsecutiveStartColumn]<<"),";
        }
        else if(i >= protein1SpacedStartColumn && i <= protein1SpacedEndColumn){
            fw << "f" << i << "(" << duoComb[i - protein1SpacedStartColumn]<<"),";
        }
        else{
            fw << "f" << i << ",";
        }
    }

    // int extraStart = 424;
    // int extraEnd = 528;
    // for(int i = extraStart; i <= extraEnd; i++){
    //     fw << "f" << i << ",";
    // }
    fw << "output" << endl;
    
    fw.close();
}

void printInFile(char letter, string left, string right,string feature1, string feature2, char feature3, vector<int> V, map<string, int> duoFrequency, char output, string fileName){
    ofstream fw;
    fw.open(fileName, ios_base::app);
    fw << letter << "," << feature1 << "," << feature2 << "," << feature3 << ",";
    for(int i = 0; i < V.size(); i++){
        fw << V[i] << ",";
    }
    map<string, int>::iterator itr;
    for(itr = duoFrequency.begin(); itr != duoFrequency.end(); itr++){
        fw << itr->second << ",";
    }

    
    fw << output <<endl;
    fw.close();
    

}

void printInFileFloat(int letter, string left, string right,string feature1, string feature2, int feature3, vector<int> V, map<string, int> duoFrequency, map <string, int> kSpacedFrequency1, char output, string fileName){
    ofstream fw;
    fw.open(fileName, ios_base::app);
    fw << letter << "," << feature1 << "," << feature2 << "," << feature3 << ",";
    for(int i = 0; i < V.size(); i++){
        fw << V[i] << ",";
    }
    map<string, int>::iterator itr;
    for(itr = duoFrequency.begin(); itr != duoFrequency.end(); itr++){
        fw << itr->second << ",";
    }

    map<string, int>::iterator itr2;
    for(itr2 = kSpacedFrequency1.begin(); itr2 != kSpacedFrequency1.end(); itr2++){
        fw << itr2->second << ",";

        // cout << itr2->second << ",";
    }
    
    // int extraStart = 424;
    // int extraEnd = 528;
    // for(int i = extraStart; i <= extraEnd; i++){
    //     fw << 0 << ",";
    // }

    fw << output <<endl;
    fw.close();
    

}

void removeExtraSpaces(string &s)
{
    while(s[0]  == ' ')
    {
        s.erase(0, 1);
    }
    while(s[s.size()-1]  == ' ')
    {
        s.erase(s.size()-1, s.size());
    }
}

void fixSequence(string &s, string &output, string pl){
    
    for(int i = 0; i < s.size(); i++){
        int count = 0;
        for(int j = 0; j < pl.size(); j++){
            if(s[i] != pl[j]){
                count++;
            }
        }
        if(count > pl.size() - 1){
            s.erase(i, 1);
            output.erase(i, 1);
            i--;
            cout << "The reformed string is " << s << endl;
        }
    }

    

}

char getMaximumRepeatedChar(string s){
    int A[26] = {0};
    char c = 'A';
    for(int i = 0; i < 26; i++){
        c = 'A' + i;
        for (int j = 0; j < s.size(); j++){
            if(s[j] == c){
                A[i]++;
            }
        }
        
    }

    int maxCount = 0, maxI = 0;
    for(int i = 0; i < 26; i++){
        if(maxCount < A[i]){
            maxCount = A[i];
            maxI = i;
        }
    }
    // cout<< "The majority letter = " << (char)('A' + maxI) << " its frequency = " << maxCount << endl;
    return 'A' + maxI;
}

bool checkVorC(char c){
    if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y' ){
        return true;
    }
    else{
        return false;
    }
}

//this function returns 1 if majority letters of this string is vowel otherwise return 0
int checkMajorVorC(string s, char dummy){
    int countV = 0, countC = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' || s[i] == 'Y' ){
            countV++;
        }
        else if (s[i] != dummy){
            countC++;
        }
        
    }

    // cout << "Vowel = " << countV << " Consonant = " << countC << endl;
    if(countV > countC){
        return 1;
    }
    else{
        return 0;
    }
}

vector<int> checkRedundency(string left, string right, string proteinList){
    vector<int> V;
    string s = left + right;
    
    for (int i = 0; i < proteinList.size(); i++)
    {   
        int countR = 0;
        for(int j = 0; j < s.size(); j ++){
            if(s[j] == proteinList[i] ){
                countR++;
            }
        }
        V.push_back(countR);
    }
    
    return V;
}

bool checkConsecutiveCharacter(string s, char c){
    int countC = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == c){
            countC++;
        }
        else if(countC > 1){
            return true;
        }
        else{
            countC = 0;
        }
    }

    return false;
}

vector <string> getConsecutiveResults(string left, string right, string proteinList){
    vector<string> V;
    string pos = "positive";
    string neg = "negative";
    for(int i = 0; i < proteinList.size(); i++){
         if(checkConsecutiveCharacter(left, proteinList[i]) == true || checkConsecutiveCharacter(right, proteinList[i]) == true ){
             V.push_back(pos);
         }
         else{
             V.push_back(neg);
         }
    }

    return V;
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

map <string, int> getDuoCombinationFrequency(string left, string right, vector<string> duoComb){
    map <string, int > M; //here the values of duoComb will be stored
    for( int i = 0; i < duoComb.size(); i++){
        M.insert(pair<string, int>(duoComb[i], 0));

        for(int j = 0; j < left.size() - 1; j++){
            if(duoComb[i][0] == left[j] && duoComb[i][1] == left[j + 1]){
                M[duoComb[i]]++;
            }
        }
        for(int j = 0; j < right.size() - 1; j++){
            if(duoComb[i][0] == right[j] && duoComb[i][1] == right[j + 1]){
                M[duoComb[i]]++;
            }
        }
    }

    return M;
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

void datasetCreateCoreAlgo(string seq, string output, int maxSide, string fileName, string proteinList){
    for (int i = 0; i < seq.size(); i ++){
        int  tempi, tempLeftSide;
        string left = "", right = "", dummyLeft = "", dummyRight = "";
        if(i - maxSide < 0){
            for(int j = 0; j <  maxSide - i; j++){
                dummyLeft += "a";
            }
            tempi = 0;
            tempLeftSide = maxSide - dummyLeft.size();
            left = dummyLeft + seq.substr(tempi, tempLeftSide);
        }
        else{
            tempi = i - maxSide;
            tempLeftSide = maxSide;
            left = seq.substr(tempi, tempLeftSide);
        }
        
        

        if( i + maxSide >= seq.size()){
            for(int j = 0; j < (maxSide + i + 1) - seq.size(); j++){
                dummyRight += "a";
            }

            right = seq.substr(i + 1, maxSide) + dummyRight;

        }
        else{
            right = seq.substr(i + 1, maxSide);
        }


        string ws = left + seq[i] + right;
        char letter = seq[i];
        // string feature1 = left;
        // string feature2 = right;
        string feature1;
        if(checkVorC(seq[i]) == 1){
            feature1 = "vowel";
        }
        else{
            feature1 = "consonant";
        }

        vector <int> V = checkRedundency(left, right, proteinList);

        string feature2;
        if(checkMajorVorC(left+right, 'a') == 1){
            feature2 = "vowel";
        }
        else{
            feature2 = "consonant";
        }

        string wlr = left + right;
        char feature3 = getMaximumRepeatedChar(wlr);

        vector <string> proteinDuoCombination = getDuoComb(proteinList);
        // vector<string> consecutive = getConsecutiveResults(left, right, proteinList);
        char o = output[i];
        map <string, int> duoFrequencey = getDuoCombinationFrequency(left, right, proteinDuoCombination);
        printInFile(letter,  left,  right, feature1,  feature2,  feature3, V, duoFrequencey, o, fileName);

        // print( letter,  feature1,  feature2, feature3,  feature4,  feature5,  o);
        // printInFile(letter,  feature1,  feature2, feature3,  feature4,  feature5,  o, "dataset.txt");
        // cout << "\nFor i = " << i << "\nLetter = " << seq[i]  <<  " Left = " << left << " Right = " << right << "\nThe whole string = " << ws << "\nThe redundency = " << checkRedundency(left, right, seq[i]) << endl <<"The majority" << checkMajorVorC(ws, 'a') << endl;
        
    }
}

void dataset(string seq, string output, int maxSide, string fileName, string proteinList){
    // cout<<"letter,feature1,feature2,feature3,feature4,feature5,output\n";
    creatingHeaderForCSVFile(fileName, proteinList);
    // fw.open("dataset.txt");
    // fw << "letter,feature1,feature2,feature3,feature4,feature5,output\n";
    // fw.close();
    datasetCreateCoreAlgo( seq,  output,  maxSide,  fileName, proteinList);
    
    
}

void createIndividualDataset(string inputFile, string destFolder){
    string proteinList = "ARNDCEQGHILKMFPSTWYV";
    string sequence = "IVEKSKICSSRYEPTV", output = "0000000000001111";
    string filePath = "./" + destFolder + "/", fileName = "sequence";
    int neighbourSize = 15;
    // dataset(sequence, output, neighbourSize, fileName);
    // cout << "Enter sequence: ";
    // cin >> sequence;
    // cout<< "Enter output: ";
    // cin >> output;
    // cout<< "Enter width size: ";
    // cin >> output;
    ifstream fr(inputFile);
    string line1,line2,line3;
    int i = 0;
    while(getline(fr, line1)){
        i++;
        
        getline(fr, sequence);
        
        getline(fr, output);
        fixSequence(sequence, output, proteinList); 
        string finalFileName =  filePath + fileName + to_string(i) + ".csv";
        removeExtraSpaces(sequence);
        removeExtraSpaces(output);
        if(sequence.size() != output.size()){
            cout << "sequence size output size not same!!!" << endl;
        }
        else{
            dataset(sequence, output, neighbourSize, finalFileName, proteinList);
            cout<<"\n\nDataset creation of sequence " << i << " DONE!!!" << endl;
        }
        
        // if(i == 2){
        //     break;
        // }
    }
}



void combinedDatasets(string seq, string output, int maxSide, string fileName,string proteinList){
    // cout<<"letter,feature1,feature2,feature3,feature4,feature5,output\n";
    // fw.open("dataset.txt");
    // fw << "letter,feature1,feature2,feature3,feature4,feature5,output\n";
    // fw.close();
    
    datasetCreateCoreAlgo( seq,  output,  maxSide,  fileName, proteinList);
    
    
}



void createCombinedDataset(string inputFile, string destFolder){
    string proteinList = "ARNDCEQGHILKMFPSTWYV";
    string sequence = "", output = "";
    string filePath = "./" + destFolder + "/", fileName = "combinedsequence";
    int neighbourSize = 15;
    // dataset(sequence, output, neighbourSize, fileName);
    // cout << "Enter sequence: ";
    // cin >> sequence;
    // cout<< "Enter output: ";
    // cin >> output;
    // cout<< "Enter width size: ";
    // cin >> output;
    ifstream fr(inputFile);
    string line1,line2,line3;
    int i = 0;

    string finalFileName =  filePath + fileName + ".csv";
    ofstream fw;
    // fw.open(finalFileName);
    // fw << "letter,feature1,feature2,feature3,feature4,feature5,feature6,output\n";
    // fw.close();
    creatingHeaderForCSVFile(finalFileName, proteinList);
    while(getline(fr, line1)){
        i++;
        getline(fr, sequence);
        getline(fr, output);
        fixSequence(sequence, output, proteinList); 
        removeExtraSpaces(sequence);
        removeExtraSpaces(output);
        if(sequence.size() != output.size()){
            cout << "sequence size output size not same!!!" << endl;
        }
        else{
            
            combinedDatasets(sequence, output, neighbourSize, finalFileName, proteinList);
            cout<<"\n\nDataset create and merge of sequence " << i << " DONE!!!" << endl;
        }
        
        // if(i == 2){
        //     break;
        // }
    }
    cout << "FULL DATASET CREATION DONE!!!!!!!" << endl;
}

string convertArraytoString(char A[]){
    string s = "";
    size_t  n = 0;
    while(A[n] != '\0'){
        n++;
    }
    cout << "The size is " << n << endl;
    for(int i = 0; i < n; i++){
        s += A[i];
    }

    return s;
}

int getProteinNumber(string proteinList, char c){
    for(int i = 0; i < proteinList.size(); i++){
        if( c == proteinList[i]){
            return i;
        }
    }
    return -1;
}

void datasetFloatCreateCoreAlgo(string seq, string output, int maxSide, string fileName, string proteinList){
    for (int i = 0; i < seq.size(); i ++){
        // if(output[i] == '0'){
        //     continue;
        // }
        int  tempi, tempLeftSide;
        string left = "", right = "", dummyLeft = "", dummyRight = "";
        if(i - maxSide < 0){
            for(int j = 0; j <  maxSide - i; j++){
                dummyLeft += "a";
            }
            tempi = 0;
            tempLeftSide = maxSide - dummyLeft.size();
            left = dummyLeft + seq.substr(tempi, tempLeftSide);
        }
        else{
            tempi = i - maxSide;
            tempLeftSide = maxSide;
            left = seq.substr(tempi, tempLeftSide);
        }
        
        

        if( i + maxSide >= seq.size()){
            for(int j = 0; j < (maxSide + i + 1) - seq.size(); j++){
                dummyRight += "a";
            }

            right = seq.substr(i + 1, maxSide) + dummyRight;

        }
        else{
            right = seq.substr(i + 1, maxSide);
        }


        string ws = left + seq[i] + right;
        int letter = getProteinNumber( proteinList, seq[i]);
        // string feature1 = left;
        // string feature2 = right;
        string feature1;
        if(checkVorC(seq[i]) == 1){
            feature1 = "1"; //vowel
        }
        else{
            feature1 = "0"; //consonant
        }

        vector <int> V = checkRedundency(left, right, proteinList);

        string feature2;
        if(checkMajorVorC(left+right, 'a') == 1){
            feature2 = "1"; // vowel
        }
        else{
            feature2 = "0"; //consonant
        }

        string wlr = left + right;
        char c = getMaximumRepeatedChar(wlr);
        int feature3 = getProteinNumber(proteinList, c);
        vector <string> proteinDuoCombination = getDuoComb(proteinList);
        // vector<string> consecutive = getConsecutiveResults(left, right, proteinList);
        char o = output[i];
        map <string, int> duoFrequencey = getDuoCombinationFrequency(left, right, proteinDuoCombination);
        int k = 1;
        map <string, int> kSpacedFrequency1 = getKSpacedCombFrequency(left, right, proteinDuoCombination, k);
        
        printInFileFloat(letter,  left,  right, feature1,  feature2,  feature3, V, duoFrequencey, kSpacedFrequency1, o, fileName);

        // print( letter,  feature1,  feature2, feature3,  feature4,  feature5,  o);
        // printInFile(letter,  feature1,  feature2, feature3,  feature4,  feature5,  o, "dataset.txt");
        // cout << "\nFor i = " << i << "\nLetter = " << seq[i]  <<  " Left = " << left << " Right = " << right << "\nThe whole string = " << ws << "\nThe redundency = " << checkRedundency(left, right, seq[i]) << endl <<"The majority" << checkMajorVorC(ws, 'a') << endl;
        
    }
}

void createCombinedFloatDataset(string inputFile, string destFolder){
    string proteinList = "ARNDCEQGHILKMFPSTWYV";
    string sequence = "", output = "";
    string filePath = "./" + destFolder + "/", fileName = "combinedsequence";
    int neighbourSize = 15;
    // dataset(sequence, output, neighbourSize, fileName);
    // cout << "Enter sequence: ";
    // cin >> sequence;
    // cout<< "Enter output: ";
    // cin >> output;
    // cout<< "Enter width size: ";
    // cin >> output;
    ifstream fr(inputFile);
    string line1,line2,line3;
    int i = 0;

    string finalFileName =  filePath + fileName + ".csv";
    ofstream fw;
    // fw.open(finalFileName);
    // fw << "letter,feature1,feature2,feature3,feature4,feature5,feature6,output\n";
    // fw.close();
    creatingHeaderForCSVFile(finalFileName, proteinList);
    while(getline(fr, line1)){
        i++;
        getline(fr, sequence);
        getline(fr, output);
        fixSequence(sequence, output, proteinList); 
        removeExtraSpaces(sequence);
        removeExtraSpaces(output);
        if(sequence.size() != output.size()){
            cout << "sequence size output size not same!!!" << endl;
        }
        else{
            
            // combinedDatasets(sequence, output, neighbourSize, finalFileName, proteinList);
            datasetFloatCreateCoreAlgo( sequence,  output,  neighbourSize,  finalFileName, proteinList);
            cout<<"\n\nDataset create and merge of sequence " << i << " DONE!!!" << endl;
        }
        
        // if(i == 2){
        //     break;
        // }
    }
    cout << "FULL DATASET CREATION DONE!!!!!!!" << endl;
}

int main(){

    // Creating a directory
    // mkdir("datasets");
    // if (mkdir("datasets") == -1)
    //     cout << "Error :  " << strerror(errno) << endl;
  
    // else
    //     cout << "Directory created";
    
    string inputFile = "data.txt";
    char destinationFolder[] = "data";
    string destFolder = convertArraytoString(destinationFolder);
    cout << "The destination folder is " << destFolder;
    mkdir(destinationFolder);
    // createIndividualDataset(inputFile, destFolder);
    // createCombinedDataset(inputFile, destFolder);
    createCombinedFloatDataset(inputFile, destFolder);
    // string protein = "ARNDCEQGHILKMFPSTWYV";
    // int s;
    // cin >> s;
    // cout<< "gg"; 
} 
