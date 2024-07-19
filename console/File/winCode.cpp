#include <bits/stdc++.h>
using namespace std;
class winCode{
	private:
		//Code ID
		string spiltCode(const vector<string> code){
			string returnText = "";
			for(int i = 1; i < code.size() ; ++i){
				returnText += code[i];
				returnText += ' ';	
			}
			return returnText;
		}
		//Function
		void cmd(const string code){
			system(code.c_str());
			return ;
		}
		void cnt(const string code){
			return ;
		}
	public:
		void Running(const vector<string> code){
			string first = code[0], Parameter = spiltCode(code);
			if(first == "cmd"){
				cmd(Parameter);
			}
			else{
				cnt(Parameter);
			}
		}
};
