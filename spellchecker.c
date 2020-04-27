#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_DOC_LEN 100
#define MAX_DIC_CAPACITY 100
#define MAX_WORD_LENGTH 20
#define MAX_MRU_LENGTH 10


int mru_count = 0;


typedef struct dict_node_type
{
    char ch;
    struct dict_node_type *next;

}dict_node;

typedef struct dictionary_type
{
    dict_node *head;
    struct dictionary_type *next;

}dictionary;

dictionary dl[MAX_DIC_CAPACITY];

typedef struct mru_node_type
{
    struct mru_node_type *next;
    int freq;
    char word[MAX_WORD_LENGTH];  

}mru_node;

typedef struct missing_node_type
{

    struct missing_node_type *next;
    char word[MAX_WORD_LENGTH];
    int freq;


}missing_list;


char string[MAX_WORD_LENGTH];

int is_punc(char ch);
void print_dictionary(dictionary *dlptr);
dictionary *insert_word(dictionary *dlptr, char s[]);
dict_node *make_dict_node(char ch);
dictionary *make_dictionary_node(dict_node *ptr);
dict_node *insert_dict_node(dict_node *lptr , char ch);
dictionary *insert_dictionary_node(dictionary *prev,dict_node *dptr,dictionary *dlptr);
char *convert_to_string(dict_node *ptr);
dictionary *find_insert_pos(char s[],dictionary *dlptr);
mru_node *make_mru_node(char s[]);
mru_node *find_mru_insert_pos(char s[],mru_node *mlptr);
mru_node *insert_mru_node(mru_node *mlptr,char s[]);
void delete_mru_node(mru_node *mlptr);
void print_mru_list(mru_node *mlptr);
void initialize_mru_list(mru_node *mlptr);
mru_node *search(mru_node *mlptr, char s[]);
dictionary *create_dict();
int search_dict(dictionary *dlptr,char s[]);
missing_list *make_missing_node(char s[]);
missing_list *search_miss_list(missing_list *last,char s[]);
void print_miss_list(missing_list *last);
missing_list *insert_miss_list_end(missing_list *last,char s[]);
missing_list *insert_miss_list_strt(missing_list *last,char s[]);


int main()
{   

    mru_node *mlptr=NULL,*ptr;
    char word[MAX_WORD_LENGTH];
   char file_name[MAX_WORD_LENGTH];

   printf("Enter file name\n\n");
   scanf("%s",file_name);

    dictionary *dlptr=NULL;
    missing_list *mptr,*last=NULL,*clptr;



   // dlptr=create_dict();

    //print_dictionary(dlptr);


    FILE *fp = fopen(file_name, "r");

    if(fp == NULL)
    {
        printf("\nNO FILE FOUND\n");
    }   

    dlptr=create_dict();


    print_dictionary(dlptr); 


 

    char ch;
    int i = 0;
    int j = 0;
    int flag = 0;
    
    ch = fgetc(fp);

    while(ch != EOF) 
    {
        if(is_punc(ch))
        {   
            if(flag==1)
            {
                word[j] = '\0';

                ptr=search(mlptr,word);
        

                if(ptr==NULL)
                {   
                        if(search_dict(dlptr,word))
                        {
                            if(mru_count<10)
                            {
                                mlptr=insert_mru_node(mlptr,word);
                                mru_count++;
                            }
                            else
                            {
                                mlptr=insert_mru_node(mlptr,word);
                                delete_mru_node(mlptr);
                            }

                        } 
                      else
                        {  
                        
                           mptr=search_miss_list(last,word);
                           if(mptr==NULL)
                           {
                            last=insert_miss_list_end(last,word);
                           }
                           else
                           {   
                               int freq;
                               freq=mptr->freq+1;
                               clptr=last->next;

                               while(clptr->next!=mptr)
                               {
                                   clptr=clptr->next;
                               }

                               clptr->next=mptr->next;

                               free(mptr);

                                last=insert_miss_list_strt(last,word);

                                last->next->freq=freq;



                           }
                           
                        
                        }
                        
                          
                    
                    
                    

                }
                else if(ptr == mlptr)
                {
                    ptr->freq+=1;
                }
                else
                {
                    int fre;
                    mru_node *post;
                    post = ptr->next;
                    fre=post->freq + 1;
                    
                    mlptr=insert_mru_node(mlptr,post->word);
                    mlptr->freq=fre;

                    ptr->next = post->next;

                    free(post);
                    
                }
                



                j=0;
                
                flag=0;
            }
        }
        else
        {
             word[j] = ch;
             j++;
             flag=1;
        }
        
        ch = fgetc(fp);
    }


    printf("\n1. Print MRU list");
    printf("\n2. Print miss list\n");


        print_mru_list(mlptr);
    


        print_miss_list(last);
    

 
 

   

 







    //print_mru_list(mlptr);





    //print_miss_list(last);




   

    
    
    










    ////////////////////////////////////////////////////////


}

