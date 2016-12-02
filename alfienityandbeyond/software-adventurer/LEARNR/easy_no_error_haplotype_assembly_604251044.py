import timeit

with open('easy_no_error_2_chromosomes_training_reads.txt') as f:
    input_matrix = f.read().splitlines()

with open('easy_no_error_2_chromosomes_training_haplotypes.txt') as f:
    input_haplotypes = f.read().splitlines()

def assemble_complement_haplotype(haplotype):
    complement_haplotype = ''
    for c in haplotype:
        if c == '0':
            complement_haplotype += '1'
        else:
            complement_haplotype += '0'
    return complement_haplotype

def generate_haplotype_combinations(comb, size):
    if size == 0:
        return comb
    else:
        if len(comb) == 0:
            return generate_haplotype_combinations(['0','1'], size-1)
        else:
            return generate_haplotype_combinations([i + '0' for i in comb] + [i + '1' for i in comb], size-1)


def base_assembly():
    base_results = []
    haplotype = ''

    # Check all 2^N combinations and verify if it matches with haplotype
    haplotype_combinations = generate_haplotype_combinations([], 25)
    for haplotype in haplotype_combinations:
        if haplotype == input_haplotypes[0][0:25] or haplotype == input_haplotypes[1][0:25]:
            base_results.append(haplotype)
            base_results.append(assemble_complement_haplotype(haplotype))
            break

    return base_results

def iterative_assembly(read_matrix):
    iterative_results = []
    haplotype = '0'
    last_index = 0

    # Iterate through all the reads and generate one haplotype from proper overlap
    # O(MN)
    for i in range(len(read_matrix)):
        for j in range(len(read_matrix[i])):
            if haplotype[last_index] == read_matrix[i][last_index] and j > last_index and read_matrix[i][j] != '-':
                haplotype += read_matrix[i][j]
                last_index = j

    iterative_results.append(haplotype)
    iterative_results.append(assemble_complement_haplotype(haplotype))
    return iterative_results

def greedy_assembly(read_matrix):
    greedy_results = []
    haplotype = '0'
    last_index = 0
    numRows = len(read_matrix)
    numCols = len(read_matrix[0])

    # Iterate through reads from last overlap rather than from the beginning
    # O(N)
    i = 0
    j = 1
    while j < numCols and i < numRows:
        if haplotype[last_index] == read_matrix[i][last_index]:
            while j < numCols:
                if read_matrix[i][j] != '-':
                    haplotype += read_matrix[i][j]
                    last_index = j
                else:
                    i += 1
                    break
                j += 1
        else:
            i += 1

    greedy_results.append(haplotype)
    greedy_results.append(assemble_complement_haplotype(haplotype))
    return greedy_results

#print('Expected training haplotypes to be assembled from input read matrix:\n'
 #     + input_haplotypes[0] + '\n' + input_haplotypes[1])

# Easy Haplotype Assembly:
# Build a greedy algorithm for haplotype phasing from sequence reads
# Assume no sequencing error
#print('Haplotype Assembly (Baseline Randomization):')
base_haplotypes = base_assembly()
for haplotype in base_haplotypes:
   print haplotype
#t_base = timeit.Timer(stmt='base_assembly()', setup='from __main__ import base_assembly')
#print('Timing (Baseline Randomization): ' + str(t_base.timeit(number=1)) + 's')

#print('Haplotype Assembly (Iterative Method):')
iterative_haplotypes = iterative_assembly(input_matrix)
for haplotype in iterative_haplotypes:
    print haplotype
#t_iterative = timeit.Timer(stmt='iterative_assembly(input_matrix)',
 #                          setup='from __main__ import iterative_assembly, input_matrix')
#print('Timing (Iterative Method): ' + str(t_iterative.timeit(number=1000)) + 's')

#print('Haplotype Assembly (Linear Greedy Method):')
greedy_haplotypes = greedy_assembly(input_matrix)
for haplotype in greedy_haplotypes:
    print haplotype
#t_greedy = timeit.Timer(stmt='greedy_assembly(input_matrix)',
#                        setup='from __main__ import greedy_assembly, input_matrix')
#print('Timing (Linear Greedy Method): ' + str(t_greedy.timeit(number=1000)) + 's')