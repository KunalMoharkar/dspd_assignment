#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEAM_SIZE 15
#define NO_OF_PLAYING_TEAMS 2


struct player{


  int player_id;
  int previous_total_score;
  int previous_avg;
  int previous_total_wickets;
  int previous_wicket_avg;
  int century;
  int previous_total_centuries;
  int present_match_score;
  int present_match_wicket;
  char player_role;
  char player_name[10];

};

struct team{

struct player p[TEAM_SIZE];

};

struct match_played{


int match_id;

struct teams_played{

 int playing_team_id[NO_OF_PLAYING_TEAMS];
 struct team playing_team[NO_OF_PLAYING_TEAMS];


}tp;

int highest_run;
int wickets_taken_by_pacer;
int man_of_the_match;
char match_result;

};

struct container    //structure for solving
{
    int id;
    int id_count;
    char name[10];

};

struct container_1 //structure for solving
{

    int id;
    int century;
    char name[10];


};

int check_1[100];
int check_2[100];      //globals for check equal
int check_1_size=0;
int check_2_size=0;



void initialize_match_stats(struct match_played mp[],int size);
void initialize_player_stats(struct team tm[],int size);
void insert_player_data(struct team tm[],int size);
void insert_data(struct match_played mp[],struct team tm[],int size_1,int size_2);
void display_team_stats(struct team tm[],int size);
void display_match_stats(struct match_played mp[],int size);
void calculate_highest_average(struct team tm[],int size);
void difference_in_wickets(struct match_played mp[],struct team tm[],int size_1,int size_2);
void print_sorted_output(struct container p[],int size);
void man_of_the_match_array_create(struct match_played mp[],struct team tm[],int size);
void man_of_the_match_array_create_1(struct container p[],struct team tm[],int size);
void calculate_highest_individual_run_getter(struct match_played mp[],struct team tm[],int size_1,int size_2);
void check_is_equal();
void player_combinations(struct team t[],int size);

int main()
{
   int n,i,j,k,a;
   printf("ENTER NO. OF TEAMS \n");
   scanf("%d",&n);

   struct team tm[n];
   int sz=(n/2)*((n)/2-1)+3;
   struct match_played mp[sz];



  initialize_match_stats(mp,sz);
  initialize_player_stats(tm,n);

  insert_player_data(tm,n);
  insert_data(mp,tm,sz,n);

  display_team_stats(tm,n);
  display_match_stats(mp,sz);

  calculate_highest_individual_run_getter(mp,tm,sz,n);

  calculate_highest_average(tm,n);
  difference_in_wickets(mp,tm,sz,n);

   man_of_the_match_array_create(mp,tm,sz);

   check_is_equal();
   player_combinations(tm,n);



}



void initialize_match_stats(struct match_played mp[],int size)
{
    int i,k,j;

           for(i=0;i<size;i++)
           {

           mp[i].match_id=0;
           mp[i].highest_run=0;
           mp[i].wickets_taken_by_pacer=0;
           mp[i].man_of_the_match=0;
           mp[i].match_result='\0';

                for(k=0;k<NO_OF_PLAYING_TEAMS;k++)
                {

                   for(j=0;j<TEAM_SIZE;j++)
                   {
                        mp[i].tp.playing_team[k].p[j].player_id=0;
                        mp[i].tp.playing_team[k].p[j].present_match_score=0;
                        mp[i].tp.playing_team[k].p[j].present_match_wicket=0;
                        mp[i].tp.playing_team[k].p[j].player_role='\0';
                        mp[i].tp.playing_team[k].p[j].player_name[0]='\0';
                   }





                }


           }



}

void initialize_player_stats(struct team tm[],int size)
{

       int i,j,id=0;

             for(i=0;i<size;i++)
             {

                for(j=0;j<TEAM_SIZE;j++)
                {
                   tm[i].p[j].player_id=id;
                   tm[i].p[j].previous_total_score=0;
                   tm[i].p[j].previous_avg=0;
                   tm[i].p[j].previous_total_wickets=0;
                   tm[i].p[j].previous_wicket_avg=0;
                   tm[i].p[j].century=0;
                   tm[i].p[j].previous_total_centuries=0;
                   tm[i].p[j].present_match_score=0;
                   tm[i].p[j].present_match_wicket=0;
                   tm[i].p[j].player_role='\0';
                   tm[i].p[j].player_name[0]='\0';

                   id++;
                }




             }



}

