#include <common.h>
#include <memory.h>
#include <cpu.h>

uint8_t *mem = NULL;
extern int debug_mode;

int main(int argc, char *argv[]){
    
    if (argc < 2) {
        log_err("Usage: %s <image_file> [debug]", argv[0]);
        return -1;
    }

    mem = (uint8_t *)malloc(MEM_SIZE);
    check_mem(mem);
    memset(mem, 0, MEM_SIZE);
    load_image(argv[1]);
    init_cpu();

    if (argc > 2 && strcmp(argv[2], "debug") == 0) {
        log_info("Debug mode enabled");
        debug_mode = 1;
    }

    cpu_exec();
    free(mem);
    return 0;

error:
    if(mem) free(mem);
    return -1;
}
