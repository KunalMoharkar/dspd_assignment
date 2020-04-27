#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE_MAIN_STATION 270
#define NO_OF_BASE_STATIONS 27
#define NO_OF_PHONES_PER_STATION 5
#define NO_OF_LEVELS 4


typedef struct moblie_set_tag
{   
    int size;
    int *left_arr;
    int *middle_arr;
    int *right_arr;
    int left_top;
    int right_top;
    int middle_top;

}mobile_set;

typedef struct station_tag
{
    int index_low;
    int index_high;
    struct station_tag *left;
    struct station_tag *middle;
    struct station_tag *right;
    mobile_set *mset;

}station;

typedef struct queue_tag
{
    station* node[100];
    int front;
    int rear;
   
}queue;






mobile_set* makemobile_set(int size);
station* makestation(int index_low ,int index_high,int size);
station* make_routing_system();
void traverse(station *root);
void insert_array(int mobile_num,station *ptr,int action);
void insert(int mob_no,int station_id,station *root);
station* search(int mob_no,station *root);
int search_arr(int mob_no,station *ptr,int action);
station* delete(int mob_no,station *root);
void delete_arr(int mob_no,station *ptr,int index,int action);
station* getstationbyid(int id,station *root);
station* getlowestrouter(int base_1,int base_2,station *root);
void getexchangelist(int mob_no_1,int mob_no_2,station *root);
int isempty(int id,station *root);
int ismember(int id,int mob_no,station *root);
int findphone(int mob_no,station *root);
void getmobileset(int id,station *root);
void getmobileset(int id,station *root);
int movephone(int mob_no,int id,station *root);
int binarySearch(int arr[], int l, int r, int x);
void printroutingstructure(station *root);
void initialize_queue(queue *qptr);
void insertque(station* node,queue *qptr);
station* deleteque(queue *qptr);
void showqueue(queue *qptr);
int isqueempty(queue *qptr);
station *insertlevelorder(station *root,queue *qptr,int index_low,int index_high,int size);
void printLevelOrder(station* root) ;
void printGivenLevel(station* root, int level) ;
int height(station *root) ;
int maximum(int a,int b,int c);

