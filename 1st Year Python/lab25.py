def compute_totals(filename: str) -> None:
    # open the input file for reading
    with open(filename, 'r') as infile:
        # read the lines of the file
        lines = infile.readlines()
        # create a 2D list to store the integers
        nums = []
        # loop over the lines
        for line in lines:
            # split the line into integers
            values = [int(x) for x in line.split()]
            # add the values to the list
            nums.append(values)

    # determine the name of the output file
    outfile_name = filename.split('.')[0] + '_totals.txt'

    # open the output file for writing
    with open(outfile_name, 'w') as outfile:
        # loop over the rows of the 2D list
        for row in nums:
            # write the values separated by tabs
            outfile.write('\t'.join(str(x) for x in row))
            # compute the sum of the row
            row_sum = sum(row)
            # write the row sum to the end of the line
            outfile.write('\t' + str(row_sum) + '\n')

if __name__ == "__main__":
    filename = input()
    compute_totals(filename)
    