dictionary* create_dict()
{   
    int done = 0;
    char str[MAX_WORD_LENGTH];
    dictionary *dlptr=NULL;
    
    
    /*

     dlptr=insert_word(dlptr,"a\0");
     dlptr=insert_word(dlptr,"the\0");
     dlptr=insert_word(dlptr,"The\0");
     dlptr=insert_word(dlptr,"of\0");
     dlptr=insert_word(dlptr,"an\0");

     dlptr=insert_word(dlptr,"is\0");
     dlptr=insert_word(dlptr,"language\0");
     dlptr=insert_word(dlptr,"I\0");
     dlptr=insert_word(dlptr,"like\0");
     dlptr=insert_word(dlptr,"all\0");

     dlptr=insert_word(dlptr,"He\0");
     dlptr=insert_word(dlptr,"he\0");
     dlptr=insert_word(dlptr,"it\0");
     dlptr=insert_word(dlptr,"real\0");
     dlptr=insert_word(dlptr,"beauty\0");

     dlptr=insert_word(dlptr,"sleep\0");
     dlptr=insert_word(dlptr,"store\0");
     dlptr=insert_word(dlptr,"you\0");
     dlptr=insert_word(dlptr,"your\0");
     dlptr=insert_word(dlptr,"ready\0");

     dlptr=insert_word(dlptr,"kill\0");
     dlptr=insert_word(dlptr,"like\0");
     dlptr=insert_word(dlptr,"serious\0");
     dlptr=insert_word(dlptr,"efficient\0");
     dlptr=insert_word(dlptr,"cry\0");


     dlptr=insert_word(dlptr,"smile\0");
     dlptr=insert_word(dlptr,"on\0");
     dlptr=insert_word(dlptr,"off\0");
     dlptr=insert_word(dlptr,"away\0");
     dlptr=insert_word(dlptr,"near\0");


     dlptr=insert_word(dlptr,"put\0");
     dlptr=insert_word(dlptr,"cut\0");
     dlptr=insert_word(dlptr,"for\0");
     dlptr=insert_word(dlptr,"better\0");
     dlptr=insert_word(dlptr,"slow\0");


     dlptr=insert_word(dlptr,"fast\0");
     dlptr=insert_word(dlptr,"fear\0");
     dlptr=insert_word(dlptr,"style\0");
     dlptr=insert_word(dlptr,"inefficient\0");
     dlptr=insert_word(dlptr,"code\0");

     dlptr=insert_word(dlptr,"boys\0");
     dlptr=insert_word(dlptr,"girls\0");
     dlptr=insert_word(dlptr,"mysterious\0");
     dlptr=insert_word(dlptr,"regular\0");
     dlptr=insert_word(dlptr,"amazed\0");


     dlptr=insert_word(dlptr,"name\0");
     dlptr=insert_word(dlptr,"nothing\0");
     dlptr=insert_word(dlptr,"tremendous\0");
     dlptr=insert_word(dlptr,"computer\0");
     dlptr=insert_word(dlptr,"science\0");

    */

       FILE *fp1 = fopen("dictfile.txt", "r");

    if(fp1 == NULL)
    {
        printf("\nNO FILE FOUND\n");
    }
    else
    {
        //printf("\nFile Found");
        //fscanf( fp1, "%s", str);
        //printf("%s",str);

        while(fgetc(fp1)!=EOF)
        {
            fscanf( fp1, "%s", str);
            dlptr=insert_word(dlptr,str);

            //printf("%s",str);
        }


    }
    

    while(!done)
    {
        printf("\n\n ENTER WORD TO BE ADDED TO DICTIONARY press 1 to quit \n\n");

        scanf("%s",str);
       

        if(str[0]=='1')
        {
            done=1;
        }
         if(done==0)
         {
          dlptr=insert_word(dlptr,str);
         }
        
    }

    return dlptr;

    

}