int main()
{
    station *root = NULL;
    station *ptr;

    int i=0,index,base_id,mob_no,j,done=0,action,retval;
    int base_id_1,base_id_2,mob_no_1,mob_no_2;
    int index_low,index_high;

    queue q;

    initialize_queue(&q);


    FILE *file = fopen("basedata.txt","r");

    for(i=1;i<=NO_OF_LEVELS;i++)
    {
        for(j=1;j<=pow(3,i-1);j++)    
        {
             fscanf(file,"%d",&index_low);
            fscanf(file,"%d",&index_high);

             root = insertlevelorder(root,&q,index_low,index_high,MAX_SIZE_MAIN_STATION/pow(3,i-1));

        }    

    }        
    //root = make_routing_system();

    FILE *fp = fopen("mobiledata.txt","r");

    for(i=0;i<NO_OF_BASE_STATIONS;i++)
    {
        fscanf(fp,"%d",&base_id);

        for(j=0;j<NO_OF_PHONES_PER_STATION;j++)
        {
            fscanf(fp,"%d",&mob_no);

            insert(mob_no,base_id,root);
        }

    }

   


    while(!done)
    {   

        printf("\n SELECT YOU ACTION \n");
        printf("0.print the entire route structure\n");
        printf("1.check if empty\n");
        printf("2.check is member\n");
        printf("3.insert a number\n");
        printf("4.delete a phone number\n");
        printf("5.get the set of phones\n");
        printf("6.find a phone\n");
        printf("7.get lowest router\n");
        printf("8.get call path\n");
        printf("9.move a phone\n");
    
        scanf("%d",&action);

        switch (action)
        {
            case 0:

                printroutingstructure(root);





                break;
            
            case 1:
                
                printf("Enter the station id \n");
                scanf("%d",&base_id);
                retval = isempty(base_id,root);

                if(retval == 1)
                {
                    printf("Set is empty\n");
                }
                else if(retval == 0)
                {
                    printf("Set is not empty\n");
                }
                else
                {
                    printf("invalid id\n");
                }
                


                break;

            case 2:

                printf("Enter the station id and mobile no \n");
                scanf("%d",&base_id);
                scanf("%d",&mob_no);

                retval = ismember(base_id,mob_no,root);

                if(retval == 1)
                {
                    printf("it is the member\n");
                }
                else if(retval == 0)
                {
                    printf("not a member\n");
                }
                else
                {
                    printf("invalid id\n");
                }

                break;
            case 3:

                
                printf("Enter the station id and mobile no \n");
                scanf("%d",&base_id);
                scanf("%d",&mob_no);

                insert(mob_no,base_id,root);

                printf("Successful insertion \n");

                break;

            case 4:

                printf("Enter the mobile no \n");
                scanf("%d",&mob_no);
                ptr = delete(mob_no,root);

                if(ptr != NULL)
                {
                    printf("deletion successful\n");
                }
                else
                {
                    printf("no such phone exists\n");
                }
                

                break;

            case 5:
                printf("Enter the station id \n");
                scanf("%d",&base_id);
                getmobileset(base_id,root);
                break;                       
            
            case 6:

                printf("Enter the mobile no \n");
                scanf("%d",&mob_no);

                retval = findphone(mob_no,root);

                if(retval == -1)
                {
                    printf("cannot find the phone\n");
                }
                else
                {
                    printf("%d is the base station id of phone\n",retval);
                }
                


                break;

            case 7:

                printf("Enter the base id's\n\n");
                scanf("%d",&base_id_1);
                scanf("%d",&base_id_2);

                if(base_id_1 > base_id_2)
                {
                     ptr = getlowestrouter(base_id_2,base_id_1,root);
                } 
                else
                {
                     ptr = getlowestrouter(base_id_1,base_id_2,root);
                }
                
                if(ptr == NULL)
                {
                    printf("%d is the lowest router\n",base_id_1);
                }
                else
                {
                    printf("%d is the lowest router\n",ptr->index_low);
                }
                


               

                break;

            case 8:
                printf("Enter the mobile numbers \n");
                scanf("%d",&mob_no_1);
                scanf("%d",&mob_no_2);

                if(mob_no_1 == mob_no_2)
                {
                    printf("call cannot be made\n");
                }

                else
                {
                     getexchangelist(mob_no_1,mob_no_2,root);
                }
                
            
            


                break;    

            case 9:

                printf("Enter the station id and mobile no \n");
                scanf("%d",&base_id);
                scanf("%d",&mob_no);

                retval = movephone(mob_no,base_id,root);

                if(retval == 1)
                {
                    printf("succesfully moved \n");
                }
                else
                {
                     printf("invalid query \n");
                }
                

                break;

        
        }


    }

    
}

mobile_set* makemobile_set(int size)
{
    mobile_set *nptr;
    nptr = (mobile_set*)malloc(sizeof(mobile_set));

    nptr->size = size;
    nptr->left_arr = (int*)malloc(sizeof(int)*size);
    nptr->middle_arr = (int*)malloc(sizeof(int)*size);
    nptr->right_arr = (int*)malloc(sizeof(int)*size);
    nptr->left_top = 0;
    nptr->middle_top = 0;
    nptr->right_top = 0;

    return nptr;

}


station* makestation(int index_low ,int index_high,int size)
{
    station *nptr;
    nptr = (station*)malloc(sizeof(station));
    nptr->index_low = index_low;
    nptr->index_high = index_high;
    nptr->mset = makemobile_set(size);
    nptr->left = NULL;
    nptr->middle = NULL;
    nptr->right = NULL;

}

