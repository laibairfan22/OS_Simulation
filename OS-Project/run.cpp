#include <sys/shm.h>
#include <string>
#include <unistd.h>
#include <cstring>

using namespace std;
int main(int argc, char **argv)
{
    int Ramid, Coresid, Diskid;

    Ramid = shmget((key_t)2345, sizeof(int), 0666 | IPC_CREAT);
    Coresid = shmget((key_t)2346, sizeof(int), 0666 | IPC_CREAT);
    Diskid = shmget((key_t)2347, sizeof(int), 0666 | IPC_CREAT);

    int* ram = (int *)shmat(Ramid, NULL, 0);
    int* cores = (int *)shmat(Coresid, NULL, 0);
    int* disk = (int *)shmat(Diskid, NULL, 0);
    
    if(argc != 0)
    {
        *cores = atoi(argv[1]);
        *ram = atoi(argv[2]);
        *disk = atoi(argv[3]); 
    }
    else
    {
        *cores = 4;
        *ram = 8;
        *disk = 256; 
    }
   
    return 0;
}
