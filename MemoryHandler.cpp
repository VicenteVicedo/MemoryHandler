#include <iostream>
#include <windows.h>
#include <String>

class MemoryHandler{
    private:
        HANDLE pHandler;
        BOOL __OpenProcess(DWORD pid){
            this->pHandler = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
            if (!this->pHandler){
                std::cerr << "Error while opening process: " << std::dec << GetLastError() << std::endl;
                return FALSE;
            }
            return TRUE;
        }
        
    public:
        MemoryHandler(DWORD pid){
            __OpenProcess(pid);
        }

        MemoryHandler(std::string processName){
            
        }

        ~MemoryHandler(){
            if(this->pHandler){
                CloseHandle(this->pHandler);
            }
        }

        template <typename T, std::size_t N = sizeof(T)> 
        T ReadMemory(LPCVOID readAddress){
            SIZE_T numReadBytes = 0;
            T readBytes;
            if constexpr (std::is_pointer<T>::value) {
                using BaseType = typename std::remove_pointer<T>::type;
                readBytes = new BaseType[N];
                ReadProcessMemory(this->pHandler, readAddress, readBytes, N, &numReadBytes);
            }
            else{
                ReadProcessMemory(this->pHandler, readAddress, &readBytes, N, &numReadBytes);
            }
             
            if (numReadBytes != sizeof(T)){
                std::cerr << "There may be reading issues. ReadBytes: " << numReadBytes << " . Size of T:" << N << std::endl;
                std::cerr << std::dec << GetLastError() << std::endl;
            }
        
            return readBytes;
        }

        template <typename T> 
        bool WriteMemory(LPVOID writeAddress, T *data){
            SIZE_T numWrittenBytes = 0;
            WriteProcessMemory(this->pHandler, writeAddress, data, sizeof((T)*data), &numWrittenBytes);
            if (numWrittenBytes != sizeof(*data)){
                std::cerr << "There may be writing issues. WrittenBytes: " << numWrittenBytes << " . Size of data:" << sizeof(T) << std::endl;
                return false;
            }
            return true;
        }

       /* template <typename T, std::size_t N = sizeof(T)> 
        T ReadArrayMemory(LPCVOID readAddress){
            SIZE_T numReadBytes = 0;

            T readBytes[N];
            ReadProcessMemory(this->pHandler, readAddress, readBytes, N, &numReadBytes);
            
            if (numReadBytes != sizeof(T)){
                std::cerr << "There may be reading issues. ReadBytes: " << numReadBytes << " . Size of T:" << N << std::endl;
                std::cerr << std::dec << GetLastError() << std::endl;
            }
        
            return readBytes;
        }*/
};

typedef char charArr[256];

int main(){
    int pid = 19636;
    MemoryHandler mem = MemoryHandler(pid);
    char arrVal[256];
    std::cout << mem.ReadMemory<int>((LPVOID)0x9381dff820) << std::endl;
    std::cout << mem.ReadMemory<char*, 256>((LPVOID)0x9381dff780) << std::endl;


    return 0;
}

void writeExec(){
    int pid = 2788;
    MemoryHandler mem = MemoryHandler(pid);
    int value = 654323;   
    mem.WriteMemory<int>((LPVOID)0x21e41ffce0, &value);
}

void exer1(){
    int pid = 2788;
    //std::cin >> pid;

    //__OpenProcess(pid, pHandle);
    MemoryHandler mem = MemoryHandler(pid);
    int *ptrVal = mem.ReadMemory<int*>((LPCVOID)0x21e41ffc28);
    int *ptr2ptrVal = mem.ReadMemory<int*>(ptrVal);
    int *ptr2intVal = mem.ReadMemory<int*>(ptr2ptrVal);
    int varIntVal = mem.ReadMemory<int>(ptr2intVal);
    std::cout << "Ptr1: " << varIntVal << std::endl;
}