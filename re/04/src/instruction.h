//
// Created by Kotori0 on 2020/10/3.
//

#ifndef EZVM_INSTRUCTION_H
#define EZVM_INSTRUCTION_H

enum InstructionList {
    INST_PUSH = 1,
    INST_POP,

    INST_PUTS,
    INST_GETS,

    INST_PUTC,
    INST_GETC,

    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_DIV,
    INST_XOR,

    INST_SHL,
    INST_SHR,

    INST_CMP,
    INST_JMP,

    INST_JE,
    INST_JNE,
    INST_JA,
    INST_JB,

    INST_DUP,
    INST_NOP,
    INST_STOP = 0xff
};

#endif //EZVM_INSTRUCTION_H
