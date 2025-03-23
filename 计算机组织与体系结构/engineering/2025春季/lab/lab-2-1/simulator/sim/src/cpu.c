#include <common.h>
#include <decode.h>
#include <memory.h>

CPU_state cpu = {};
static int running = 1;
int debug_mode = 0; // 0: Batch mode, 1: Debug mode

void init_cpu(){
    cpu.pc = MEM_BASE;
    cpu.reg[0] = 0;
}

static void exec_once(){
    Decode s;
    s.pc   = cpu.pc;
    s.inst = inst_fetch(s.pc);
    s.snpc = s.pc + 4;
    decode_exec(&s);
    cpu.pc = s.dnpc;
}

void cpu_exec() {
    while (running) {
        if (debug_mode) {
            // Debug mode: Prompt for user input before each instruction
            log_info(ANSI_FMT("PC: 0x%016lx", ANSI_FG_BLUE), cpu.pc);

            char command[10];
            printf("sim> ");
            scanf("%9s", command);

            if (strcmp(command, "c") == 0) {
                // Continue execution until next breakpoint
                debug_mode = 0;
            } else if (strcmp(command, "q") == 0) {
                // Quit the simulator
                running = 0;
            } else if (strcmp(command, "si") == 0) {
                // Single step execution
                int n = 1;
                char *end;
                char num[10];
                scanf("%9s", num);
                if (num[0] != '\0') {
                    n = strtol(num, &end, 10);
                    if (*end != '\0') {
                        printf("Invalid number\n");
                        continue;
                    }
                }
                for (int i = 0; i < n && running; i++) {
                    exec_once();
                }
            } else if (strcmp(command, "info") == 0) {
                // Print register state
                char reg[10];
                scanf("%9s", reg);
                if (strcmp(reg, "r") == 0) {
                    printf("PC:   0x%08lx\n", cpu.pc);
                    for (int i = 0; i < 32; i++) {
                        if (cpu.reg[i] == 0) continue;
                        // printf("x%02d: 0x%016lx\n", i, cpu.reg[i]);
                        switch (i) {
                            case 0: printf("zero: 0x%lx\n", cpu.reg[i]); break;
                            case 1: printf("ra:   0x%lx\n", cpu.reg[i]); break;
                            case 2: printf("sp:   0x%lx\n", cpu.reg[i]); break;
                            case 3: printf("gp:   0x%lx\n", cpu.reg[i]); break;
                            case 4: printf("tp:   0x%lx\n", cpu.reg[i]); break;
                            case 5: 
                            case 6: 
                            case 7: printf("t%d:   0x%lx\n", i-5, cpu.reg[i]); break;
                            case 8: printf("s0:   0x%lx\n", cpu.reg[i]); break;
                            case 9: printf("s1:   0x%lx\n", cpu.reg[i]); break;
                            case 10: 
                            case 11: 
                            case 12: 
                            case 13: 
                            case 14: 
                            case 15: 
                            case 16: 
                            case 17: printf("a%d:   0x%lx\n", i-10, cpu.reg[i]); break;
                            case 28: 
                            case 29: 
                            case 30:
                            case 31: printf("t%d:   0x%lx\n", i-25, cpu.reg[i]); break;
                            case 26:
                            case 27: printf("s%d:  0x%lx\n", i-16, cpu.reg[i]); break;
                            default: printf("s%d:   0x%lx\n", i-16, cpu.reg[i]); break;
                        }
                    }
                }
            } else if (strcmp(command, "x") == 0) {
                // Examine memory
                int n;
                uint64_t addr;
                char dummy;
                scanf("%d%c%lx", &n, &dummy, &addr);
                for (int i = 0; i < n; i++) {
                    uint64_t data = mem_read(addr + i * 4, 4);
                    printf("0x%08lx: 0x%lx\n", addr + i * 4, data);
                }
            } else if (strcmp(command, "help") == 0) {
                // Print help information
                printf("Available commands:\n");
                printf("  c          - Continue execution\n");
                printf("  q          - Quit the simulator\n");
                printf("  si [N]     - Single step execution (N times, default 1)\n");
                printf("  info r     - Print register state\n");
                printf("  x N ADDR   - Examine memory at address ADDR, N words, ADDR: 0xXXXXXXXX\n");
                printf("  help       - Print this help information\n");
            } else {
                printf("Unknown command. Type 'help' for a list of commands.\n");
            }
        } else {
            // Batch mode: Execute instructions without interruption
            exec_once();
        }
    }
}

void toggle_debug_mode() { // Toggle debug mode
    debug_mode = !debug_mode;
    if (debug_mode) {
        printf("Debug mode enabled\n");
    } else {
        printf("Batch mode enabled\n");
    }
}

void halt_trap(uint64_t pc, uint64_t code){
    if(code){
        printf(ANSI_FMT("HIT BAD TRAP!\n", ANSI_FG_RED));
    }else{
        printf(ANSI_FMT("HIT GOOD TRAP!\n", ANSI_FG_GREEN));
    }
    log_info("Program ended at pc %08lx, with exit code %ld.", pc, code);
    running = 0;
}
