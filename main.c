#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXPAYLOAD 1000000
#define INPUTMAXPAYLOAD 15 

unsigned int answer[MAXPAYLOAD]={0};
unsigned int calculation(unsigned int );
struct data {
	unsigned int input ;
	struct data *previous;

};
int main (){
	char input[INPUTMAXPAYLOAD];
	unsigned int smaller_value,larger_value,loop;
	answer[1]=1;
	/*
	 * is the input is 1 , the answer will be 1 as well
	 */

	unsigned int final_ans=0,temp;

	while(fgets(input,sizeof(input),stdin)!=NULL){
		/*Handle EOF
		 */
		if(input[0]=='\n')
			break;
			/*Handle empty line
			 */
		sscanf(input,"%u %u",&smaller_value,&larger_value);
		printf("%u %u ",smaller_value,larger_value);
		if(smaller_value>larger_value){
			/*
			 * swap their value if larger_value is < smaller value 
			 */
			temp=smaller_value;
			smaller_value=larger_value;
			larger_value=temp;
		}
		loop=smaller_value;
			 /*
			  * Start calculating from smaller value to larger value 
			  */
		while(loop<=larger_value){
			temp=calculation(loop);
			if(temp>final_ans){
				final_ans=temp;
			}
			loop++;
		}
		printf("%u\n",final_ans);
		final_ans=0;
		memcpy(input,"\0",INPUTMAXPAYLOAD);
	}

}

unsigned int calculation (unsigned int input){
	if(input==1){
		return 1;
	}
	else if(answer[input]!=0){
		return answer[input];
	}
	int ans=1;
	
	/*
	 * circulat linked list
	 */
	struct data * first=NULL,*last=NULL,*temp=NULL;
	unsigned int loop =input;
	int count =0;
	while(loop!=1){

		/*find out every number during the calculation 
		 */	
		if(loop<1000000 && answer[loop]!=0){
			/*
			 * the input is solved previously
			 */
			ans=answer[loop];
			break;
		}

		if(first==NULL){
			/* create a circular linked list for every number in process
			 * if this is the first number
			 */
			first =malloc(sizeof(struct data));
			first->input=loop;
			first->previous=NULL;
			last=first;
		}

		else {
			temp=malloc(sizeof(struct data));
			temp->input=loop;
			temp->previous=last;
			last=temp;
		}

		if(loop%2==0){
			/*input is even number 
			 */
			loop/=2;	
		}
		else {
			loop*=3;
			loop++;
		}
		count++;
	}
	while(last!=NULL){
		temp=last;
		last=last->previous;
		++ans;
		if(temp->input<1000000){
			answer[temp->input]=ans;
		}
		free(temp);
	}
	return answer[input];
}