void insert_player_data(struct team tm[],int size)
{

    int i,j;


    for(i=0;i<size;i++)
    {

        for(j=0;j<TEAM_SIZE;j++)

        {

            printf("DETAILS OF PLAYER ID:%d\n",tm[i].p[j].player_id);

            printf("TOURNAMENT AVERAGE\n");
            scanf("%d",&tm[i].p[j].previous_avg);

            printf("no. of centuaries \n");
            scanf("%d",&tm[i].p[j].century);

            printf("player role\n");

            scanf(" %c",&tm[i].p[j].player_role);

            printf("player_name\n");

            scanf(" %s",&tm[i].p[j].player_name);


        }

    }










}

void insert_data(struct match_played mp[],struct team tm[],int size_1,int size_2)
{
    int i,j,k,a;



   for(i=0;i<size_1;i++)
   {
       printf("ENTER DETAILS OF MATCH %d \n",i+1);
       printf("MATCH_ID\n");
       scanf("%d",&mp[i].match_id);
       printf("TEAMS_PLAYED\n");

       for(k=0;k<NO_OF_PLAYING_TEAMS;k++)
       {

       printf("TEAM%d_id\n",k+1);
       scanf("%d",&mp[i].tp.playing_team_id[k]);

       a=mp[i].tp.playing_team_id[k];


       printf("ENTER PLAYER DETAILS\n\n");

       for(j=0;j<TEAM_SIZE;j++)
       {
         printf("player_id:%d\n",tm[a-1].p[j].player_id);


        printf("present match score\n");
        scanf("%d",&tm[a-1].p[j].present_match_score);

         printf("present match wickets\n");
        scanf("%d",&tm[a-1].p[j].present_match_wicket);



            mp[i].tp.playing_team[k].p[j].player_id=tm[a-1].p[j].player_id;
            mp[i].tp.playing_team[k].p[j].present_match_score=tm[a-1].p[j].present_match_score;
            tm[a-1].p[j].previous_total_score += tm[a-1].p[j].present_match_score;
            mp[i].tp.playing_team[k].p[j].present_match_wicket=tm[a-1].p[j].present_match_wicket;
            tm[a-1].p[j].previous_total_wickets += tm[a-1].p[j].present_match_wicket;
            mp[i].tp.playing_team[k].p[j].player_role=tm[a-1].p[j].player_role;
            strcpy(mp[i].tp.playing_team[k].p[j].player_name,tm[a-1].p[j].player_name);


       }


       }


        printf("HIGHEST_RUNS\n");
        scanf("%d",&mp[i].highest_run);

        printf("WICKET TAKEN BY PACERS\n");
        scanf("%d",&mp[i].wickets_taken_by_pacer);

        printf("MATCH RESULT\n");
        scanf(" %c",&mp[i].match_result);

        printf("MAN OF THE MATCH\n");
        scanf("%d",&mp[i].man_of_the_match);



   }






}

void display_team_stats(struct team tm[],int size)
{
    int i,j;

   for(i=0;i<size;i++)
   {

       printf("DETAILS OF TEAM %d \n\n",i+1);


         for(j=0;j<TEAM_SIZE;j++)

         {
             printf("player_id : %d\n",tm[i].p[j].player_id);
             printf("previous total score: %d\n",tm[i].p[j].previous_total_score);
             printf("previous total wickets: %d\n",tm[i].p[j].previous_total_wickets);
             printf("previous average: %d\n",tm[i].p[j].previous_avg);
             printf("total centuries: %d\n",tm[i].p[j].century);
             printf("player role: %c\n",tm[i].p[j].player_role);
             printf("player name: %s\n",tm[i].p[j].player_name);

         }

      printf("\n\n");


   }



}