station* make_routing_system()
{
    station *root;

    root = makestation(68,128,270);

    root->left = makestation(25,48,90);
    root->middle = makestation(82,108,90);
    root->right = makestation(142,162,90);

    root->left->left = makestation(10,20,30);
    root->left->middle = makestation(30,40,30);
    root->left->right = makestation(50,60,30);
    root->middle->left = makestation(70,80,30);
    root->middle->middle = makestation(90,100,30);
    root->middle->right = makestation(110,120,30);
    root->right->left = makestation(130,140,30);
    root->right->middle = makestation(150,160,30);
    root->right->right = makestation(170,180,30);

    root->left->left->left = makestation(9,0,10);
    root->left->left->middle = makestation(11,0,10);
    root->left->left->right = makestation(21,0,10);
    root->left->middle->left = makestation(29,0,10);
    root->left->middle->middle = makestation(31,0,10);
    root->left->middle->right = makestation(41,0,10);
    root->left->right->left = makestation(49,0,10);
    root->left->right->middle = makestation(51,0,10);
    root->left->right->right = makestation(61,0,10);
    root->middle->left->left = makestation(69,0,10);
    root->middle->left->middle = makestation(71,0,10);
    root->middle->left->right = makestation(81,0,10);
    root->middle->middle->left = makestation(89,0,10);
    root->middle->middle->middle = makestation(91,0,10);
    root->middle->middle->right = makestation(101,0,10);
    root->middle->right->left = makestation(109,0,10);
    root->middle->right->middle = makestation(111,0,10);
    root->middle->right->right = makestation(121,0,10);
    root->right->left->left = makestation(129,0,10);
    root->right->left->middle = makestation(131,0,10);
    root->right->left->right = makestation(141,0,10);
    root->right->middle->left = makestation(149,0,10);
    root->right->middle->middle = makestation(151,0,10);
    root->right->middle->right = makestation(161,0,10);
    root->right->right->left = makestation(169,0,10);
    root->right->right->middle = makestation(171,0,10);
    root->right->right->right = makestation(181,0,10); 

    return root;

}

void traverse(station *root)
{   int i=0;
    if(root != NULL)
    {   
        printf("%d ",root->index_low);
        printf("\n\n");

        printf("LEFT CONTENTS :\n");
        for(i=0;i<root->mset->left_top;i++)
        {
            printf("%d ",root->mset->left_arr[i]);
            
        }
         printf("\nMiddle CONTENTS :\n");
         for(i=0;i<root->mset->middle_top;i++)
        {
            printf("%d ",root->mset->middle_arr[i]);
            
        }
         printf("\nright CONTENTS :\n");
         for(i=0;i<root->mset->right_top;i++)
        {
            printf("%d ",root->mset->right_arr[i]);
            
        }
        printf("\n");
        traverse(root->left);
        traverse(root->middle);
        traverse(root->right);

    }    


}

void insert(int mob_no,int station_id,station *root)
{
    station *ptr;
    ptr=root;

    while(ptr != NULL)
    {
        if(station_id < ptr->index_low)
        {
            insert_array(mob_no,ptr,1);
            ptr = ptr->left;
        }
        else if(station_id > ptr->index_high)
        {   
             insert_array(mob_no,ptr,2);
            ptr = ptr->right;
        }
        else
        {   
             insert_array(mob_no,ptr,3);
            ptr = ptr->middle;
        }
        
    }





}

void insert_array(int mobile_num,station *ptr,int action)
{
    mobile_set *mptr;
    mptr = ptr->mset;
    int i,j;
    

    if(action == 1)
    {

        j=mptr->left_top;

        while(j>0&&mptr->left_arr[j-1]>mobile_num)
        {
            mptr->left_arr[j]=mptr->left_arr[j-1];

            j--;
        }

        mptr->left_arr[j] = mobile_num;
        mptr->left_top += 1;

    }
    else if(action == 3)
    {   
        
        j=mptr->middle_top;

        while(j>0&&mptr->middle_arr[j-1]>mobile_num)
        {
            mptr->middle_arr[j]=mptr->middle_arr[j-1];

            j--;
        }

        mptr->middle_arr[j] = mobile_num;
        mptr->middle_top++;




    }
    else
    {
        
        j=mptr->right_top;

        while(j>0&&mptr->right_arr[j-1]>mobile_num)
        {
            mptr->right_arr[j]=mptr->right_arr[j-1];

            j--;
        }

        mptr->right_arr[j] = mobile_num;
        mptr->right_top++;

    
    }
    

}

