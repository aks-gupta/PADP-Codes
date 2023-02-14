#include<iostream>
#include<fstream>
#include<omp.h>
#include<stdlib.h>
using namespace std;
int main(int argc,char **argv){
	
	
	string words[4]={"Lorem", "ipsum", "dolor", "amet"};
	
	for(int i=1;i<=8;i=i*2){
		
		double t = omp_get_wtime();
		#pragma omp parallel for shared(words) num_threads(i)
		for(int j=0;j<4;j++){
			int ct=0;
			fstream file;
			string s;
			file.open("words.txt");
			while(file>>s){
				if(s==words[j]){
					ct++;
				}
			}	
			cout<<"thread is "<<i<< ", word is "<<words[j]<<", count is "<<ct<<endl;
		}	
		t = omp_get_wtime() - t;
        cout<<"Time taken: "<<t<<endl;

	}
}