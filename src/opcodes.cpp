// Copyright 2026 JesusTouchMe

#include "Bibble/opcodes.h"

namespace bibble::opcodes::opcodeutils {
    std::string GetOpcodeName(Opcode opcode) {
        switch (static_cast<Opcodes>(opcode)) {
            case NOP:
                return "nop";
            case MOV:
                return "mov";
            case MOV_RANGE:
                return "mov_range";
            case SWAP:
                return "swap";
            case LOAD_CONST:
                return "load_const";
            case LOAD_IMM:
                return "load_imm";
            case LOAD_NULL:
                return "load_null";
            case ADD:
                return "add";
            case SUB:
                return "sub";
            case MUL:
                return "mul";
            case SDIV:
                return "sdiv";
            case UDIV:
                return "udiv";
            case SMOD:
                return "smod";
            case UMOD:
                return "umod";
            case NEG:
                return "neg";
            case ABS:
                return "abs";
            case AND:
                return "and";
            case OR:
                return "or";
            case XOR:
                return "xor";
            case NOT:
                return "not";
            case SHL:
                return "shl";
            case SHR:
                return "shr";
            case SAR:
                return "sar";
            case FADD:
                return "fadd";
            case FSUB:
                return "fsub";
            case FMUL:
                return "fmul";
            case FDIV:
                return "fdiv";
            case FNEG:
                return "fneg";
            case FABS:
                return "fabs";
            case TR8:
                return "tr8";
            case TR16:
                return "tr16";
            case TR32:
                return "tr32";
            case SEX8:
                return "sex8";
            case SEX16:
                return "sex16";
            case SEX32:
                return "sex32";
            case ZEX8:
                return "zex8";
            case ZEX16:
                return "zex16";
            case ZEX32:
                return "zex32";
            case I2F:
                return "i2f";
            case U2F:
                return "u2f";
            case I2D:
                return "i2d";
            case U2D:
                return "u2d";
            case F2I:
                return "f2i";
            case F2U:
                return "f2u";
            case D2I:
                return "d2i";
            case D2U:
                return "d2u";
            case F2D:
                return "f2d";
            case D2F:
                return "d2f";
            case ICMP:
                return "icmp";
            case UCMP:
                return "ucmp";
            case FCMP:
                return "fcmp";
            case STRCMP:
                return "strcmp";
            case INC:
                return "inc";
            case DEC:
                return "dec";
            case JMP:
                return "jmp";
            case JEQ:
                return "jeq";
            case JNE:
                return "jne";
            case JLT:
                return "jlt";
            case JLE:
                return "jle";
            case JGT:
                return "jgt";
            case JGE:
                return "jge";
            case RESERVED_FOR_SWITCH_0:
                return "reserved_for_switch_0";
            case RESERVED_FOR_SWITCH_1:
                return "reserved_for_switch_1";
            case RESERVED_FOR_SWITCH_2:
                return "reserved_for_switch_2";
            case RESERVED_FOR_SWITCH_3:
                return "reserved_for_switch_3";
            case NEWINSTANCE:
                return "newinstance";
            case NEWARRAY:
                return "newarray";
            case NEWSTRING:
                return "newstring";
            case NEWFUTURE:
                return "newfuture";
            case OBJKIND:
                return "objkind";
            case ISKIND:
                return "iskind";
            case INSTANCEOF:
                return "instanceof";
            case GETFIELD:
                return "getfield";
            case SETFIELD:
                return "setfield";
            case DISPATCHMETHOD:
                return "dispatchmethod";
            case GETCLASS:
                return "getclass";
            case ARRAYLENGTH:
                return "arraylength";
            case ARRAYGET:
                return "arrayget";
            case ARRAYSET:
                return "arrayset";
            case STRLENGTH:
                return "strlength";
            case STRGET:
                return "strget";
            case STR2ARRAY:
                return "str2array";
            case RESOLVE:
                return "resolve";
            case CANCEL:
                return "cancel";
            case ISFUTUREREADY:
                return "isfutureready";
            case POLL:
                return "poll";
            case AWAIT:
                return "await";
            case CALL:
                return "call";
            case TAIL_CALL:
                return "tail_call";
            case CALLA:
                return "calla";
            case CALLAP:
                return "callap";
            case CALLARP:
                return "callarp";
            case CALL_DYN:
                return "call_dyn";
            case TAIL_CALL_DYN:
                return "tail_call_dyn";
            case CALLA_DYN:
                return "calla_dyn";
            case CALLAP_DYN:
                return "callap_dyn";
            case CALLARP_DYN:
                return "callarp_dyn";
            case RETURN:
                return "return";
            case YIELD:
                return "yield";
        }

        __builtin_unreachable(); //TODO: replace with compiler independent symbol
    }

