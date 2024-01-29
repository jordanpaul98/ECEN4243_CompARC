"""
  Register File Testbench generator built for ECEN 4243 LAB0

  generates all test cases for N number of input registers and output registers for 1 write addressa nd 1 write data
  to be used for testvecotr inputs for system verilog

  Ex. readAddress1, readAdress2, writeAdress, writeData, readData1, readData2 (5bit registers address and 32 bit data)
  ->  OUTPUT: xxxxx_xxxxx_xxxxx_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
      Where for each write data test will generate all registers states.
            any zero read address will ahve zero on read data

             00000_00000_00001_[_write_data]_[ zero ]_[ zero ]
             00000_00001_00001_[_write_data]_[ zero ]_[_write_data]
             00001_00000_00001_[_write_data]_[_write_data]_[ zero ]
             00001_00001_00000_[_write_data]_[_write_data]_[_write_data]

     test case for read Address for zero manually entered as for any write data will be zero
              - includes case to test if read data for both read address are zero with write data
"""


def regout_generator(num_reg, register_size, output_size):
    from random import randint
    # Make the first two lines where the read address are 0 with write data set to 0 and max,
    # were expected is supposed to be zero out read data is 0
    lines = ["_".join(f"{0:0>{register_size}}" for _ in range(num_reg + 1)) +
             f"_{0:0>{output_size}}" * (num_reg + 1),

             "_".join(f"{0:0>{register_size}}" for _ in range(num_reg + 1)) +
             f"_{2 ** output_size - 1:0>{output_size}b}" +
             f"_{0:0>{output_size}}" * num_reg]

    # loop over 1 to max register space (2 ** register_size - 1)
    for register_index in range(1, 2 ** register_size):

        # get a random write data value
        rand_value = randint(0, 2 ** output_size)

        for i in range(2 ** num_reg):
            tv_str = ''

            # loop over each read address state Ex. if there are two registers [ 0|0, 0|1, 1|0, 1|1 ]
            # were 1 would imply that the register as a read address provided zero would expect zero
            # to be read on the output for any input
            for j in range(num_reg):
                if i & (1 << j):
                    tv_str += f"{register_index:0>{register_size}b}_"
                else:
                    tv_str += f"{0:0>{register_size}b}_"

            # add the write address
            tv_str += f"{register_index:0>{register_size}b}"
            # add the write data
            tv_str += f"_{rand_value:0>{output_size}b}"

            # add the expected read data, zero if read address is zero, else the write data
            for j in range(num_reg):
                if i & (1 << j):
                    tv_str += f"_{rand_value:0>{output_size}b}"
                else:
                    tv_str += f"_{0:0>{output_size}b}"

            # append the data to be return
            lines.append(tv_str)

    return lines

if __name__ == "__main__":

    outfile_name = 'regfile.tv'

    with open(outfile_name, 'w') as file:
        # loop over each line and write the data
        for line in regout_generator(2, 5, 32):
            file.write(f"{line}\n")
        file.close()
