#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sys/shm.h>
#include <pthread.h>
#include <stdlib.h>
#include <algorithm>
#include <semaphore.h>
#include <signal.h>
#include <fstream>
#include <queue>

using namespace std;

struct dict
{
    string key;
    string value;
};

class prg_info
{
public:
    string name;
    int req_ram;
    int req_mem;

    prg_info(){}

    prg_info(string n, int r, int m)
    {
        name = n;
        req_mem = m;
        req_ram = r;
    }
};

class proccess
{
public:
    int pid;
    prg_info* req_resources;

    proccess(){}
    proccess(int id, prg_info* resources)
    {
        pid = id;
        req_resources = resources;
    }
};

// * Globals

int disk = 0, memory = 0, cores = 0;

dict *commands;
pthread_t last_thread_id;
bool running = false;
string userin;
int Count = 0; // Commands Count

prg_info* run_prg;
vector<prg_info>prg_infos;
queue<proccess> FIFO_Queue;

vector<int> processes;

pthread_mutex_t sync_Process_io;
pthread_mutex_t schedularMutex;



int Ramid, Coresid, Memid;
int *remaining_mem, *remaining_cores, *remaining_disk;

// * -------

// * Function Prototypes
void removeWhitespaces(string &str);
bool userLogin();
void readspecs();
prg_info* findProgram(string);
void readPrograms();
void readCommands();
void *processCommand(void *args);
void creatingProcess(prg_info*);
void writeProcesses();
void readProcesses();
void *keepProcessesUpdated(void *args);
void tot_mem_usage();
void *scheduler(void *args);
void manualinput(int);
// * -------

void releaseResources()
{
    cout << "\n\nResources Released!\n\n";
    *remaining_cores = *remaining_cores + 1;
    *remaining_disk = *remaining_disk + run_prg->req_mem;
    *remaining_mem = *remaining_mem + run_prg->req_ram;
    running = false;
}

void CTRL_C_Handler(int signum) 
{

}

void Terminal_Handler(int signum) 
{
    if(running == true)
    {
        releaseResources();
    }

   exit(signum);
}

int main(int argc, char **argv)
{
    // -- OS INITIALIZATIONS
    // chdir("..");

    signal(SIGINT, CTRL_C_Handler);
    signal(SIGHUP, Terminal_Handler);

    Ramid = shmget((key_t)2345, sizeof(int), 0666 | IPC_CREAT);
    Coresid = shmget((key_t)2346, sizeof(int), 0666 | IPC_CREAT);
    Memid = shmget((key_t)2347, sizeof(int), 0666 | IPC_CREAT);

    remaining_mem = (int *)shmat(Ramid, NULL, 0);
    remaining_cores = (int *)shmat(Coresid, NULL, 0);
    remaining_disk = (int *)shmat(Memid, NULL, 0);

    // cout << *remaining_cores << endl;
    // cout << *remaining_mem << endl;
    // cout << *remaining_disk << endl;

    pthread_mutex_init(&sync_Process_io, NULL);
    pthread_mutex_init(&schedularMutex, NULL);

    readspecs();
    readPrograms();
    readCommands();
    writeProcesses();

    if (pthread_create(&last_thread_id, NULL, keepProcessesUpdated, NULL))
    {
        cout << "Process Log Init Failed.\nShutting Down Xaxis.\n";
        exit(-1);
    }

    if (pthread_create(&last_thread_id, NULL, scheduler, NULL))
    {
        cout << "Scheduler Init Failed.\nShutting Down Xaxis.\n";
        exit(-2);
    }

    // -- IDR SE APNA START KR
    if (argc != 0)
    {
        userin = "";
        for (int i = 1; i < argc; i++)
        {
            userin += argv[i];
            userin += " ";
        }

    }

    manualinput(argc);

    // -- Destroying
    pthread_mutex_destroy(&sync_Process_io);
    pthread_mutex_destroy(&schedularMutex);
}

/*

*/

void manualinput(int args)
{
    // while(!userLogin());
    // cin.ignore();
    while (1)
    {
        usleep(10000);
        if(running == false)
        {
            if (args == 1)
            {
                cout << "user@FantasyOs : ";
                
                getline(cin, userin);
                cin.clear();
            }
            else
            {
                args = 1;
            }

            if(*remaining_cores == 0)
            {
                cout << "[!]ERROR: No cores are available.\n";
            }
            else
            {
                if(userin == "exit")
                {
                    exit(0);
                }
                else if (userin == "resusage")
                {
                    cout << "\nCORES IN USE : " << cores - *remaining_cores  << endl;
                    cout << "DISK IN USE : " << disk - *remaining_disk << " MBs\n";
                    cout << "MEMORY IN USE : " << memory - *remaining_mem << " MBs\n\n";
                    //userin.clear();
                }
                else if (userin == "specs")
                {
                    cout << "\nCPU Cores : " << cores << endl;
                    cout << "MEMORY : " << memory << " MBs\n";
                    cout << "STORAGE : " << disk << " MBs" << " MBs\n\n";
                    //userin.clear();
                }
                else
                {
                    if (pthread_create(&last_thread_id, NULL, processCommand, NULL))
                    {
                        cout << "Thread Creation Failed, Couldn't Process Command.\n";
                    }

                    pthread_join(last_thread_id, NULL);
                    usleep(20000);
                }
    
            }
        }


    }
}