int is_punc(char ch)
{
    int retval;

    if(ch == '.' || ch == ',' || ch == '"' || ch == '?'|| ch == '!' || ch == ' '|| ch == '-')
    {
        retval = 1;
    }
    else
    {
        retval = 0;
    }

    return retval;
    
}

void print_dictionary(dictionary *dlptr)
{
    dictionary *dptr;
    dict_node *ptr;

    dptr = dlptr;

    
        printf("\n\n THE DICTIONARY : \n\n");

    while(dptr!=NULL)
    {
        ptr=dptr->head;


        while(ptr!=NULL)
        {
            printf("%c",ptr->ch);
            ptr=ptr->next;
        }
    
        dptr=dptr->next;

        printf("\n");


    }


}


dictionary *insert_word(dictionary *dlptr, char s[])
{
    int i=0;
    dict_node *lptr=NULL;
    dictionary *pos;
    char *check;
    

    while(s[i]!='\0')\
    {
        
        lptr = insert_dict_node(lptr,s[i]);
        i++;
    }




        pos=find_insert_pos(s,dlptr);
        dlptr=insert_dictionary_node(pos,lptr,dlptr);


    return dlptr;


}

dict_node *make_dict_node(char ch)
{
    dict_node *nptr;

    nptr = (dict_node*)malloc(sizeof(dict_node));
    nptr->ch = ch;
    nptr->next = NULL;

    return nptr;
}

dictionary *make_dictionary_node(dict_node *ptr)
{
    dictionary *nptr;

    nptr = (dictionary*)malloc(sizeof(dictionary));
    nptr->head = ptr;
    nptr->next = NULL;

    return nptr;
}

dict_node *insert_dict_node(dict_node *lptr , char ch)
{
    dict_node *nptr,*ptr;
    nptr=make_dict_node(ch);
    ptr = lptr;
    
    if(lptr==NULL)
    {
        lptr=nptr;
    }
    else 
    {
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }

        ptr->next=nptr;

    }

    return lptr;

}

dictionary *insert_dictionary_node(dictionary *prev,dict_node *dptr,dictionary *dlptr)
{
    dictionary *nptr,*ptr,*post;
    ptr=prev;
    nptr=make_dictionary_node(dptr);


    if(prev==NULL)
    {
        nptr->next = dlptr;
        dlptr=nptr;
    }
    else if(prev->next==NULL)
    {
        prev->next=nptr;
    }
    else
    {
        post=prev->next;
        prev->next=nptr;
        nptr->next=post;
    }
    
    return dlptr;
}


char *convert_to_string(dict_node *ptr)
{
    
    int i=0,j=0;

    for(j=0;j<MAX_WORD_LENGTH;j++)
    {
        string[j]='\0';
    }



    while(ptr!=NULL)
    {
        string[i]=ptr->ch;
        ptr=ptr->next;
        i++;
    }

    return string;

}

dictionary *find_insert_pos(char s[],dictionary *dlptr)
{       
    char *str;
    dictionary *prev=NULL;

    if(dlptr==NULL)
    {
        prev=NULL;
    }
    else
    {
        
            str = convert_to_string(dlptr->head);
        

            while(strcmp(s,str)>0&&dlptr!=NULL)
            {   
                
                prev=dlptr;
                dlptr=dlptr->next;

                if(dlptr!=NULL)
                {

                     str = convert_to_string(dlptr->head);

                }
                
            }



    
    }
    

    return prev;


}





int search_dict(dictionary *dlptr,char s[])
{
    dictionary *ptr;
    ptr=dlptr;
    char *str;
    int retval=0;

    while(ptr!=NULL)
    {
         str = convert_to_string(ptr->head);

         

         if(strcmp(str,s)==0)
         {
             retval = 1;
         }

         ptr=ptr->next;



    }

    return retval;


}







//make MRU node

mru_node *make_mru_node(char s[])
{
    mru_node *nptr;
    int i=0;

    nptr  = (mru_node*)malloc(sizeof(mru_node));
    nptr->freq=1;
    
    while(s[i]!='\0')
    {
        nptr->word[i]=s[i];
        i++;
    }

    nptr->word[i+1]='\0';

    nptr->next=NULL;

    return nptr;

}

