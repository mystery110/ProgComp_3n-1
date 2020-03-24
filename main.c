#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXPAYLOAD 30000000
#define INPUTMAXPAYLOAD 15 

unsigned int answer[MAXPAYLOAD]={0};
unsigned int calculation(unsigned int );
struct data {
	int input ;
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
	 * create a circular linked list for every number in process
	 */
	struct data* first =malloc(sizeof(struct data));
	first->input=input;
	first->previous=NULL;
	struct data * last=first,*temp;
	/*
	 * circulat linked list
	 */
	unsigned int loop ;
	if(input%2==0){
		/*input is even number 
		 */
		loop=input/2;	
	}
	else {
		loop=input*3;
		loop++;
	}	

	while(loop!=1){
		/*find out every number during the calculation 
		 */
		
		temp=malloc(sizeof(struct data));
		temp->input=input;
		temp->previous=last;
		last=temp;

		if(loop%2==0){
			/*input is even number 
			 */
			loop/=2;	
		}
		else {
			loop*=3;
			loop++;
		}
/*	
		if(answer[loop]!=0){
			//the input is solved previously
			printf("Input is :%u\n",loop);
			printf("The ans is :%u\n",answer[loop]);
			ans=answer[loop];
			break;
		}
		*/
	}
	
	while(last!=NULL){
		temp=last;
		last=last->previous;
		answer[temp->input]=++ans;
		free(temp);
	}
	return answer[input];
}

