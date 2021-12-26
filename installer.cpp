#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
vector<string>Get_Paths(){
    string P=getenv("PATH");
    string temp="";
    vector<string>Paths;
    for(int i=0;i<P.size();i++){
        if(P[i]==':'){
            Paths.push_back(temp);
            temp="";
        }
        else{
            temp+=P[i];
        }
    }
    Paths.push_back(temp);
    return Paths;
}
int main(int argc,char**argv){
    vector<string>Paths=Get_Paths();
    for(int i=0;i<Paths.size();i++){
        cout<<i<<" : "<<Paths[i]<<endl;

    }
    return 0;
}