station* search(int mob_no,station *root)
{
    station *prev,*ptr = root;
    int found_left=0;
     int found_right=0;
      int found_middle=0;
    
    while(ptr != NULL)
    {   
        prev = ptr;
        found_left=0;
        found_right=0;
        found_middle=0;
        
    

        if(search_arr(mob_no,ptr,1)>=0)
        {
            found_left = 1;
        }

        if(search_arr(mob_no,ptr,2)>=0)
        {
            found_middle = 1;
        }

        if(search_arr(mob_no,ptr,3)>=0)
        {
            found_right = 1;
        }
        
        if(found_left)
        {
            ptr = ptr->left;
        }
        
         else if(found_middle)
        {
            ptr = ptr->middle;
        }
        
         else if(found_right)
        {
            ptr = ptr->right;
        }
        else
        {   
            prev = NULL;
            break;
        }
        
        

    }

    

    return prev;


}

int search_arr(int mob_no,station *ptr,int action)
{
    int low,mid,high,index=-1,found=0,retval;
    mobile_set *mptr;

    mptr = ptr->mset;

    low=0;

    if(action == 1)
    {

        high=mptr->left_top;
        int i;

        retval = binarySearch(mptr->left_arr,0,high-1,mob_no);


        

    }
    else if(action == 2)
    {

        high=mptr->middle_top;

          int i;

         retval = binarySearch(mptr->middle_arr,0,high-1,mob_no);

    }

    else
    {

        high=mptr->right_top;

          int i;

         retval = binarySearch(mptr->right_arr,0,high-1,mob_no);
        

    }



    

    return retval;


}

station* delete(int mob_no,station *root)
{
     station *prev,*ptr = root;
    int found_left=0;
     int found_right=0;
      int found_middle=0;
      int index;
    
    while(ptr != NULL)
    {   
        prev = ptr;
        found_left=0;
        found_right=0;
        found_middle=0;
        
    

        if(search_arr(mob_no,ptr,1)>=0)
        {
            found_left = 1;
            index=search_arr(mob_no,ptr,1);
            delete_arr(mob_no,ptr,index,1);
        }

        if(search_arr(mob_no,ptr,2)>=0)
        {
            found_middle = 1;
            index=search_arr(mob_no,ptr,2);
            delete_arr(mob_no,ptr,index,2);
        }

        if(search_arr(mob_no,ptr,3)>=0)
        {
            found_right = 1;
             index=search_arr(mob_no,ptr,3);
            delete_arr(mob_no,ptr,index,3);
        }
        
        if(found_left)
        {
            ptr = ptr->left;
        }
        
         else if(found_middle)
        {
            ptr = ptr->middle;
        }
        
         else if(found_right)
        {
            ptr = ptr->right;
        }
        else
        {   
            prev = NULL;
            break;
        }
        
        

    }

    

    return prev;



}

void delete_arr(int mob_no,station *ptr,int index,int action)
{

    int i;
    mobile_set *mptr = ptr->mset;

    if(action == 1)
    {


            for(i=index;i<mptr->left_top-1;i++)
            {
                mptr->left_arr[i] = mptr->left_arr[i+1];
            }

            mptr->left_top--;
    
        


    }
    else if(action == 2)
    {
        
            for(i=index;i<mptr->middle_top-1;i++)
            {
                mptr->middle_arr[i] = mptr->middle_arr[i+1];
            }

            mptr->middle_top--;
    }
    else
    {  

            for(i=index;i<mptr->right_top-1;i++)
            {
                mptr->right_arr[i] = mptr->right_arr[i+1];
            }

            mptr->right_top--;
    


    }

    
    
}


station* getstationbyid(int id,station *root)
{
    station *ptr;

    ptr = root;

    while(ptr != NULL && ptr->index_low != id)
    {
        if(id < ptr->index_low)
        {
            ptr= ptr->left;
        }
        else if(id > ptr->index_high)
        {
            ptr = ptr->right;
        }
        else 
        {
            ptr = ptr->middle;
        }
        


    }


    return ptr;

}

int isempty(int id,station *root)
{
    station *ptr;
    mobile_set *mptr;
    int retval;

    ptr = getstationbyid(id,root);

    if(ptr != NULL)
    {

        mptr = ptr->mset;

        if(mptr->left_top == 0 && mptr->middle_top == 0 && mptr->right_top == 0)
        {
            retval = 1;
        }
        else
        {
            retval = 0;
        }
    }    
    else
    {
        retval = -1;
    }
    
    
    return retval;
}


