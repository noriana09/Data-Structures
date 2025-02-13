/***************************************************************
 *
 * file: pss.h
 *
 * @Author  noriana tzatzai csd5016@csd.uoc.gr
 *
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

void DL_Insert(struct Info newI, int z);
void DL_Print(int z);
void SL_Print();
void SL_Insert(struct SubInfo newSub);
void L_Insert(struct Subscription news, int z);
void L_Print(int z);
int L_LookUP(int i,int sId);
void L_Delete(int i,int sId);
int SL_Delete(int sId);

struct SubInfo *L=NULL;
struct Group G[MG];

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void){
  int i;
  for(i=0; i<MG; i++){
	G[i].gId=i;
	G[i].ggsub=NULL;
	G[i].gfirst=NULL;
	G[i].glast=NULL;
  }
    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){
	int i;
	struct Info newI;
	newI.itm=iTM;
	newI.iId=iId;
	for(i=0;i<size_of_gids_arr;i++){
             if(gids_arr[i]<=MG && gids_arr[i]>=0){
		DL_Insert(newI, gids_arr[i]);
		DL_Print(gids_arr[i]);
             }
	}
    return EXIT_SUCCESS;
}

void DL_Insert(struct Info newI, int z){
        struct Info *c;
        struct Info *newn;
	if(G[z].gfirst==NULL){
		G[z].gfirst=(struct Info *)malloc(sizeof(struct Info));
		G[z].gfirst->iId=newI.iId;
		G[z].gfirst->itm=newI.itm;
		G[z].gfirst->inext=NULL;
		G[z].gfirst->iprev=NULL;
		G[z].glast=G[z].gfirst;
	}
	else{
		c=G[z].gfirst;
		while(c->inext!=NULL && c->itm<newI.itm){
			c=c->inext;
		}
		if(c==G[z].gfirst && c->itm>newI.itm){                     /* An exw mono 1 kombo elexxw afton*/
		    newn=(struct Info *)malloc(sizeof(struct Info));
		    newn->iId=newI.iId;
		    newn->itm=newI.itm;
		    newn->inext=c;
		    c->iprev=newn;
		    newn->iprev=NULL;
		    G[z].gfirst=newn;
		    if(newn->inext==NULL) G[z].glast=newn;
		}else{
		    newn=(struct Info *)malloc(sizeof(struct Info));
		    newn->iId=newI.iId;
		    newn->itm=newI.itm;
		    newn->inext=c->inext;
		    if(newn->inext!=NULL) newn->inext->iprev=newn;
		    newn->iprev=c;
		    c->inext=newn;
		    if(newn->inext==NULL) G[z].glast=newn;
	       }
        }
	return ;
}

void  DL_Print(int z){
	int i;
	 struct Info *c;
	 c=G[z].gfirst;
       if(z!=-1){
	 printf("GRUPID=<%d>, INFOLIST=<",z); /* andi gia G[i].gId mporei na mpei kai sketo z afou einai idia*/
	 while(c!=NULL){
	 	printf("%d, ",c->iId);
	 	c=c->inext;
	 }
	 printf(">\n");
      }
     return;
}


/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
        int i;
	struct SubInfo newSub;
	struct Subscription news;
	news.sId=sId;
	newSub.stm=sTM;
	newSub.sId=sId;
	for(i=0;i<MG;i++){
		newSub.sgp[i]=G[i].gfirst;
	}
	for(i=0;i<size_of_gids_arr;i++){
             if(gids_arr[i]>=0 && gids_arr[i]<=MG){
		newSub.sgp[gids_arr[i]]=G[gids_arr[i]].gfirst;   /* vazw to sgp na deixnei sto prwto struct tou group gia to opoio endiaferete*/

             }
	}
	/*for(i=0;i<MG;i++){
		if(newSub.sgp[i]==NULL){
			newSub.sgp[i]=(struct Info*)1;
		}
	}*/
	SL_Insert(newSub);
	SL_Print();
	for(i=0;i<size_of_gids_arr;i++){
             if(gids_arr[i]>=0 && gids_arr[i]<=MG){
		L_Insert(news, gids_arr[i]);
		L_Print(gids_arr[i]);
             }
	}
    return EXIT_SUCCESS;
}


void SL_Insert(struct SubInfo newSub){
	int i;
        struct SubInfo *c;
        struct SubInfo *newn;
        c=L;
	if(L==NULL){
		L=(struct SubInfo *)malloc(sizeof(struct SubInfo));
		L->sId=newSub.sId;
		L->stm=newSub.stm;
		L->snext=NULL;
		for(i=0;i<MG;i++){
			L->sgp[i]=newSub.sgp[i];
		}
	}
	else{
		while(c->snext!=NULL && c->snext->stm<newSub.stm){
			c=c->snext;
		}
		if(c==L && c->stm>newSub.stm){                     /* An exw mono 1 kombo elexxw afton*/
		    newn=(struct SubInfo *)malloc(sizeof(struct SubInfo));
		    newn->sId=newSub.sId;
		    newn->stm=newSub.stm;
		    newn->snext=c;
		    L=newn;
		    for(i=0;i<MG;i++){
			    newn->sgp[i]=newSub.sgp[i];
		   }
		}
		else{
		    newn=(struct SubInfo *)malloc(sizeof(struct SubInfo));
		    newn->sId=newSub.sId;
		    newn->stm=newSub.stm;
		    newn->snext=c->snext;
		    c->snext=newn;
		    for(i=0;i<MG;i++){
			    newn->sgp[i]=newSub.sgp[i];
		   }
	    }
	}
	return;
}