    std::string GetOpcodeName(Opcode opcode, const PrefixState& prefix) {
        std::string name;
        if (prefix.wideOperand0) name += "wide_operand0 ";
        if (prefix.wideOperand1) name += "wide_operand1 ";
        if (prefix.wideOperand2) name += "wide_operand2 ";
        if (prefix.wideOperand3) name += "wide_operand3 ";
        if (prefix.hugeImmediate) name += "huge_immediate ";
        if (prefix.giganticImmediate) name += "gigantic_immediate ";
        name += GetOpcodeName(opcode);
        return name;
    }

    static size_t GetRegisterSize(bool wide) {
        return wide ? 2 : 1;
    }

    static size_t GetImmediateSize(bool wide, bool huge = false, bool gigantic = false) {
        if (gigantic) return 8;
        if (huge) return 4;
        if (wide) return 2;
        return 1;
    }

    static size_t GetConstPoolIndexSize(bool wide) {
        return wide ? 2 : 1;
    }

    size_t GetFixedLength(Opcode opcode, const PrefixState& prefixState) {
        size_t size = 1;
        if (prefixState.wideOperand0) size++;
        if (prefixState.wideOperand1) size++;
        if (prefixState.wideOperand2) size++;
        if (prefixState.wideOperand3) size++;
        if (prefixState.hugeImmediate) size++;
        if (prefixState.giganticImmediate) size++;

        switch (static_cast<Opcodes>(opcode)) {
            case NOP:
                break;
            case MOV:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case MOV_RANGE:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetImmediateSize(prefixState.wideOperand2);
                break;
            case SWAP:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case LOAD_CONST:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetConstPoolIndexSize(prefixState.wideOperand1);
                break;
            case LOAD_IMM:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetImmediateSize(prefixState.wideOperand1, prefixState.hugeImmediate, prefixState.giganticImmediate);
                break;
            case LOAD_NULL:
                size += GetRegisterSize(prefixState.wideOperand0);
                break;
            case ADD:
            case SUB:
            case MUL:
            case SDIV:
            case UDIV:
            case SMOD:
            case UMOD:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case NEG:
            case ABS:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case AND:
            case OR:
            case XOR:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case NOT:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case SHL:
            case SHR:
            case SAR:
            case FADD:
            case FSUB:
            case FMUL:
            case FDIV:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case FNEG:
            case FABS:
            case TR8:
            case TR16:
            case TR32:
            case SEX8:
            case SEX16:
            case SEX32:
            case ZEX8:
            case ZEX16:
            case ZEX32:
            case I2F:
            case U2F:
            case I2D:
            case U2D:
            case F2I:
            case F2U:
            case D2I:
            case D2U:
            case F2D:
            case D2F:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case ICMP:
            case UCMP:
            case FCMP:
            case STRCMP:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case INC:
            case DEC:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetImmediateSize(prefixState.wideOperand1, prefixState.hugeImmediate,
                                         prefixState.giganticImmediate);
                break;
            case JMP:
                size += GetImmediateSize(prefixState.wideOperand0, prefixState.hugeImmediate,
                                         prefixState.giganticImmediate);
                break;
            case JEQ:
            case JNE:
            case JLT:
            case JLE:
            case JGT:
            case JGE:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetImmediateSize(prefixState.wideOperand1, prefixState.hugeImmediate,
                                         prefixState.giganticImmediate);
                break;
            case RESERVED_FOR_SWITCH_0:
            case RESERVED_FOR_SWITCH_1:
            case RESERVED_FOR_SWITCH_2:
            case RESERVED_FOR_SWITCH_3:
                break;
            case NEWINSTANCE:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetConstPoolIndexSize(prefixState.wideOperand1);
                break;
            case NEWARRAY:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += 1;
                break;
            case NEWSTRING:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case NEWFUTURE:
                size += GetRegisterSize(prefixState.wideOperand0);
                break;
            case OBJKIND:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case ISKIND:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += 1;
                break;
            case INSTANCEOF:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetConstPoolIndexSize(prefixState.wideOperand2);
                break;
            case GETFIELD:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetConstPoolIndexSize(prefixState.wideOperand2);
                break;
            case SETFIELD:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetConstPoolIndexSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case DISPATCHMETHOD:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetConstPoolIndexSize(prefixState.wideOperand2);
                break;
            case GETCLASS:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case ARRAYLENGTH:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case ARRAYGET:
            case ARRAYSET:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case STRLENGTH:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case STRGET:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case STR2ARRAY:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case RESOLVE:
            case CANCEL:
            case ISFUTUREREADY:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case POLL:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case AWAIT:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case CALL:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetConstPoolIndexSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case TAIL_CALL:
                size += GetConstPoolIndexSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case CALLA:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetConstPoolIndexSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case CALLAP:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetConstPoolIndexSize(prefixState.wideOperand2);
                size += GetRegisterSize(prefixState.wideOperand3);
                break;
            case CALLARP:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += 1;
                size += GetConstPoolIndexSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case CALL_DYN:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case TAIL_CALL_DYN:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                break;
            case CALLA_DYN:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case CALLAP_DYN:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                size += GetRegisterSize(prefixState.wideOperand3);
                break;
            case CALLARP_DYN:
                size += GetRegisterSize(prefixState.wideOperand0);
                size += 1;
                size += GetRegisterSize(prefixState.wideOperand1);
                size += GetRegisterSize(prefixState.wideOperand2);
                break;
            case RETURN:
                size += GetRegisterSize(prefixState.wideOperand0);
                break;
            case YIELD:
                break;
        }

        return size;
    }