mru_node *insert_mru_node(mru_node *mlptr,char s[])
{   
    mru_node *nptr = make_mru_node(s);

     nptr->next=mlptr;
     mlptr=nptr;

     return mlptr;
}

void delete_mru_node(mru_node *mlptr)
{   
    
    mru_node *ptr,*prev;
    ptr=mlptr;
    prev=NULL;

    while(ptr->next!=NULL)
    {
        prev=ptr;
        ptr=ptr->next;
    }

    prev->next=NULL;

}

void print_mru_list(mru_node *mlptr)
{
    mru_node *ptr,*sptr;
    ptr=mlptr;
    

    printf("\n\n THE MRU LIST ALPHABETICAL ORDER : \n\n");

    int count = 0;
    int i,j,k;


     for(k=0;k<10;k++)
    {
        ptr=mlptr;


    for(i=0;i<10;i++)
    {   
        sptr=mlptr;
        count=0;

       

            for(j=0;j<10;j++)
            {

                if(strcmp(ptr->word,sptr->word)>0)
                {
                    count++;
                }

                sptr=sptr->next;
            }

            if(count==k)
            {
                printf("%s-----%d\n",ptr->word,ptr->freq);
            }

            ptr=ptr->next;
        
        }
    }
    
    ptr=mlptr;

    printf("\n\n THE MRU LIST : \n\n");

    while(ptr!=NULL)
    {
       printf("%s-------%d",ptr->word,ptr->freq);
       printf("\n");
       ptr=ptr->next;
    }

}


mru_node *search(mru_node *mlptr, char s[])
{   
    mru_node *ptr,*retval,*prev;
    retval = NULL;

    ptr=mlptr;

    if(ptr!=NULL)
    {

        if(ptr->next==NULL&&strcmp(s,ptr->word)==0)
        {
            retval = mlptr; 
        }

        else
        {

            while(ptr!=NULL)
            {   

                prev=ptr;
                ptr=ptr->next;

                if(ptr!=NULL)
                 {

                    if(strcmp(s,ptr->word)==0)
                    {
                        retval = prev;
                    }

                 }

            
            }
            
        }

    }
    return retval;

}



/////miss list

missing_list *make_missing_node(char s[])
{
    missing_list *nptr;
    int i=0;

    nptr=(missing_list*)malloc(sizeof(missing_list));

    nptr->freq=1;

       while(s[i]!='\0')
    {
        nptr->word[i]=s[i];
        i++;
    }

    nptr->word[i+1]='\0';

    nptr->next=NULL;

    return nptr;
    
}

missing_list *insert_miss_list_strt(missing_list *last,char s[])
{   
    missing_list *nptr;
    nptr=make_missing_node(s);

    if(last==NULL)
    {
        last = nptr;
        last->next=nptr;
    }
    else
    {
         nptr->next=last->next;
         last->next=nptr;
    }
    

    return last;


}

missing_list *insert_miss_list_end(missing_list *last,char s[])
{
    missing_list *nptr,*ptr;
    nptr = make_missing_node(s);

    if(last==NULL)
    {
        last=nptr;
        last->next=nptr;
    }
    else
    {  
       ptr=last->next;
       last->next=nptr;
       nptr->next=ptr;
       last=nptr;

    }
    

        return last;


}





missing_list *search_miss_list(missing_list *last,char s[])
{
    missing_list *ptr,*retval;
    retval = NULL;

    if(last!=NULL)

    {


    ptr=last->next;

    while(ptr!=last)
    {
        if(strcmp(ptr->word,s)==0)
        {
            retval=ptr;
        }

        ptr=ptr->next;

    }

        if(strcmp(ptr->word,s)==0)
        {
            retval=ptr;
        }

    }

    return retval;
}


void print_miss_list(missing_list *last)
{
    missing_list *ptr=last->next;

    printf("\n\n THE MISSING LIST : \n\n");

    while(ptr!=last)
    {
        printf("%s-------%d",ptr->word,ptr->freq);
        printf("\n\n");
        ptr=ptr->next;

    }

        printf("%s-------%d",ptr->word,ptr->freq);
        printf("\n");




}










