.feature org_per_seg
.setcpu "none"
ADDR_NONE = -1
ADDR_IMM = %0000000
ADDR_DIR = %0100000
ADDR_IND = %1000000
ADDR_IMP = %0000000

; instruction opcodes
OPCODE_HALT = %00000
OPCODE_ADD = %00001
OPCODE_SUB = %00010
OPCODE_MUL = %00011
OPCODE_DIV = %00100
OPCODE_NOT = %00101
OPCODE_AND = %00110
OPCODE_OR = %00111
OPCODE_XOR = %01000
OPCODE_CMP = %01001
OPCODE_JMP = %01010
OPCODE_JZ = %01011
OPCODE_JNZ = %01100
OPCODE_ROL = %01101
OPCODE_ROR = %01110
OPCODE_INC = %01111
OPCODE_DEC = %10000
OPCODE_STORE = %10001
OPCODE_LOAD = %10010

; custom instruction microcode opcodes
MOPC_MOVE_ACC_TO_MBR = 0
MOPC_MOVE_MBR_TO_ACC = 1
MOPC_MOVE_PC_TO_MAR = 2
MOPC_MOVE_MBR_TO_IR = 5
MOPC_HALT = 6
MOPC_READ_MEM = 7
MOPC_WRITE_MEM = 8
MOPC_ADD = 9
MOPC_INC_PC = 10
MOPC_TEST_ACC = 11
MOPC_NOT_ACC = 12
MOPC_RSHIFT_ACC = 13
MOPC_DECODE = 14
MOPC_MOVEADR_MBR_TO_MAR = 15
MOPC_MOVEADR_IR_TO_MBR = 16
MOPC_MUL = 17
MOPC_DIV = 18
MOPC_LSHIFT_ACC = 19
MOPC_AND = 20
MOPC_OR = 21
MOPC_XOR = 22
MOPC_CMP = 23
MOPC_MOVEADR_MBR_TO_PC = 24
MOPC_INC_ACC = 25
MOPC_DEC_ACC = 26
MOPC_SUB = 27
MOPC_TESTN_ACC = 28

; instruction macros
.define halt .faraddr ADDR_IMP | OPCODE_HALT
.define not .faraddr ADDR_IMP | OPCODE_NOT
.define rol .faraddr ADDR_IMP | OPCODE_ROL
.define ror .faraddr ADDR_IMP | OPCODE_ROR

.macro add_imm value
 
    .faraddr ADDR_IMM | OPCODE_ADD | ((value & $ffff) << 7)
.endmacro
.macro add_dir value
 
    .faraddr ADDR_DIR | OPCODE_ADD | (((value & $ffff) / 3) << 7)
.endmacro
.macro add_ind value
 
    .faraddr ADDR_IND | OPCODE_ADD | (((value & $ffff) / 3) << 7)
.endmacro

.macro sub_imm value
 
    .faraddr ADDR_IMM | OPCODE_SUB | ((value & $ffff) << 7)
.endmacro
.macro sub_dir value
 
    .faraddr ADDR_DIR | OPCODE_SUB | (((value & $ffff) / 3) << 7)
.endmacro
.macro sub_ind value
 
    .faraddr ADDR_IND | OPCODE_SUB | (((value & $ffff) / 3) << 7)
.endmacro

.macro mul_imm value
 
    .faraddr ADDR_IMM | OPCODE_MUL | ((value & $ffff) << 7)
.endmacro
.macro mul_dir value
 
    .faraddr ADDR_DIR | OPCODE_MUL | (((value & $ffff) / 3) << 7)
.endmacro
.macro mul_ind value
 
    .faraddr ADDR_IND | OPCODE_MUL | (((value & $ffff) / 3) << 7)
.endmacro

.macro div_imm value
 
    .faraddr ADDR_IMM | OPCODE_DIV | ((value & $ffff) << 7)
.endmacro
.macro div_dir value
 
    .faraddr ADDR_DIR | OPCODE_DIV | (((value & $ffff) / 3) << 7)
.endmacro
.macro div_ind value
 
    .faraddr ADDR_IND | OPCODE_DIV | (((value & $ffff) / 3) << 7)
.endmacro

.macro and_imm value
 
    .faraddr ADDR_IMM | OPCODE_AND | ((value & $ffff) << 7)
.endmacro
.macro and_dir value
 
    .faraddr ADDR_DIR | OPCODE_AND | (((value & $ffff) / 3) << 7)
.endmacro
.macro and_ind value
 
    .faraddr ADDR_IND | OPCODE_AND | (((value & $ffff) / 3) << 7)
.endmacro

.macro or_imm value
 
    .faraddr ADDR_IMM | OPCODE_OR | ((value & $ffff) << 7)
.endmacro
.macro or_dir value
 
    .faraddr ADDR_DIR | OPCODE_OR | (((value & $ffff) / 3) << 7)
.endmacro
.macro or_ind value
 
    .faraddr ADDR_IND | OPCODE_OR | (((value & $ffff) / 3) << 7)
.endmacro

.macro xor_imm value
 
    .faraddr ADDR_IMM | OPCODE_XOR | ((value & $ffff) << 7)
.endmacro
.macro xor_dir value
 
    .faraddr ADDR_DIR | OPCODE_XOR | (((value & $ffff) / 3) << 7)
.endmacro
.macro xor_ind value
 
    .faraddr ADDR_IND | OPCODE_XOR | (((value & $ffff) / 3) << 7)
.endmacro


.macro cmp_imm value
 
    .faraddr ADDR_IMM | OPCODE_CMP | ((value & $ffff) << 7)