/*

*/

void removeWhitespaces(string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if(str[i] == ' ' || str[i] == '\n')
        {
            str.erase(str.begin()+i);
            i=0;
        }
    }
    
}

void readspecs()
{
    ifstream reader("./osspecs");
    
    reader >> cores >> memory >> disk;
}

/*

*/

void readCommands()
{
    string comm_tmp;
    ifstream reader;
    reader.open("commands");

    // Count Commands
    while (getline(reader, comm_tmp))
    {
        Count++;
    }
    //------

    commands = new dict[Count];
    reader.close();
    reader.open("commands");
    for (int i = 0; i < Count; i++)
    {
        reader >> commands[i].key;
        getline(reader, commands[i].value, '\n');
    }
    reader.close();
}

/*

*/


/*

*/

void *processCommand(void *args)
{
    bool found = false;
    string arg, comm;
    stringstream split(userin);

    split >> arg;
    getline(split, comm);



    if (arg == "run")
    {
        found = true;
        removeWhitespaces(comm);
        transform(comm.begin(), comm.end(), comm.begin(), ::tolower);

        run_prg = findProgram(comm);
        
        if(run_prg != NULL)
        {
            creatingProcess(run_prg);
        }
        else
        {
            cout << "[!]ERROR: Invalid Program\n";
        }
    }
    else
    {
        for (int j = 0; j < Count; j++)
        {
            if (arg == commands[j].key)
            {
                found = true;
                if (commands[j].value[0] == 'c' && commands[j].value[1] == 'd')
                {
                    chdir(&comm[0]);
                }
                else
                {
                    system((commands[j].value + comm).c_str());
                }
            }
        }
    }

    if(found == false)
    {
        cout << "[!]ERROR: Invalid Command\n";
    }

    pthread_exit(0);
}

void stopProcess(int pid)
{
    string cmd = "kill -STOP ";
    cmd += to_string(pid);
    system(&cmd[0]);
}

void removeProcessFromQueue(int pid)
{
    readProcesses();
    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i] == pid)
        {
            processes.erase(processes.begin() + i);
            break;
        }
    }
    writeProcesses();
}

void creatingProcess(prg_info* prg)
{
    
    int pid = fork();

    if (pid != 0)
    {
        FIFO_Queue.push(proccess(pid, prg));
        // processes.push_back(pid);
        writeProcesses();

        usleep(20000);
        wait(NULL);
        running = false;
        //userin.clear();
    }
    else
    {

        // stops the current proccess and wait for the scheduler to run it.
        stopProcess(getpid());

        string arg = "./prgs/" + prg->name;

        system(&arg[0]);

        removeProcessFromQueue(getpid());

        *remaining_cores = *remaining_cores + 1;
        *remaining_disk = *remaining_disk + prg->req_mem;
        *remaining_mem = *remaining_mem + prg->req_ram;

        exit(0);
        
    }
    return;
}

void writeProcesses()
{
    pthread_mutex_lock(&sync_Process_io);

    ofstream writer("./processes");

    for(int i=0;i<processes.size(); i++){
        writer << processes[i] << endl;
    }
    writer.close();    

    pthread_mutex_unlock(&sync_Process_io);
    return;
}


void readProcesses()
{

    pthread_mutex_lock(&sync_Process_io);
    processes.clear();

    int id;
    string name;

    ifstream reader;
    reader.open("./processes");


    while (reader >> id)
    {
        processes.push_back(id);
    }

    reader.close();
    pthread_mutex_unlock(&sync_Process_io);

}


void readPrograms()
{
    string name;
    int ram, mem;
    ifstream reader;
  
    reader.open("./programs");
    do
    {
        reader >> name;
        reader >> ram >> mem;

        prg_infos.push_back(prg_info(name, ram, mem));

    } while (!reader.eof());

    reader.close();
}

prg_info* findProgram(string name)
{
    
    for (int i = 0; i < prg_infos.size(); i++)
    {
        if(prg_infos[i].name == name)
        {
            return &prg_infos[i];
        }
    }

    return NULL;
    
}

void *keepProcessesUpdated(void *args)
{
    while (1)
    {
        readProcesses();
        usleep(10000);
    }
}


void *scheduler(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&schedularMutex);
        int numDots = 1;

        
        //busy waiting
        while (*remaining_cores == 0 && running == false);

        

        if (FIFO_Queue.size())
        {
            proccess *p;
            p = &FIFO_Queue.front();

            while(*remaining_mem < p->req_resources->req_ram && running == false);

            while(*remaining_disk < p->req_resources->req_mem && running == false);

            processes.push_back(p->pid);
            writeProcesses();
            
            string reviver = "kill -CONT ";
            reviver += to_string(p->pid);
            system(&reviver[0]);

            *remaining_cores = *remaining_cores - 1;
            *remaining_disk = *remaining_disk - p->req_resources->req_mem;
            *remaining_mem = *remaining_mem - p->req_resources->req_ram;
            running = true;
            
            usleep(2000);

            FIFO_Queue.pop();
        }
        pthread_mutex_unlock(&schedularMutex);
    }
}