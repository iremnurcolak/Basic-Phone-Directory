#include "main.h"
#include "linkedlist.h"

int a=0;
typedef struct{
	char* name;
	char* number;
} DirectoryEntry;

struct Node  {
	DirectoryEntry* entry;
	struct Node* next;
	struct Node* prev;
};

struct Node * head;


void addEntry(char *name, char *number){
	struct Node * temp= head;
	
	while(temp!=NULL){
		if(strcmp(name,(temp->entry)->name)==0){
			free((temp->entry)->number);
			(temp->entry)->number=(char*)malloc(sizeof(char)*(strlen(number)+1));
			strcpy((temp->entry)->number,number);
			return;
		}
		temp=temp->next;
	
	}

	struct Node* newPtr= (struct Node*)malloc(sizeof(struct Node));
	DirectoryEntry * entry= (DirectoryEntry*)malloc(sizeof(DirectoryEntry));
	entry->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
	strcpy(entry->name,name);
	
	entry->number=(char*)malloc(sizeof(char)*(strlen(number)+1));
	strcpy(entry->number,number);
	newPtr->entry = entry;
	newPtr->prev = NULL;
	newPtr->next = NULL;
	
	struct Node* previousPtr = NULL;
	struct Node* currentPtr=head;

		if(head == NULL) {
			head = newPtr;
			return;
		}
		while ( currentPtr != NULL ) {
			if(strcmp(name,(currentPtr->entry)->name)>0){
				previousPtr = currentPtr;
				currentPtr = currentPtr->next;
		        }else break;
		}
		if ( previousPtr == NULL ) { 
			 newPtr->next= head;
			 head->prev=newPtr;
			 head = newPtr;
      		}
      		else { 
      			 newPtr->prev=previousPtr;
			 previousPtr->next= newPtr;
			 
			 
			 if(currentPtr!=NULL){
			 	newPtr->next= currentPtr;
			 	currentPtr->prev=newPtr;
			 	
			 }else{
			 	newPtr->next= NULL;
			 }
		}
}


void deleteEntry(char *name){

	if(head == NULL) {
		printf("deletion error - list is empty.");
		return;
	}
	else{
		struct Node* temp = head;
	        while(temp != NULL){
			if( strcmp((temp->entry)->name,name)==0 ){
		        	if(temp->prev==NULL&&temp->next==NULL){ //liste tek elemanli
		                    	head=NULL;
		                    	free((temp->entry)->name);
		                    	free((temp->entry)->number);
		                    	free(temp->entry);
		                    	free(temp);
		                }
		                else if(temp->prev==NULL&&temp->next!=NULL){ //listede 1den fazla eleman var ve head siliniyor
		                    	head=temp->next;
		                    	(temp->next)->prev=NULL;
		                    	free((temp->entry)->name);
		                    	free((temp->entry)->number);
		                    	free(temp->entry);
		                    	free(temp);
		                }
		                else if(temp->prev!=NULL&&temp->next==NULL){//eleman listenin sonundaysa
		        		struct Node* last=temp->prev;
		        		last->next=NULL;
		                    	free((temp->entry)->name);
		                    	free((temp->entry)->number);
		                    	free(temp->entry);
		                    	free(temp);
		                    	
		                }
		                else{
		                    	
		                    	(temp->next)->prev=temp->prev;
		                    	(temp->prev)->next=temp->next;
		                    	free((temp->entry)->name);
		                    	free((temp->entry)->number);
		                    	free(temp->entry);
		                    	free(temp);
		                }
		                if(a==0)
		                printf("deletion is successfull.\n");
		                return;
		         }
		         temp = temp->next;
		}
		printf("deletion error - %s does not exist in the phone directory.\n",name);
	}



}

void searchEntry(char *name){
	struct Node* temp = head;
	while(temp != NULL){
		if(strcmp((temp->entry)->name,name)==0){
			
			printf("founded: %s %s\n",(temp->entry)->name,(temp->entry)->number);
			return;
		} 
		temp=temp->next;
	}
	printf("%s is not found.\n",name);
}

void printPhoneDirectory(){
	struct Node * temp= head;
	if(head==NULL){
		printf("phone directory is empty.\n");
	}
	while(temp!=NULL){
		printf("%s %s\n",(temp->entry)->name,(temp->entry)->number);
		temp=temp->next;

	}


}
void saveAndExit(char * filename){
	a=1;
	FILE * fp=fopen(filename,"wb");
	struct Node * temp= head;
	while(temp!=NULL){
		//dosyayaonce namein uzunlugunu yaziyorumsonra da name uzunlugu kadar char okuyorum
		//ayni seyi number icin de yapiyorum
		int lenName=strlen((temp->entry)->name)+1;
		char* strName=(char *)malloc(lenName*sizeof(char));
		int lenNum=strlen((temp->entry)->number)+1;
		char* strNum=(char *)malloc(lenNum*sizeof(char));
		strcpy(strName,temp->entry->name);
		strcpy(strNum,temp->entry->number);
		fwrite(&lenName,sizeof(int),1,fp);
		fwrite(strName,sizeof(char),lenName,fp);
		fwrite(&lenNum,sizeof(int),1,fp);
		fwrite(strNum,sizeof(char),lenNum,fp);
		free(strName);
		free(strNum);
		temp=temp->next;
	}
	fclose(fp);
}
void load(char *filename){
	FILE * fp=fopen(filename,"rb");
	int lenNum,lenName;
	while( fread(&lenName,sizeof(int),1,fp)==1){
	//dosyadan once namein uzunlugunu okuyorum sonra da name uzunlugu kadar char okuyorum
	//ayni seyi number icin de yapiyorum
		char* strName=(char *)malloc(lenName*sizeof(char));
		fread(strName,sizeof(char),lenName,fp);
		fread(&lenNum,sizeof(int),1,fp);
		char* strNum=(char *)malloc(lenNum*sizeof(char));
		fread(strNum,sizeof(char),lenNum,fp);
		addEntry(strName,strNum);
		free(strName);
		free(strNum);
	}
	fclose(fp);

}
void cleanList(){
	struct Node* current = head;
	while( current != NULL ) {
	   struct Node* next = current->next;
	   deleteEntry( current->entry->name );
	   current = next;
	}
	
}