.endmacro
.macro cmp_dir value
    .faraddr ADDR_DIR | OPCODE_CMP | (((value & $ffff) / 3) << 7)
.endmacro
.macro cmp_ind value
    .faraddr ADDR_IND | OPCODE_CMP | (((value & $ffff) / 3) << 7)
.endmacro

.macro jmp_imm value
    .faraddr ADDR_IMM | OPCODE_JMP | (((value & $ffff) / 3) << 7)
.endmacro

.macro jz_imm value
    .faraddr ADDR_IMM | OPCODE_JZ | (((value & $ffff) / 3) << 7)
.endmacro

.macro jnz_imm value
 
    .faraddr ADDR_IMM | OPCODE_JNZ | (((value & $ffff) / 3) << 7)
.endmacro

.macro inc_imm value
 
    .faraddr ADDR_IMM | OPCODE_INC | ((value & $ffff) << 7)
.endmacro
.macro inc_dir value
 
    .faraddr ADDR_DIR | OPCODE_INC | (((value & $ffff) / 3) << 7)
.endmacro
.macro inc_ind value
 
    .faraddr ADDR_IND | OPCODE_INC | (((value & $ffff) / 3) << 7)
.endmacro

.macro dec_imm value
 
    .faraddr ADDR_IMM | OPCODE_DEC | ((value & $ffff) << 7)
.endmacro
.macro dec_dir value
 
    .faraddr ADDR_DIR | OPCODE_DEC | (((value & $ffff) / 3) << 7)
.endmacro
.macro dec_ind value
 
    .faraddr ADDR_IND | OPCODE_DEC | (((value & $ffff) / 3) << 7)
.endmacro

.macro store_dir value
 
    .faraddr ADDR_DIR | OPCODE_STORE | (((value & $ffff) / 3) << 7)
.endmacro
.macro store_ind value
 
    .faraddr ADDR_IND | OPCODE_STORE | (((value & $ffff) / 3) << 7)
.endmacro

.macro load_dir value
    .faraddr ADDR_DIR | OPCODE_LOAD | (((value & $ffff) / 3) << 7)
.endmacro
.macro load_ind value 
    .faraddr ADDR_IND | OPCODE_LOAD | (((value & $ffff) / 3) << 7)
.endmacro

; data definition macros
_value_file_offset .set 0
.macro value_single name, value
    .if .tcount(value) <> 1
        .error "value_single only supports 1 value"
    .endif

name: 
    .faraddr value
.export name
.ident(.concat("__OFFS_", .string(name))) = _value_file_offset
    .export .ident(.concat("__OFFS_", .string(name)))
.ident(.concat("__SIZE_", .string(name))) = 1
    .export .ident(.concat("__SIZE_", .string(name)))
_value_file_offset .set _value_file_offset + 3
.endmacro

.macro value_multi_begin name
:
name:
.ident(.concat("__OFFS_", .string(name))) = _value_file_offset
    .export .ident(.concat("__OFFS_", .string(name)))
.export name
.endmacro

.macro value_multi_end name
:
_value_file_offset .set _value_file_offset + (:- - :--)
.ident(.concat("__SIZE_", .string(name))) = (:- - :--)/3
    .export .ident(.concat("__SIZE_", .string(name)))
.endmacro

; custom instruction definition macros
.macro _error_on_invalid_addressing addr
    .if .not (.xmatch(addr, ADDR_NONE) .or .xmatch(addr, ADDR_IMM) .or .xmatch(addr, ADDR_DIR) .or .xmatch(addr, ADDR_IND))
        .error .sprintf("invalid addressing mode: %d", addr)
    .endif
.endmacro
_instruction_counter .set OPCODE_LOAD+1
.macro call_ins_imm ident, value
    .faraddr ADDR_IMM | ident | ((value & $ffff) << 7)
.endmacro
.macro call_ins_dir ident, value
    .faraddr ADDR_DIR | ident | ((value & $ffff) << 7)
.endmacro
.macro call_ins_ind ident, value
    .faraddr ADDR_IND | ident | ((value & $ffff) << 7)
.endmacro
.macro call_ins_imp ident
    .faraddr ADDR_IMP | ident
.endmacro
.macro ins_begin name, addr
    _error_on_invalid_addressing addr
    
    .ident (name) = _instruction_counter
    .byte _instruction_counter
    _instruction_counter .set _instruction_counter + 1

    .scope
    .if .xmatch(addr, ADDR_NONE)
        .byte ADDR_NONE+1
    .elseif .xmatch(addr, ADDR_IMM)
        .byte ADDR_IMM+1
    .elseif .xmatch(addr, ADDR_DIR)
        .byte ADDR_DIR+1
    .elseif .xmatch(addr, ADDR_IND)
        .byte ADDR_IND+1
    .endif

    .asciiz name
    .byte :++ - :+
:
    .if .xmatch(addr, ADDR_IMM)
        .byte MOPC_MOVEADR_IR_TO_MBR
    .elseif .xmatch(addr, ADDR_DIR)
        .byte MOPC_MOVEADR_IR_TO_MBR, MOPC_MOVEADR_MBR_TO_MAR, MOPC_READ_MEM
    .elseif .xmatch(addr, ADDR_IND)
        .byte MOPC_MOVEADR_IR_TO_MBR, MOPC_MOVEADR_MBR_TO_MAR, MOPC_READ_MEM, MOPC_MOVEADR_MBR_TO_MAR, MOPC_READ_MEM
    .endif
 .endmacro
 .macro ins_end
 :
    .endscope
 .endmacro

.define rexim_addr(val) val*3