void display_match_stats(struct match_played mp[],int size)
{
    int i,j,k;

    for(i=0;i<size;i++)
   {
       printf("STATS OF MATCH %d\n\n",i+1);

       for(k=0;k<NO_OF_PLAYING_TEAMS;k++)
       {
          printf("STATS OF TEAM %d\n",mp[i].tp.playing_team_id[k]);

               for(j=0;j<TEAM_SIZE;j++)
               {

                  printf("player id :%d\n", mp[i].tp.playing_team[k].p[j].player_id);
                  printf("present score :%d\n",mp[i].tp.playing_team[k].p[j].present_match_score);
                  printf("present wickets :%d\n",mp[i].tp.playing_team[k].p[j].present_match_wicket);
                  printf("player role : %c \n",mp[i].tp.playing_team[k].p[j].player_role);
                  printf("player name : %s \n",mp[i].tp.playing_team[k].p[j].player_name);
                  printf("\n\n\n\n");

               }

        }


     }



}


void calculate_highest_average(struct team tm[],int size)
{

    int i,j,maxavg=0,id;

    for(i=0;i<size;i++)
    {

        for(j=0;j<TEAM_SIZE;j++)
        {
           if(tm[i].p[j].previous_avg>=maxavg)
           {
             maxavg=tm[i].p[j].previous_avg;
             id=tm[i].p[j].player_id;
           }


        }



    }


    printf("\n\nINDIVIDUAL HAVING HIGHEST AVERAGE IS PLAYER ID:%d AND AVERAGE IS %d\n\n",id,maxavg);



}


void difference_in_wickets(struct match_played mp[],struct team tm[],int size_1,int size_2)
{
   int i,j;
   int total_wickets_taken_by_pacers=0,total_wickets=0,wickets_difference;


       for(i=0;i<size_1;i++)
       {
           total_wickets_taken_by_pacers += mp[i].wickets_taken_by_pacer;

       }

       for(i=0;i<size_2;i++)
       {

           for(j=0;j<TEAM_SIZE;j++)
           {
               total_wickets+=tm[i].p[j].previous_total_wickets;
           }

       }


    wickets_difference=2*total_wickets_taken_by_pacers-total_wickets;


    printf("DIFFERENCE IN WICKETS TAKEN BY PACERS AND SPINNERS IS %d \n\n",wickets_difference);


}





void man_of_the_match_array_create(struct match_played mp[],struct team tm[],int size)
{
    int i,j,id_size,k=1,flag,team_pos,player_pos;
    struct container man_of_match[size];

    for(i=0;i<size;i++)
    {
        man_of_match[i].id_count=0;
    }



        man_of_match[0].id=mp[0].man_of_the_match;
        team_pos=man_of_match[0].id/TEAM_SIZE;
        player_pos=man_of_match[0].id%TEAM_SIZE;
        strcpy(man_of_match[0].name,tm[team_pos].p[player_pos].player_name);
        man_of_match[0].id_count++;

    for(i=1;i<size;i++)
    {

        flag=0;

        for(j=0;j<k;j++)
        {
            if(man_of_match[j].id==mp[i].man_of_the_match)
            {
               man_of_match[j].id_count++;
               flag=1;
            }

        }


        if(flag==0)
        {

            man_of_match[k].id=mp[i].man_of_the_match;
            team_pos=man_of_match[k].id/TEAM_SIZE;
            player_pos=man_of_match[k].id%TEAM_SIZE;
            strcpy(man_of_match[k].name,tm[team_pos].p[player_pos].player_name);
            man_of_match[k].id_count++;
            k++;

        }



    }



  print_sorted_output(man_of_match,k);

  man_of_the_match_array_create_1(man_of_match,tm,k);

}


