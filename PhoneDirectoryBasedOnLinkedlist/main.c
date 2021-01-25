#include "main.h"
#include "linkedlist.h"
#include "menu.h"
extern struct Node * head;
int main(int argc, char* argv[]){
	head = NULL; // initially there are no nodes
	FILE * fp=fopen(argv[1],"rb");
	if(fp!=NULL){
		load(argv[1]);
	}
        
        char name[51];
        char number[51]; // char entered by user
	char choice[51];
        instructions(); // display the menu
        printf( "%s", "? " );
        fgets(choice,51,stdin);
        choice[strlen(choice)-1]=0;
                while (1) { 

			if(strcmp(choice,"1")==0){
	              
	                	printf( "Enter a name and press enter: " );
				fgets(name,52,stdin);
				name[strlen(name)-1]=0;
				printf( "Enter a phone number and press enter: " );
				fgets(number,52,stdin);
				number[strlen(number)-1]=0;
				addEntry( name , number ); 
                   
                        }
                    
                	else if(strcmp(choice,"2")==0){
                		printf( "Enter a name to be deleted and press enter: " );
		                fgets(name,52,stdin);
		                name[strlen(name)-1]=0;
		        	deleteEntry(name);
                	}
                	else if(strcmp(choice,"3")==0){
		        	printf( "Enter a name to be searched and press enter: " );
		                fgets(name,52,stdin);
		                name[strlen(name)-1]=0;
		        	searchEntry(name);
                	}
                	else if(strcmp(choice,"4")==0)
                    		printPhoneDirectory();
             
                    	else if(strcmp(choice,"5")==0){
                    		if(argv[1]!=NULL)
                    			saveAndExit(argv[1]);
                    		else printf("filename is not provided - save error\n");
                  		cleanList();
                    		return 0;
                    	}
                 	else{
		            puts( "Invalid choice.\n" );
		            instructions();
                    	}
             	 

              	printf( "%s", "\nChoice again? " );
              	fgets(choice,50,stdin);
              	choice[strlen(choice)-1]=0;
           } // end while


}



