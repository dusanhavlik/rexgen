
# REXIM Generator
haha funi simulator go (boom)

## Limitations
- Can not use .org in code
- .org addresses in .data have to be multiplied by 3
- hardcoded limit of 256 instructions and 768 data values
- Unintuitive value definition syntax
- Source file must create all three segments
- No string length checking in microinstruction definition segment (must be <= 5)
- Very much barely tested and fragile

## Prerequisites
- python
- [cc65 toolchain](https://cc65.github.io/) (only cl65/ca65/ld65 actually necessary)
- REXIM simulator

## Usage
- Assemble prepared source file using `cl65 -C rexim.cfg -t none --cpu none {IN_SOURCEFILE} -Ln {OUT_LABELFILE} -o {OUT_NAME}`
- Pass through python script: `python rexgen.py {OUT_NAME}.code {OUT_NAME}.data {OUT_NAME}.insdef {OUT_LABELFILE} {OUT_REXFILE_FINAL}`

Example:
- `cl65 -C rexim.cfg -Ln template.lbl -t none --cpu none template.asm -o template`
- `python rexgen.py template.code template.data template.insdef template.lbl output.rex`