void print_sorted_output(struct container p[],int size)
{

    int i,flag=1,k=0,maxcount;

     maxcount=p[0].id_count;

     for(i=0;i<size;i++)
     {
         if(p[i].id_count>maxcount)
         {
            maxcount=p[i].id_count;
         }

     }




     while(flag!=0)
     {


       int max=p[0].id_count;
       int maxpos=0;

       for(i=0;i<size;i++)
       {
               if(p[i].id_count>max)
               {
                   max=p[i].id_count;
                   maxpos=i;
               }

               else if(p[i].id_count==max)
               {

                       if(strcmp(p[i].name,p[maxpos].name)<0)
                       {
                           maxpos=i;
                       }

               }


        }


        if(p[maxpos].id_count==maxcount)
        {
           printf("%d \n",p[maxpos].id);
        }
        else
        {
            flag=0;
        }

        p[maxpos].id_count=-1;

   }


}

void man_of_the_match_array_create_1(struct container p[],struct team tm[],int size)
{
    int i,j,k,index=0;
    struct container_1 q[size];

    printf("ENTER THE VALUE OF K \n");
    scanf("%d",&k);

    for(i=0;i<size;i++)
    {
        if(p[i].id_count>=k)
        {
            q[index].id=p[i].id;
            q[index].century=tm[p[i].id/TEAM_SIZE].p[p[i].id%TEAM_SIZE].century;
            strcpy(q[index].name,p[i].name);

            index++;
        }


    }

  print_sorted_output(q,index);

}

void calculate_highest_individual_run_getter(struct match_played mp[],struct team tm[],int size_1,int size_2)
{

    int i,j,k,pos;
    int runs[TEAM_SIZE*size_2];

    for(i=0;i<TEAM_SIZE*size_2;i++)
    {

        runs[i]=0;
    }

    for(i=0;i<size_1-3;i++)
    {
        for(k=0;k<NO_OF_PLAYING_TEAMS;k++)
        {


                for(j=0;j<TEAM_SIZE;j++)
                {

                     pos=mp[i].tp.playing_team[k].p[j].player_id;
                     runs[pos]+=mp[i].tp.playing_team[k].p[j].present_match_score;

                }


        }



    }


    int maxruns=runs[0],maxpos=0,flag=1,team_pos,player_pos,max;


    for(i=0;i<size_2*TEAM_SIZE;i++)
    {

        if(runs[i]>maxruns)
        {
            maxruns=runs[i];

        }

    }



    while(flag!=0)
    {

       max=runs[0];
       maxpos=0;



    for(i=0;i<size_2*TEAM_SIZE;i++)
    {

      if(runs[i]>max)
      {

          max=runs[i];
          maxpos=i;

      }

       else if(runs[i]==max)
       {
           team_pos=i/TEAM_SIZE;
           player_pos=i%TEAM_SIZE;

           if(tm[team_pos].p[player_pos].previous_total_score>tm[maxpos/TEAM_SIZE].p[maxpos%TEAM_SIZE].previous_total_score)
           {

               maxpos=i;
           }

           else if(tm[team_pos].p[player_pos].previous_total_score==tm[maxpos/TEAM_SIZE].p[maxpos%TEAM_SIZE].previous_total_score)
           {

                 team_pos=i/TEAM_SIZE;
                 player_pos=i%TEAM_SIZE;




               if((strcmp(tm[team_pos].p[player_pos].player_name,tm[maxpos/TEAM_SIZE].p[maxpos%TEAM_SIZE].player_name)<0))
               {
                  maxpos=i;

               }

           }

       }


    }




      if(runs[maxpos]==maxruns)
        {
           printf("%d \n",maxpos);
        }
        else
        {
            flag=0;
        }

        runs[maxpos]=-1;


    }









}