int ismember(int id,int mob_no,station *root)
{
    station *ptr;
    mobile_set *mptr;
    int index_left,index_middle,index_right,retval;
    ptr = getstationbyid(id,root);

    mptr = ptr->mset;

    if(ptr != NULL)
    {
       index_left = search_arr(mob_no,ptr,1);
        index_middle = search_arr(mob_no,ptr,2);
         index_right = search_arr(mob_no,ptr,3);

        if(index_left >=0 || index_middle >=0 ||index_right >=0)
        {
            retval =1;
        }
        else
        {
            retval =0;
        }
        

    }    
    else
    {
        retval = -1;
    }
    
    return retval;
}

void getmobileset(int id,station *root)
{
    station *ptr;
    mobile_set *mptr;
    int i;

    ptr = getstationbyid(id,root);

    if(ptr != NULL)
    {
            mptr = ptr->mset;

                printf("\n");

            if(!isempty(ptr->index_low,root))
            {

            for(i = 0 ; i<mptr->left_top;i++ )
            {
                printf("%d ",mptr->left_arr[i]);

            }

                printf("\n");

            for(i = 0 ; i<mptr->middle_top;i++ )
            {
                printf("%d ",mptr->middle_arr[i]);

            }
                printf("\n");


            for(i = 0 ; i<mptr->right_top;i++ )
            {
                printf("%d ",mptr->right_arr[i]);

            }
        }
        else
        {
            printf("\n EMPTY SET \n");
        }
        
             printf("\n");

         
        
    }
    else
    {
      printf("\nNOT VALID ID\n");  
    }
    
}

int findphone(int mob_no,station *root)
{
    station *ptr;
    int retval;

    ptr = search(mob_no,root);

    if(ptr != NULL)
    {
        retval = ptr->index_low;

    }
    else
    {
        retval = -1;
    }
    

    return retval;

}
int movephone(int mob_no,int id,station *root)
{   
    station *ptr;
    int retval;
    ptr=delete(mob_no,root);

    if(ptr != NULL)
    {
        insert(mob_no,id,root);
        retval =1;
    }
    else
    {
        retval =0;
    }

    return retval;

}

station* getlowestrouter(int base_1,int base_2,station *root)
{
        station *ptr;
        int found = 0;
        ptr =root;

      

    while(!found && ptr!=NULL)    
    {   

    
        if(base_1 < ptr->index_low && base_2 < ptr->index_low)
        {
            ptr=ptr->left;
            
        }
        else
        {
            if(base_1 > ptr->index_high && base_2 > ptr->index_high)
            {

                ptr = ptr->right;
            }
            else
            {
                if(base_1 > ptr->index_low && base_2 < ptr->index_high)
                {
                    ptr=ptr->middle;
                }else
                {
                    found =1;
                }
                
            }
            
        }
        


            
    
        
    }     

    return ptr;

}

void getexchangelist(int mob_no_1,int mob_no_2,station *root)
{
    station *ptr_1,*ptr_2,*lowest_router,*ptr;
    int base_1,base_2,id;
    int arr_to[4];
    int arr_from[4];
    int size_to = 0;
    int size_from = 0;
    int i;

    ptr_1 = search(mob_no_1,root);
    ptr_2 = search(mob_no_2,root);

    base_1 = ptr_1->index_low;
    base_2 = ptr_2->index_low;

    lowest_router = getlowestrouter(base_1,base_2,root);

    if(lowest_router == NULL)
    {
        printf("\n%d \n",base_1);
    }
    else{

    ptr = lowest_router;

    

    id = base_1;


    while(ptr != NULL && ptr->index_low != id)
    {
        if(id < ptr->index_low)
        {
            ptr= ptr->left;
        }
        else if(id > ptr->index_high)
        {
            ptr = ptr->right;
        }
        else 
        {
            ptr = ptr->middle;
        }

        arr_from[size_from] = ptr->index_low;
        size_from++;      
    }


    
    ptr = lowest_router;

    

    id = base_2;


    while(ptr != NULL && ptr->index_low != id)
    {
        if(id < ptr->index_low)
        {
            ptr= ptr->left;
        }
        else if(id > ptr->index_high)
        {
            ptr = ptr->right;
        }
        else 
        {
            ptr = ptr->middle;
        }

        arr_to[size_to] = ptr->index_low;
        size_to++;      
    }


    for(i=size_from-1; i>=0;i--)
    {
        printf("%d ",arr_from[i]);
    }

     printf("%d ",lowest_router->index_low);

    for(i=0;i<size_to;i++)
    {
        printf("%d ",arr_to[i]);
    }


    }

}


