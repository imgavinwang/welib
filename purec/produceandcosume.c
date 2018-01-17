#include <stdio.h>
#include <pthread.h>
#include <iostream>

using namespace std;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t event = PTHREAD_COND_INITIALIZER;

int num = 0;
int countP = 0;

bool flag=false;

void *produce(void *p)
{
    int count = 0;
    while(!flag) 
    {
        pthread_mutex_lock(&lock);
        while(num==100)
        {
            cout<<"producer num==100"<<endl;
            pthread_cond_wait(&event,&lock);
        }

        bool empty = false;
        if(num==0)
        {
            empty=true;
            num++;
            cout<<"producer num==0"<<endl;
            pthread_cond_broadcast(&event);
        }
        if(!empty)
            num++;
        pthread_mutex_unlock(&lock);
        count++;
    }
    return (void*)count;
}

void *cosume(void *p)
{
    int count = 0;
    while(!flag)
    {
        pthread_mutex_lock(&lock);
        while(num==0)
        { 
            pthread_cond_wait(&event, &lock);
        }
        countP++;
        if(countP==1000)
            flag = true;
        bool full = false;
        if(num==100)
        {
            full = true;
            num--;
            pthread_cond_broadcast(&event);
        }
        if(!full)
            num--;
        pthread_mutex_unlock(&lock);
        count++;
    }
    return (void*)count;
}

int main()
{
    pthread_t tid[4];
    pthread_create(tid+0, NULL, produce, NULL);
    //sleep(1);
    pthread_create(tid+1, NULL, produce, NULL);
    //sleep(1);
    pthread_create(tid+2, NULL, cosume, NULL);
    pthread_create(tid+3, NULL, cosume, NULL);
    
    int countP;
    int countM;
    pthread_join(tid[0], (void**)&countM);
    cout<<"producer 0 "<<" "<<countM<<endl;
    pthread_join(tid[1], (void**)&countM);
    cout<<"producer 1 "<<" "<<countM<<endl;
    pthread_join(tid[2], (void**)&countM);
    cout<<"consumer 0 "<<" "<<countM<<endl;
    pthread_join(tid[3], (void**)&countM);
    cout<<"consumer 1 "<<" "<<countM<<endl;
        

    return 0;
}
