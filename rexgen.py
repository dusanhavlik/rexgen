from io import SEEK_SET
import sys
from dataclasses import dataclass
from typing import Dict
import struct

@dataclass
class Label:
    name: str
    offset: int
    value: int
    size: int

@dataclass
class CustomInstruction:
    name: str
    opcode: int
    addressing_mode: int
    micro_instructions: bytearray

INSTRUCTION_TABLE = [
    'HALT', 'ADD', 'SUB', 'MUL', 'DIV', 'NOT', 'AND', 'OR', 'XOR', 'CMP', 'JMP', 'JZ', 'JNZ', 'ROL', 'ROR', 'INC', 'DEC', 'STORE', 'LOAD'
]
ADDR_TABLE = [
    'IMM', 'DIR', 'IND'
]
if __name__ == '__main__':
    if len(sys.argv) != 6:
        print('Usage: rexgen.py [code_path] [data_path] [insdef_path] [lbl_path]')
        print('    code_path   - Cesta ku vygenerovanemu binarnemu suboru obsahujucemu kod')
        print('    data_path   - Cesta ku vygenerovanemu binarnemu suboru obsahujucemu data')
        print('    insdef_path - Cesta ku vygenerovanemu binarnemu suboru obsahujucemu definicie vlastnych instrukcii')
        print('    lbl_path    - Cesta ku vygenerovanemu suboru VICE label file')
        print('    out_path    - Cesta ku vystupnemu suboru')
        sys.exit(0)

    codepath = sys.argv[1]
    datapath = sys.argv[2]
    microinspath = sys.argv[3]
    labelpath = sys.argv[4]
    outpath = sys.argv[5]
    rex_lines = []

    # parse microinstruction file
    custom_instructions: Dict[int, CustomInstruction] = {}
    with open(microinspath, 'rb') as f:
        count = f.read(1)[0]
        for i in range(0, count):
            # get opcode
            opcode = f.read(1)[0]

            # get addressing mode
            addr_mode = f.read(1)[0] + 1

            # get name
            name_bytes = bytearray()
            temp = f.read(1)[0]
            while temp != 0:
                name_bytes.append(temp)
                temp = f.read(1)[0]
            name = name_bytes.decode(encoding='ASCII')

            # get microinstructions
            microins = bytearray()
            microcount = f.read(1)[0]
            for z in range(0, microcount):
                microins.append(f.read(1)[0])
            custom_instructions[opcode] = CustomInstruction(name, opcode, addr_mode, microins)
    
    # generate microinstruction definitions
    name_line = ''
    addrmode_line = ''
    microins_lines = []
    for i in range(13):
        microins_line = ''
        if (i+19) in custom_instructions:
            instruction = custom_instructions[i+19]
            name_line += instruction.name + ' '
            addrmode_line += str(instruction.addressing_mode) + ' '
            for microins in instruction.micro_instructions:
                microins_line += str(microins) + ' '
        else:
            name_line += 'n '
            addrmode_line += 'n '
            microins_line = 'n '
        microins_lines.append(microins_line)

    # write microinstruction definitions to file
    rex_lines.append(name_line + '\r')
    rex_lines.append(addrmode_line + '\n')
    for line in microins_lines:
        rex_lines.append(line + '\r')

    # TODO: custom code/data section sizes
    rex_lines.append('256\n')
    rex_lines.append('768\n')

    # read and decode instructions in code file
    instructions = 0
    code_lines = []
    with open(codepath, 'rb') as f:
        packed = f.read(3)
        while packed:
            number = struct.unpack('<I', packed + bytes([0]))[0]
            
            opcode = number & 0b00011111
            addrmode = (number & 0b01100000) >> 5
            value = (number & 0xffff80) >> 7

            print(f'{(opcode < len(INSTRUCTION_TABLE)) and INSTRUCTION_TABLE[opcode] or opcode} {ADDR_TABLE[addrmode]} {value}')
            code_lines.append(f'{opcode}\n')
            code_lines.append(f'{value}\n')
            code_lines.append(f'{addrmode}\n')
            instructions += 1
            packed = f.read(3)

    if instructions >= 256:
        print("too many instructions!")
        sys.exit(1)

    # fill up to upper code boundary
    for i in range(instructions, 256):
        code_lines.append(f'n\n')
    
    rex_lines += code_lines

    data_values = ['n\n' for i in range(768)]

    # parse labels
    labels: Dict[str, Label] = {}
    label_ids: Dict[int, str] = {}
    labelfilelines = []
    size_replacements: Dict[str, int] = {}
    offset_replacements: Dict[str, int] = {}
    
    with open(labelpath, 'r') as f:
        line = f.readline()
        while line:
            _, value, name = line.split()
            value = int(value, 16)

            dotprefix = name.find('.')
            if dotprefix >= 0:
                name = name[dotprefix+1:]
            
            if name.startswith('__SIZE_'):
                name = name[7:]
                size_replacements[name] = value
            elif name.startswith('__OFFS_'):
                name = name[7:]
                offset_replacements[name] = value
            else:
                label_ids[value//3 - 256] = name
                labels[name] = Label(name, -1, value//3 - 256, 1)

            line = f.readline()

    for key in size_replacements:
        labels[key].size = size_replacements[key]
    for key in offset_replacements:
        labels[key].offset = offset_replacements[key]
    for label_name in labels:
        label = labels[label_name]
    
    # read data based on exported labels
    with open(datapath, 'rb') as f:
        for _id in label_ids:
            label = labels[label_ids[_id]]
            idx = label.value
            f.seek(label.offset, SEEK_SET)
            for z in range(label.size):
                value = struct.unpack('<I', f.read(3) + bytes([0]))[0]
                data_values[idx] = str(value) + '\n'
                idx += 1
    rex_lines += data_values

    # write generated lines to file
    with open(outpath, 'w') as f:
        f.writelines(rex_lines)