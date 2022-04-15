#include <dirent.h>
#include <malloc.h>
 
int main()
{
    struct dirent **namelist;
    int n;
 
    n = scandir(".", &namelist, 0, alphasort);
    if (n < 0){
        perror("not found\n");
    }
    else{
        while(n--){
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
    return 0;
}
