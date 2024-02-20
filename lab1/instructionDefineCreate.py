# create all the #define index for instruction calls

instructions = ["ADD", "ADDI", "AND", "ANDI", "AUIPC", "BEQ",
                "BGE", "BGEU", "BLT", "BLTU", "BNE", "JAL",
                "JALR", "LB", "LBU", "LH", "LHU", "LUI",
                "LW", "OR", "ORI", "SB", "SH", "SLL",
                "SLLI", "SLT", "SLTI", "SLTIU", "SLTU", "SRA",
                "SRAI", "SRL", "SRLI", "SUB", "SW", "XOR",
                "XORI", "ECALL"]

print(len(instructions))

for i, intr in enumerate(instructions):
    print(f"#define {intr}_INSTRUCTION {i}")
