#include <iostream>
#include <stack>
#include <random>
#include "program.h"
#include "instruction.h"

int main() {
    std::stack<uint8_t> stk;

    /* encryption */
    std::mt19937 generator(0x1919810);
    std::uniform_int_distribution<uint16_t> dis(0, 0xff);
    for(int i = 0; i < sizeof(program_const); i++) {
        program[i] = (dis(generator) & 0xff) ^ program_const[i];
    }

    const uint8_t* program_ptr = program;
    int8_t cmp = 0;
    bool stop = false;

    while (*program_ptr != 0) {
        uint8_t inst = *program_ptr;
        program_ptr++;
        if (stop) {
            break;
        }

        switch (inst) {
            case INST_PUSH:
                stk.push(*program_ptr++); break;
            case INST_POP:
                stk.pop(); break;
            case INST_PUTS: {
                while (stk.top() != 0) {
                    putchar(stk.top());
                    stk.pop();
                }
                stk.pop();
                putchar('\n');
                break;
            }
            case INST_GETS: {
                stk.push(0);
                while (true) {
                    uint8_t c = getchar();
                    if (c == '\n') {
                        break;
                    }
                    stk.push(c);
                }
                break;
            }
            case INST_PUTC: {
                putchar(stk.top());
                stk.pop();
                break;
            }
            case INST_GETC: {
                stk.push(getchar());
                break;
            }
            case INST_ADD: {
                uint8_t a = stk.top();stk.pop();
                uint8_t b = stk.top();stk.pop();
                stk.push(a + b);
                break;
            }
            case INST_SUB: {
                uint8_t a = stk.top();stk.pop();
                uint8_t b = stk.top();stk.pop();
                stk.push(a - b);
                break;
            }
            case INST_MUL: {
                uint8_t a = stk.top();stk.pop();
                uint8_t b = stk.top();stk.pop();
                stk.push(a * b);
                break;
            }
            case INST_DIV: {
                uint8_t a = stk.top();stk.pop();
                uint8_t b = stk.top();stk.pop();
                stk.push(a / b);
                break;
            }
            case INST_XOR: {
                uint8_t a = stk.top();stk.pop();
                uint8_t b = stk.top();stk.pop();
                stk.push(a ^ b);
                break;
            }
            case INST_SHL: {
                uint8_t a = stk.top();stk.pop();
                uint8_t shift = *++program_ptr;
                stk.push(a << shift);
                break;
            }
            case INST_SHR: {
                uint8_t a = stk.top();stk.pop();
                uint8_t shift = *++program_ptr;
                stk.push(a >> shift);
                break;
            }
            case INST_CMP: {
                uint8_t a = stk.top();stk.pop();
                uint8_t b = stk.top();stk.pop();
                if (a == b) {
                    cmp = 0;
                } else if (a > b) {
                    cmp = 1;
                } else {
                    cmp = -1;
                }
                break;
            }
            case INST_JMP: {
                uint16_t addr = *(uint16_t *)program_ptr;
                program_ptr = program + addr;
                break;
            }
            case INST_JE: {
                if (cmp == 0) {
                    uint16_t addr = *(uint16_t *)program_ptr;
                    program_ptr = program + addr;
                } else {
                    program_ptr += 2;
                }

                break;
            }
            case INST_JNE: {
                if (cmp != 0) {
                    uint16_t addr = *(uint16_t *)program_ptr;
                    program_ptr = program + addr;
                } else {
                    program_ptr += 2;
                }
                break;
            }
            case INST_JA: {
                if (cmp > 0) {
                    uint16_t addr = *(uint16_t *)program_ptr;
                    program_ptr = program + addr;
                } else {
                    program_ptr += 2;
                }
                break;
            }
            case INST_JB: {
                if (cmp < 0) {
                    uint16_t addr = *(uint16_t *)program_ptr;
                    program_ptr = program + addr;
                } else {
                    program_ptr += 2;
                }
                break;
            }
            case INST_STOP:
                stop = true;
                break;
            case INST_DUP:
                stk.push(stk.top());
                break;
            case INST_NOP:
                break;
            default:
                throw std::runtime_error("Unknown Instruction");
        }
    }
    return 0;
}
