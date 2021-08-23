#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

using namespace std ;

typedef struct alarm{
    int second ;
    char message[64] ;

}alarmType;

void *alarmThread(void *arg)
{
    alarmType *palarm = (alarmType*)arg ;

    int status = pthread_detach(pthread_self()) ;

    if(status != 0)
    {
        cout<<"detach failed"<<endl ;
        return NULL ;
    }

    sleep(palarm->second) ;
    cout<<palarm->second<<" "<<palarm->message<<endl ;

    free(palarm);

    return NULL ;
}


int main()
{
    int status = 0 ;
    alarmType *palarm ;
    pthread_t thread ;

    while(1)
    {
        cout<<"Alarm::>>" ;
        palarm = (alarmType*)malloc(sizeof(alarmType)) ;
        if(NULL == palarm)
        {
            cout<<"malloc error"<<endl ;
            continue ;
        }
        cin>>palarm->second ;
        cin>>palarm->message ;

        if(0 == palarm->second || 0 == strcmp("quit",palarm->message))
        {
            cout<<"quit"<<endl ;
            return 0;
        }

        if(0 == strlen(palarm->message))
        {
            cout<<"please input something"<<endl ;
            continue ;
        }
        else
        {
            status = pthread_create(&thread,NULL,alarmThread,palarm);
            if(0 != status)
            {
                cout<<"create thread error"<<endl ;
                continue ;
            }
        }


    }
    return 0 ;
}