int binarySearch(int arr[], int l, int r, int x) 
{ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
        if (arr[m] == x) 
            return m; 
  
        if (arr[m] < x) 
            l = m + 1; 
  
        else
            r = m - 1; 
    } 
  
    return -1; 
} 






/////////////////////////////////////


void printLevelOrder(station* root) 
{   

    int h = height(root); 
    int i; 
    for (i=1; i<=h; i++) 
        printGivenLevel(root, i); 
} 
  
void printroutingstructure(station *root)
{

    int i;

    for(i=1;i<=4;i++)
    {   
        printf("\nstation level %d \n\n",i);
        printGivenLevel(root,i);

        printf("\n");

    }

}



void printGivenLevel(station* root, int level) 
{   int i;
    if (root == NULL) 
        return; 
    if (level == 1) 
    {   
        printf("\n %d \n",root->index_low);
        
        for(i=0;i<root->mset->left_top;i++)
        {
            printf("%d ",root->mset->left_arr[i]);
        }
         for(i=0;i<root->mset->middle_top;i++)
        {
            printf("%d ",root->mset->middle_arr[i]);
        }
        for(i=0;i<root->mset->right_top;i++)
        {
            printf("%d ",root->mset->right_arr[i]);
        }

    }





    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->middle, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 
  

int height(station *root) 
{   
    int max;

    if (root==NULL) 
        return 0; 
    else
    { 
        
        int lheight = height(root->left); 
        int mheight = height(root->middle);
        int rheight = height(root->right); 
  
        /* use the larger one */
         max = maximum(lheight,mheight,rheight);
    } 

    return max;
} 

int maximum(int a,int b,int c)
{   
    int max;
    if(a>=b && a>=c)
    {
        max=a;
    }
    else if(b>=a && b>=c)
    {
        max=b;
    }
    else
    {
        max = c;
    }
    
    return max;

}



void initialize_queue(queue *qptr)
{
    qptr->front=0;
    qptr->rear=0;
}



void insertque(station *nod,queue *qptr)
{
    qptr->node[qptr->rear] = nod;
    qptr->rear++;
}

station* deleteque(queue *qptr)
{
    station *ptr;
    ptr = qptr->node[qptr->front];
    qptr->front++;

    if(qptr->front == qptr->rear)
    {
        qptr->front = 0;
        qptr->rear = 0;
    }

    return ptr;

}

void showqueue(queue *qptr)
{
    int i;

    for(i=qptr->front;i<qptr->rear;i++)
    {
        printf("%d ",qptr->node[i]->index_low);
    }


}

int isqueempty(queue *qptr)
{

    int retval =0;

    if(qptr->front == 0 && qptr->rear == 0)
    {
        retval = 1;
    }

    return retval;
}


station *insertlevelorder(station *root,queue *qptr,int index_low,int index_high,int size)
{   
    station *ptr;

    if(root == NULL)
    {
        root = makestation(index_low,index_high,size);
    }

    else
    {
        insertque(root,qptr);

        while(!isqueempty(qptr))
        {
            ptr = deleteque(qptr);

            if(ptr->left == NULL)
            {
                ptr->left = makestation(index_low,index_high,size);
                initialize_queue(qptr);
                break;
            }
            else
            {
                insertque(ptr->left,qptr);
            }
            
            if(ptr->middle == NULL)
            {
                ptr->middle = makestation(index_low,index_high,size);
                initialize_queue(qptr);
                break;
            }
            else
            {
                insertque(ptr->middle,qptr);
            }
            
            if(ptr->right == NULL)
            {
                ptr->right = makestation(index_low,index_high,size);
                initialize_queue(qptr);
                break;
            }
            else
            {
                insertque(ptr->right,qptr);
            }


        }

    }


    return root;

}