    bool IsTerminator(Opcode opcode) {
        switch (opcode) {
            case JMP:
            case TAIL_CALL:
            case TAIL_CALL_DYN:
            case RETURN:
                return true;
            default:
                return false;
        }
    }

    bool IsConditionalBranch(Opcode opcode) {
        switch (opcode) {
            case JEQ:
            case JNE:
            case JLT:
            case JGT:
            case JLE:
            case JGE:
                return true;
            default:
                return false;
        }
    }

    bool IsBranch(Opcode opcode) {
        return IsConditionalBranch(opcode) || opcode == JMP;
    }

    bool IsCall(Opcode opcode) {
        switch (opcode) {
            case CALL:
            case TAIL_CALL:
            case CALLA:
            case CALLAP:
            case CALLARP:
            case CALL_DYN:
            case TAIL_CALL_DYN:
            case CALLA_DYN:
            case CALLAP_DYN:
            case CALLARP_DYN:
                return true;
            default:
                return false;
        }
    }

    bool IsAsyncCall(Opcode opcode) {
        switch (opcode) {
            case CALLA:
            case CALLAP:
            case CALLARP:
            case CALLA_DYN:
            case CALLAP_DYN:
            case CALLARP_DYN:
                return true;
            default:
                return false;
        }
    }

    bool IsFloatOp(Opcode opcode) {
        switch (opcode) {
            case FADD:
            case FSUB:
            case FMUL:
            case FDIV:
            case FNEG:
            case FABS:
            case FCMP:
            case I2F:
            case U2F:
            case I2D:
            case U2D:
            case F2I:
            case F2U:
            case D2I:
            case D2U:
            case F2D:
            case D2F:
                return true;
            default:
                return false;
        }
    }
}