void  SL_Print(){
	 struct SubInfo *c;
	 c=L;
	 printf("SUBSCRIBERLIST=<");
	 while(c!=NULL){
	 	printf("%d, ",c->sId);
	 	c=c->snext;
	 }
	 printf(">\n");
     return;
}



void L_Insert(struct Subscription news, int z){
	int i,k;
     if(z>=0 && z<=MG){
	if(G[z].ggsub==NULL){
		G[z].ggsub=(struct Subscription *)malloc(sizeof(struct Subscription));
		G[z].ggsub->sId=news.sId;
		G[z].ggsub->snext=NULL;
	}
	else{
		struct Subscription *c;
		c=G[z].ggsub;
		k=0;
		while(c->snext!=NULL && k==0){
			if(c->snext->snext==NULL){
				k=1;
				c=c->snext;
			}
			else{
			    c=c->snext;	
			}
		}
		struct Subscription *newn;
		newn=(struct Subscription *)malloc(sizeof(struct Subscription));
		newn->sId=news.sId;
		newn->snext=c->snext;
		c->snext=newn;
	}
     }
	return;
}


void  L_Print(int z){
	 struct Subscription *c;
	 c=G[z].ggsub;
       if(z!=-1){
	 printf("GRUPID=<%d>, SUBLIST=<",G[z].gId);
	 while(c!=NULL){
	 	printf("%d, ",c->sId);
	 	c=c->snext;
	 }
	 printf(">\n");
       }
     return;
}


/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){
    int i,k;
    struct SubInfo *c;
    struct SubInfo *t;
    struct Subscription *s;
    struct Info *p;
    c=L;
    t=NULL;
    p=NULL;
    s=NULL;
    while(c!=NULL){
          if(c->sId==sId)t=c;
          c=c->snext;
    }
    if(t!=NULL){
       for(i=0;i<MG;i++){
           s=G[i].ggsub;
           k=0;
           while(s!=NULL && k==0){
                 if(s->sId==t->sId)k=1;
                 s=s->snext;
           }
         if(k==1){
           p=t->sgp[i];
           if(G[i].gfirst!=NULL && p==NULL) p=G[i].gfirst;
           printf("%d\n",p);
           printf("GROUPID=<%d>, INFOLIST=<",i);
           while(p!=NULL){
                 printf("%d, ",p->iId);
                 if(p->inext==NULL)t->sgp[i]=p;
                 p=p->inext;
           }
           if(t->sgp[i]!=NULL) printf(">, NEWSGP=<%d>\n",t->sgp[i]->iId);
           printf("\n");
        }
       }
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
       int i,k,p;
       p=SL_Delete(sId);
      if(p==1){
	SL_Print();
	for(i=0;i<MG;i++){
		k=L_LookUP(i,sId);
		if(k==1) {
			L_Delete(i,sId);
			L_Print(i);
		}
	}
      }
    return EXIT_SUCCESS;
}

int L_LookUP(int i, int sId){
     struct Subscription *c;
     c=G[i].ggsub;
     while(c!=NULL){
          if(c->sId==sId) return 1;
          c=c->snext;
     }
     return 0;
}

void L_Delete(int i, int sId){
     struct Subscription *c;
     int k;
     c=G[i].ggsub;
     if(G[i].ggsub->sId==sId){
       G[i].ggsub=G[i].ggsub->snext;
     }
     else{
       k=0;
       while(k==0 && c!=NULL){
            if(c->snext->sId==sId){
                struct Subscription *t;
                t=c->snext;
                c->snext=t->snext;
                k=1;
            }
            else{
                c=c->snext;
            }
       }
     }
    return;
}

int SL_Delete(int sId){
     struct SubInfo *c;
     int k;
     c=L;
     if(L->sId==sId){
       L=L->snext;
       return 1;
     }
     else{
       k=0;
       while(k==0 && c!=NULL){
            if(c->snext!=NULL && c->snext->sId==sId){
                struct SubInfo *t;
                t=c->snext;
                c->snext=t->snext;
                k=1;
                return 1;
            }
            else{
                c=c->snext;
            }
       }
     }
    return 0;
}



/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
	int i,k,NO_G=0,NO_S=0;
	struct Info *c;
	struct Subscription *c1;
	struct SubInfo *c2;
	c2=L;
     for(i=0;i<MG;i++){
       	    c=G[i].gfirst;
            c1=G[i].ggsub;
            if(c!=NULL || c1!=NULL){
                NO_G++;
                printf("GROUPID=<%d>, INFOLIST=<",i);
                while(c!=NULL){
                     printf("%d, ",c->iId);
                     c=c->inext;
                }
                printf(">, SUBLIST=<");
                while(c1!=NULL){
                     printf("%d, ",c1->sId);
                     c1=c1->snext;
                }
                printf(">\n\n");
            }
     }
     printf("SUBSCRIBERLIST=<");
     while(c2!=NULL){
	   printf("%d,",c2->sId);
	   c2=c2->snext;
	   NO_S++;
     }
     printf(">\n\n");
	c2=L;
	while(c2!=NULL){
		printf("SUBSCRIBERID=<%d>, GROUPLIST=<",c2->sId);
		for(i=0;i<MG;i++){
			k=L_LookUP(i,c2->sId);
                        if(k==1){
				printf("%d,",G[i].gId);
			}
		}
		printf(">\n");
		c2=c2->snext;
	}
	printf("\nNO_GROUPS=<%d>,NO_SUBSCRIBERS=<%d>\n",NO_G,NO_S);
    return EXIT_SUCCESS;
}