void player_combinations(struct team t[],int size)
{



        int batsman_size;
        int batsman[TEAM_SIZE];
        int bowler_size;
        int bowler[TEAM_SIZE];
        int allrounder_size;
        int allrounder[TEAM_SIZE];




    int i,j,k,m=0,player_pos,l;
    int bat[2],bowl[2],arr[11];







    for(i=0;i<size;i++)                //classify all players
    {
        batsman_size=0;
        bowler_size=0;
        allrounder_size=0;
         m=0;

        for(j=0;j<TEAM_SIZE;j++)
        {
               if(t[i].p[j].player_role=='B')
               {

                   batsman[batsman_size]=t[i].p[j].player_id;
                   batsman_size++;
               }

                else if(t[i].p[j].player_role=='b')
                {
                    bowler[bowler_size]=t[i].p[j].player_id;
                    bowler_size++;

                }
                else
                {
                    allrounder[allrounder_size]=t[i].p[j].player_id;
                    allrounder_size++;
                }

        }


          while(m<2)
          {
                 int max=-1,maxpos=0;

                 for(k=0;k<batsman_size;k++)
                 {
                     player_pos=batsman[k]%TEAM_SIZE;

                        if(t[i].p[player_pos].previous_total_score>max)
                        {
                            max=t[i].p[player_pos].previous_total_score;
                            maxpos=batsman[k];
                        }
                        else if(t[i].p[player_pos].previous_total_score==max)
                        {
                                    if(t[i].p[player_pos].previous_avg>t[i].p[maxpos%TEAM_SIZE].previous_avg)
                                    {
                                        maxpos=batsman[k];

                                    }

                        }



                }

                      bat[m]=maxpos;
                      t[i].p[maxpos%TEAM_SIZE].previous_total_score=-1;

    //for bowlers

                    max=-1,maxpos=0;

                 for(k=0;k<bowler_size;k++)
                 {
                     player_pos=bowler[k]%TEAM_SIZE;

                        if(t[i].p[player_pos].previous_total_wickets>max)
                        {
                            max=t[i].p[player_pos].previous_total_wickets;
                            maxpos=bowler[k];
                        }
                        else if(t[i].p[player_pos].previous_total_wickets==max)
                        {
                                    if(t[i].p[player_pos].previous_avg>t[i].p[maxpos%TEAM_SIZE].previous_avg)
                                    {
                                        maxpos=bowler[k];
                                    }

                        }



                    }

                      bowl[m]=maxpos;
                      t[i].p[maxpos%TEAM_SIZE].previous_total_wickets=-1;
                      m++;


                }

                 //regroup back all players

                  k=0;
                  for(l=0;l<batsman_size;l++)
                  {


                      if(batsman[l]!=bat[0]&&batsman[l]!=bat[1])
                       {
                           arr[k]=batsman[l];
                           k++;
                       }


                  }

                  for(l=0;l<bowler_size;l++)
                  {


                      if(bowler[l]!=bowl[0]&&bowler[l]!=bowl[1])
                       {
                           arr[k]=bowler[l];
                           k++;
                       }


                  }

                   for(l=0;l<allrounder_size;l++)
                  {
                           arr[k]=allrounder[l];
                           k++;

                  }


                  int a,b,c,d,e,f,g;

                  printf("%d %d %d %d",bat[0],bat[1],bowl[0],bowl[1]);
                  printf("\n");


            for(a=0;a<=4;a++)   //printing permutations
            {


                for(b=a+1;b<=5;b++)
                {

                  for(c=b+1;c<=6;c++)
                  {

                      for(d=c+1;d<=7;d++)
                      {

                          for(e=d+1;e<=8;e++)
                          {

                              for(f=e+1;f<=9;f++)
                              {
                                  for(g=f+1;g<=10;g++)
                                  {

                                      printf("%d %d %d %d",bat[0],bat[1],bowl[0],bowl[1]);
                                      printf("\n");
                                      printf("%d %d %d %d %d %d %d",arr[a],arr[b],arr[c],arr[d],arr[e],arr[f],arr[g]);
                                      printf("\n\n");
                                  }


                              }



                          }




                      }



                  }


               }

            }









       printf("-----------------------------------------------------------------------------/n/n/n");










        }










}

void check_is_equal()
{
    int i,flag=1;

    if(check_1_size==check_2_size)
    {

            for(i=0;i<check_1_size;i++)
            {
                if(check_1[i]!=check_2[i])
                {
                    flag=0;
                }

            }

    }
    else
        {
           flag=0;
        }


    if(flag==1)
    {
        printf("THE RESULTS ARE EQUAL \n\n");
    }
    else
    {
        printf("THE RESULTS ARE NOT EQUAL\n\n");
    }


}


