.include "rexim.inc"

; custom instruction definition segment
.segment "MICROINS"

    .byte 1 ; number of defined instructions - value must exist, if there are no instructions, then it's zero

    ; custom instruction names have to be less or equal to 5 characters
    ; things may break otherwise (no error handling)
    ins_begin "NOP", ADDR_NONE
        .byte MOPC_INC_ACC
        .byte MOPC_DEC_ACC
    ins_end

    ; macro needs to be defined manually
    ; call_ins_imp is used for implied addressing - no value
    ; call_ins_imm is used for immediate addressing - single value
    ; call_ins_dir is used for direct addressing - single pointer to value
    ; call_ins_ind is used for indirect addressing - single pointer to pointer to vlaue

    .macro nop
        call_ins_imp NOP
    .endmacro

    ;.macro example_direct_instruction addr
    ;   call_ins_dir addr/3
    ;.endmacro
; data segment
.segment "DATA"

    ; starts at rexim address 256
    value_single test_single_value, 4

    ; array of values
    value_multi_begin test_multi_value
        .faraddr 1 ; do not use any other type here other than .faraddr, especially not value_single
        .faraddr 1
        .faraddr 2
    value_multi_end test_multi_value ; needs to be passed both to value_multi_begin and value_multi_end

    .org rexim_addr(300) ; at rexim address 300
    value_single another_single_value, 5

; code segment
.segment "CODE"
; DO NOT USE .ORG HERE. THINGS WILL BREAK.
    nop
    load_dir test_single_value
    cmp_imm 5
    jz_imm is_five
        ; accumulator will be 25
        mul_imm 5
        halt
is_five:
    ; accumulator will be 104
    add_imm 100
    halt