#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEAM_SIZE 5
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
void initialize_match_stats(struct match_played mp[],int size);
void initialize_player_stats(struct team tm[],int size);
void insert_player_data(struct team tm[],int size);
void insert_data(struct match_played mp[],struct team tm[],int size_1,int size_2);
void display_team_stats(struct team tm[],int size);
void display_match_stats(struct match_played mp[],int size);

void calculate_highest_average(struct team tm[],int size);
void difference_in_wickets(struct match_played mp[],struct team tm[],int size_1,int size_2);

int main()
{
   int n,i,j,k,a;
   printf("ENTER NO. OF TEAMS \n");
   scanf("%d",&n);

   struct team tm[n];
   int sz=3;
   struct match_played mp[sz];



  initialize_match_stats(mp,sz);
  initialize_player_stats(tm,n);

  insert_player_data(tm,n);
  insert_data(mp,tm,sz,n);

  display_team_stats(tm,n);
  display_match_stats(mp,sz);

  calculate_highest_average(tm,n);
  difference_in_wickets(mp,tm,sz,n);


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

       int i,j,id=1;

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

    int i,j,maxavg,id;

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









