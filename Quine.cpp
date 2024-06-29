#include<bits/stdc++.h>
using namespace std;

vector<string> minTermsBits;
vector<string> minTermsStr;
vector<string> implicantsBits;
vector<string> implicants;
vector<bool> track;
vector<string> essentialImplicantsBits;
vector<string> dominatingRowsBits;
map<string,bool> minTermOccurred;

int numMinTerms;
bool table[50][50]={0};
int presentFinal[50] = {0};

string ConvertToBits(int minTerm){			
    int num = minTerm;
    int index = 0; 
    char bits[20];
    char rbits[20];
    for (int i=0 ; i<8 ; i++){
        bits[i] = num%2 + '0';
        num/=2;
    }
    bits[8] = '\0';
    for (int i=7 ; i>=0 ; i--){
        rbits[7-i] = bits[i]; 
    }
    rbits[8] = '\0';
    string str = rbits;				
    return str;
}

string ConvertToString(int num){			
    int res = num;
    int index = 0;
    char ch[4], rch[4];
    while (res){
        ch[index] = res%10 + '0';
        res/=10;
        index++;
    }
    ch[index] = '\0';
    for (int i=index-1 ; i>=0 ; i--){
        rch[index-1-i] = ch[i];
    }
    rch[index] = '\0';
    if (num == 0){
        rch[0] = '0';
        rch[1] = '\0';
    }
    string str = rch;
    return	str;
}

bool OneBitDifference(string s1, string s2){		
    int count = 0;
    for (int i=0 ; i<8 ; i++){
        if (s1[i]!=s2[i]){
            count++;
        }
    }
    return (count==1);
}

string EditString(string s1, string s2){		
    string res = s1;
    for (int i=0 ; i<8 ; i++){
        if (s1[i]!=s2[i]){
            res[i] = '-';
        }	
    }
    return res;
}

void CreateTable(int start){					
    bool repeat = false;
    int len = minTermsBits.size();
    for (int i=start ; i<len-1 ; i++){
        for (int j=i+1 ; j<len ; j++){
            if (OneBitDifference(minTermsBits[i], minTermsBits[j])){
                track[i] = true;
                track[j] = true;
                if (!minTermOccurred[EditString(minTermsBits[i], minTermsBits[j])]){
                    minTermsStr.push_back(minTermsStr[i] + "," + minTermsStr[j]);
                    minTermsBits.push_back(EditString(minTermsBits[i], minTermsBits[j]));
                    minTermOccurred[EditString(minTermsBits[i], minTermsBits[j])] = true;
                    repeat = true;
                }
            }			
        }
    }
    if (!repeat){
        return;
    }
    else{
        CreateTable(len);
    }
}

void ImplicantTable(){			
    int len = minTermsStr.size();
    for (int i=0 ; i<len ; i++){
        if (!track[i]){	
            implicants.push_back(minTermsStr[i]);
            implicantsBits.push_back(minTermsBits[i]);
        }
    }
    
    len = implicants.size();
    for (int i=0 ; i<len ; i++){
        for (int j=0 ; j<numMinTerms ; j++){
            table[i][j] = false;
            char temp1[30], temp2[10];	
            strcpy(temp1, implicants[i].c_str());
            strcpy(temp2, minTermsStr[j].c_str());
            char *ptr = strstr(temp1, temp2); 
            if (ptr && (temp1[ptr-temp1+strlen(temp2)]==',' || temp1[ptr-temp1+strlen(temp2)]=='\0')){
                table[i][j] = true;
            }
        }
    }
}

void FindEssentialImplicants(){
    int len = implicants.size();
    int count = 0;
    int index = -1;
    for (int i=0 ; i<numMinTerms ; i++){
        count = 0;
        for (int j=0 ; j<len ; j++){
            if (table[j][i]){
                count++;
                index = j;
            }
        }
        if (count==1){
            essentialImplicantsBits.push_back(implicantsBits[index]);
            presentFinal[index] = 1;
            for (int k=0 ; k<numMinTerms ; k++){
                if (table[index][k]){
                    for (int l=0 ; l<len ; l++){
                        table[l][k] = false;
                    }
                }
            }
        }
    }
}

void RemoveDominatingRows(){						
    int len = implicants.size();
    bool dominated = true;
    bool rDominated = true;
    for (int i=0 ; i<len ; i++){				
        for (int j=0 ; j<len ; j++){
            if (presentFinal[j]==0){
                dominated = true;
                rDominated = true;
                if (i!=j){
                    for (int k=0 ; k<numMinTerms ; k++){
                        if (table[j][k] != table[i][k]){
                            rDominated = false;			
                        }
                        if (table[j][k]==1 && table[i][k]!=1){
                            dominated = false;
                            break;
                        }
                    }
                    if (dominated && presentFinal[j]==0){
                        presentFinal[j] = -1;
                    }
                    if (rDominated){
                        presentFinal[i] = 2;	
                    }						
                }							
            }							
        }										
    }											
}											
												
void PrintResult(int numBits){						
    int len = implicants.size();
    char ch = 'A';
    for (int i=0 ; i<len ; i++){
        if (presentFinal[i]==1){				
            ch = 'A';
            for (int j=8-numBits ; j<8 ; j++){
                if (implicantsBits[i][j]=='0'){
                    cout << ch << "'";
                }
                if (implicantsBits[i][j]=='1'){
                    cout << ch;
                }
                ch++;	
            }
            cout << " + ";	
        }
    }
    cout << "\n";					
}

int main(){
    int numBits;
    cout << "Enter the number of bits: ";
    cin >> numBits;
    cout << "Enter the number of MinTerms: ";
    cin >> numMinTerms;
    int minTerms[numMinTerms];
    for (int i=0 ; i<numMinTerms ; i++){
        cout << "Enter MinTerm: ";
        cin >> minTerms[i];
    }

    sort(minTerms, minTerms+numMinTerms);			
    for (int i=0 ; i<numMinTerms ; i++){
        minTermsBits.push_back(ConvertToBits(minTerms[i]));
        minTermsStr.push_back(ConvertToString(minTerms[i]));
        track.push_back(false);
    }
    CreateTable(0);
    ImplicantTable();
    FindEssentialImplicants();
    RemoveDominatingRows();	
    PrintResult(numBits);	
    return 0;	
}
