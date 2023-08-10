#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <vector>
#include <TlHelp32.h>

std::vector<DWORD> GetProcIdsByName(const char* proc_name)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    std::vector<DWORD> ids;
 
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
 
    if(Process32First(snapshot, &entry))
        while(Process32Next(snapshot, &entry))
            if(!strcmp(entry.szExeFile, proc_name))
                ids.push_back(entry.th32ProcessID);
 
    return ids;
}

int main(int argc, char* argv[])
{
    HANDLE pHndl;
    HMODULE* modHndls;
    DWORD b_alloc = 8, b_needed; 
    char modName[MAX_PATH];
    std::vector<DWORD> pID = GetProcIdsByName(argv[1]);
    for (int j = 0; j < pID.size(); j++)
    {
        pHndl = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pID[j]);
        while (1)
        {
            modHndls=(HMODULE*)malloc(b_alloc);
            EnumProcessModules(pHndl,modHndls,b_alloc,&b_needed);
            if (b_alloc >= b_needed)
                break;
            else
            {
                free(modHndls);
                b_alloc=b_needed;
            }
        }

        for(int i=0; i < b_needed/sizeof(DWORD); i++)
        {
            GetModuleBaseName(pHndl, modHndls[i], (LPSTR)modName, sizeof(modName));
            printf("%u\t%s", modHndls[i],modName);
            GetModuleFileName(modHndls[i], (LPSTR)modName, sizeof(modName));
            printf("\t%s\n",modName);
        }
    }
    return 0;
}
