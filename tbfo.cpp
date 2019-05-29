/*
	===============KELOMPOK KECE========================
	ANGGOTA : BAGAS PANGESTU (14117026)
			  NARDIYANSAH TRI JATMIKO (14117037)
			  DION TRIWIJAYA (16117036)
*/


#include <bits/stdc++.h> // library yang mencakup seluruh library standar seperti iostream, stdio, stdlib, stack dll.
using namespace std;

	//Definisi matriks secara Global agar tidak perlu inisiasi lagi pada sub - program
	int matriks[19][128];

		//memastikan yang dimasukkan adalah digit angka
		bool isAngka(char kar){
   			 return (kar >= '0' && kar <='9');
		}

		//operator - operator
		bool isOPRATOR(char kar){
    		return(kar=='+' || kar=='-' || kar=='*' || kar=='/' || kar=='(' || kar==')');
		}

		//kondisi operasi
		int Kondisi(char karakter){

			switch(karakter){
    		case '+' :
    		case '-' : return 1;
    		case '*' :
    		case '/' : return 2;
    		case '(' :
    		case ')' : return 3;

    		default : return -1;
    		}

		}

		//ketika menemukan simbol pada inputan maka yang dilakukan adalah seperti dibawah
		int Operasi(int x, int y, char c){
    		if(c=='+'){
        		return x+y;
    		}else if(c=='-'){
        		return x-y;
    		}else if(c=='*'){
        		return x*y;
    		}else{
        		return x/y;
    		}
		}

		//operasi aritmatika
		int Operasikan(string s){
    		stack<int> XNILAI; // menggunakan stack pada implementasi program
    		stack<char> OPERASI;

    		int temp=0;
    		int i=0;

    			while(i<s.length()){
        				char XKAR = s[i];

						if(isAngka(XKAR)){
            				temp= (temp*10) + (int)(XKAR - '0');
        				}else if(isOPRATOR(XKAR)){
            				if(XKAR=='('){
                				OPERASI.push(XKAR);
                				temp=0;
            				}else if(XNILAI.empty()){ // jika kosong nilainya
                				XNILAI.push(temp);
                				OPERASI.push(XKAR);
                				temp=0;
            				}else if(XKAR==')'){
                				XNILAI.push(temp);

								while(OPERASI.top() != '('){
                    				XKAR=OPERASI.top();
                    				OPERASI.pop();
                    				temp=XNILAI.top();
                    				XNILAI.pop();

									int pre = XNILAI.top();

									XNILAI.pop();
                    				temp = Operasi(pre,temp,XKAR);
                    				XNILAI.push(temp);
                				}
                				OPERASI.pop();
                				XNILAI.pop();

							}else{
                				char prec = OPERASI.top();

								if(prec=='('){
                    				XNILAI.push(temp);
                    				OPERASI.push(XKAR);
                    				temp=0;

								}else if(Kondisi(XKAR) > Kondisi(prec)){
                    				XNILAI.push(temp);
                    				OPERASI.push(XKAR);
                    				temp=0;

								}else{
                    				int PREVNILAI = XNILAI.top();

									XNILAI.pop();
                    				char prevop = OPERASI.top();
                    				OPERASI.pop();
                    				PREVNILAI=Operasi(PREVNILAI,temp,prevop);
                    				XNILAI.push(PREVNILAI);
                    				OPERASI.push(XKAR);
                   					temp=0;
                				}
            				}
        				}
        				i++;
    			}

				while(!OPERASI.empty()){
        			int prev = XNILAI.top();
        			XNILAI.pop();
        			char preop = OPERASI.top();
        			OPERASI.pop();
       				temp = Operasi(prev,temp,preop);
    			}
    		return temp;
		}

		bool isStuck(int state){
  			if (state < 0){
    			return true;
  			}else{
    			return false;
  			}
		}

		bool isFinal(int state){
  			if(state == 9 || state == 17 || 19){
    			return true;
  			}else{
    			return false;
 		 	}
		}

		bool isEnd(int state){
  			if(state == 17){
    			return true;
  			}else{
    			return false;
	  			}
			}


		void Simpan_operasi (string *x, char y){
    		*x = *x + y;
		}

		void Simpan_kata (string *x, char y){
  			*x = *x + y;
		}

		//menelusuri state
		void State(string x, bool *selesai){
  			int i = 0;
  			int state = 0;
  			string kata="\0";
  			string oper="\0";

  			while(i < x.length() && isStuck(state) == false){
    				state = matriks[state][x[i]];

    				if(state == 7 && x[i] != 34){
        				Simpan_kata(&kata, x[i]);
    				}else if(state==18 && x[i] != 59){
        				Simpan_operasi(&oper,x[i]);
    				}
    				i++;
  			}

  			if(isStuck(state) == true || isFinal(state) == false ){
    			kata = "\0";
    			cout << "> Masukan anda tidak sesuai dengan format"<< endl;
    			return;

			}else{
    			if(isEnd(state) == true){
        			cout << "Terima kasih telah menggunakan compiler TIM KECE";
        			*selesai = true;

				}else if(state==19){
        			int temp = Operasikan(oper);
        			cout << "> " << temp << endl;

				}else
					cout << "> " << kata << endl;
    			return;
  			}
		}


	int main(){

  		for(int i = 0 ; i < 19 ; i++){
    		for(int j = 0 ; j < 128 ; j++){
      			matriks[i][j] = -1;
    		}
  		}


		//membuat table transisi state
		matriks[0][32] = 0;
  		//huruf kecil
  		matriks[0][99] = 1;
  		matriks[1][101] = 2;
  		matriks[2][116] = 3;
  		matriks[3][97] = 4;
  		matriks[4][107] = 5;
  		matriks[5][32] = 6;
		matriks[6][32] = 6;
		matriks[6][34] = 7;

  		//operator aritmatika dan angka
  		matriks[6][40]=18;
 		matriks[6][41]=18;
  		matriks[6][42]=18;
  		matriks[6][43]=18;
  		matriks[6][45]=18;
  		matriks[6][47]=18;
  		matriks[6][48]=18;
  		matriks[6][49]=18;
  		matriks[6][50]=18;
  		matriks[6][51]=18;
  		matriks[6][52]=18;
  		matriks[6][53]=18;
  		matriks[6][54]=18;
  		matriks[6][55]=18;
  		matriks[6][56]=18;
  		matriks[6][57]=18;

  		matriks[18][40]=18;
	  	matriks[18][41]=18;
  		matriks[18][42]=18;
  		matriks[18][43]=18;
  		matriks[18][45]=18;
  		matriks[18][47]=18;
  		matriks[18][48]=18;
  		matriks[18][49]=18;
  		matriks[18][50]=18;
  		matriks[18][51]=18;
  		matriks[18][52]=18;
  		matriks[18][53]=18;
  		matriks[18][54]=18;
  		matriks[18][55]=18;
  		matriks[18][56]=18;
  		matriks[18][57]=18;
  		matriks[18][32]=18;
  		matriks[18][59]=19;
  		//huruf besar
  		matriks[0][67] = 1;
  		matriks[1][69] = 2;
  		matriks[2][84] = 3;
  		matriks[3][65] = 4;
  		matriks[4][75] = 5;

  		for(int i = 0 ; i < 128 ; i++){
    		matriks[7][i] = 7;
  		}

			matriks[7][34] = 8;
  			matriks[8][32] = 8;
  			matriks[8][59] = 9;
  			matriks[0][115] = 10;
  			matriks[10][101] = 11;
  			matriks[11][108] = 12;
  			matriks[12][101] = 13;
  			matriks[13][115] = 14;
  			matriks[14][97] = 15;
  			matriks[15][105] = 16;
  			matriks[16][32] = 16;
  			matriks[16][59] = 17;
  			matriks[0][83] = 10;
  			matriks[10][69] = 11;
            matriks[11][76] = 12;
  			matriks[12][69] = 13;
  			matriks[13][83] = 14;
  			matriks[14][65] = 15;
  			matriks[15][73] = 16;

		//IO pada program
  		string x;
  			bool selesai = false;
  			while(selesai ==false){
    			cout <<"# ";
    			getline(cin,x);
    			State(x, &selesai);
  			}

}
