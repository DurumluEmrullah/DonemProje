#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include<ctype.h>
typedef struct String {
   char characters[50];
   int length;
}String;

int charAt(String *s, int indeks);
String *concat(String *s1, String *s2);
unsigned int strSearch(String *s1, String *s2);
unsigned int findScore(String *s1);
int operationIndex(String s,char op);
int countWord(String s);
String fonk(String s);

int main(int argc,char* argv[]){
	char control[4];
	int counterLetter=0;
	int counterWord=0;
	unsigned int score;
	String *newString;
	
	String a[40];
	if(argc==1) 
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc ==2)
    	printf("Enter the output file name\n");
 	
 	
	FILE *input = fopen(argv[1], "r");
 	FILE *output = fopen(argv[2], "w");
	int i =0;
  	while(! feof(input) ){
  	fgets(a[i].characters,50,input); 
   	a[i].length =strlen( a[i].characters);
   	i++;
  	}
	
  	fclose(input);
	int index;
	int c ;
	int j=0;
	int word =0;
	for(;j<i;j++){
	
		int op = operationIndex(a[j],':');
		switch(a[j].characters[op+1]){
			case '1':
				c=0;
				while(c<a[j].length){
					if((a[j].characters[c]>=65 && a[j].characters[c]<=90) ||(a[j].characters[c]>=97 && a[j].characters[c]<=122)){
						counterLetter++;
					}					
					c++;
				}
				word+=countWord(a[j])+1;
				fprintf(output,"%c\n",charAt(&a[j],a[j].characters[(operationIndex(a[j],',')+1)]-'0'));
				break;
			case '2':
				c=0;
				while(c<a[j].length){
					if((a[j].characters[c]>=65 && a[j].characters[c]<=90) ||(a[j].characters[c]>=97 && a[j].characters[c]<=122)){
						counterLetter++;
					}					
					c++;
				}
				word+=countWord(a[j])+2;
				newString=concat(&a[j],newString);	
				fprintf(output,"%s",newString);
				break;
			case '3':
				c=0;
				while(c<a[j].length){
					if((a[j].characters[c]>=65 && a[j].characters[c]<=90) ||(a[j].characters[c]>=97 && a[j].characters[c]<=122))
						counterLetter++;					
					c++;
				}
				String inWord =fonk(a[j]);
				inWord.length=strlen(inWord.characters);
				 
				fprintf(output,"%d\n",strSearch(&a[j],&inWord));
				word+=countWord(a[j])+2;
				break;
			case '4':
				c=0;	
				while(c<a[j].length){
					if((a[j].characters[c]>=65 && a[j].characters[c]<=90) ||(a[j].characters[c]>=97 && a[j].characters[c]<=122)){
						counterLetter++;
					}					
					c++;
				}
				word+=countWord(a[j])+1;
				score =findScore(&a[j]);
				fprintf(output,"%d\n",score);
				break;	
		}
		
		int i =0;
		for(;i<4;i++){
			control[i]=a[j].characters[i];
		}
	
		if(strcmp(control,"stat")==0)
		{
			fprintf(output,"The number of words: %d\n",word);
			fprintf(output,"The number of alphabetic letters: %d\n",counterLetter);
		}
			
		if(strcmp(control,"exit")==0||strcmp(control,"quit")==0)
		{
			fprintf(output,"Program ends. Bye\n");
			fclose(output);
			return;
		}
		
		}
		
	fclose(output);
	return 0;
}

int charAt(String *s, int indeks){
	return s->characters[indeks];
}

String *concat(String *s1, String *s2){
	int indexOfColon,indexOfComma;
	bool isSpace =false;
	s2=s1;
	indexOfColon = operationIndex(*s1,':');
	indexOfComma = operationIndex(*s1,',');
	
	while (indexOfComma<s1->length){
			if(!isSpace){
			isSpace = !isSpace;
			s2->characters[indexOfColon] =' ';
			indexOfComma++;
			indexOfColon++;
			continue;
		}
		s2->characters[indexOfColon]=s1->characters[indexOfComma];
		indexOfColon++;
		indexOfComma++;
		
	}
	while(indexOfColon<s2->length){
		s2->characters[indexOfColon]=0;
		indexOfColon++;
	}
	return s2;
}

unsigned int strSearch(String *s1, String *s2){
	unsigned int i =0,j=0;
	bool ok=true;
	int start,finish;
	while(i<s1->length){
		if(s1->characters[i]==s2->characters[j]){
			
			j++;
			if(j==s2->length){
				break;
			}
			
		}
		else 
		{
			j=0;
			ok=false;
		}
		i++;
	}
	start =i;
	finish=i;
	
	while(start>0){
		if(s1->characters[start]==' '){
			break;
		}
		start--;
	}
	while(finish<s1->length){
		if(s1->characters[finish]==' ' || isalnum(s1->characters[finish])==0){
			break;
		}
		finish++;
	}	
	unsigned int length=(finish-start)-1;	
	if(start == 0)
		length=(finish-start);
	return length;
}
unsigned int findScore(String *s1){
	int i =0;
	unsigned int score=0;
	for(;i<s1->length;i++){
		
		switch(toupper(s1->characters[i])){
			
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
			case 'L':
			case 'N':
			case 'R':
			case 'S':
			case 'T':	
				score +=1;
				break;
			case 'D':
			case 'G':
				score +=2;
				break;
			case 'B':
			case 'C':
			case 'M':
			case 'P':
				score +=3;
				break;
			case 'F':
			case 'H':
			case 'V':
			case 'W':
			case 'Y':
				score +=4;
				break;
			case 'K':
				score+=5;
				break;
			case 'J':
			case 'X':
				score +=8;
				break;
			case 'Q':
			case 'Z':
				score +=10;
				break ;
					
		}
	}
	return score;
}
int operationIndex(String s,char op){
	int i =0;
	while(i<s.length){
		if(s.characters[i]==op)
			break;
			
		i++;	
	}
	
	return i;
}
int countWord(String s){
	int count=0;
	int i=0;
	while(i<s.length){
	if(s.characters[i]==' ')
		count ++;
			
	i++;	
	}
	return count;
}
String fonk(String s){
	String operationThreeString;
			int op = operationIndex(s,',');
			op++;
			int i=0;
			while(op<s.length-1){
				operationThreeString.characters[i]=s.characters[op];
				i++;
				op++;
				
			}
		
		return operationThreeString;
}


