# Read in snp_table
snp_table = read.table("SNP_Status.txt", header = TRUE, sep=" ", nrows=1, comment.char="")
classes <- sapply(snp_table,class)
snp_table2 = read.table("SNP_Status.txt", header = TRUE, sep=" ", colClasses=classes, comment.char="")
snp_matrix = as.matrix(snp_table2)

num_cases <- 0
num_controls <- 0

allele_case_count <- vector(mode="integer", length=100000)
allele_control_count <- vector(mode="integer", length=100000)

is_case <- TRUE

#Gather allele case and control counts
for (i in 1:2000) {
  if (snp_matrix[i, 100002] == 'Control') {
    is_case <- FALSE
  } else {
    is_case <- TRUE
  }
  for (j in 2:100001) {
    j_index <- j-1
    snp_value <- as.numeric(snp_matrix[i,j])
    if(is_case == TRUE) {
      allele_case_count[j_index] <- allele_case_count[j_index] + snp_value
    } else {
      allele_control_count[j_index] <- allele_control_count[j_index] + snp_value
    }
  }
}

allele_case_frequency <- vector(mode="double", length=100000)
allele_control_frequency <- vector(mode="double", length=100000)

for(i in 1:100000) {
  # Gather Pa+ and Pa- (observed frequencies) for each SNP A
  allele_case_frequency[i] <- (allele_case_count[i] / 2000)
  allele_control_frequency[i] <- (allele_control_count[i] / 2000)
}

snp_assoc_stat <- vector(mode="double", length=100000)
snp_pval <- vector(mode="double", length=100000)

two_div_n <- sqrt(2/2000)
for (i in 1:100000) {
  # Calculate assoc_stat for SNP A
  pa_avg <- (allele_case_frequency[i] + allele_control_frequency[i]) / 2
  snp_assoc_stat[i] <- (allele_case_frequency[i] - allele_control_frequency[i])/((two_div_n)*(sqrt(pa_avg*(1-pa_avg))))
  # Calculate pval for SNP A
  snp_pval[i] <- 2*pnorm(-1*abs(snp_assoc_stat[i]))
}

for(i in 1:100000) {
  if (is.nan(snp_pval[i]))
    snp_pval[i] <- 1
}

pval_thresh <- 2*pnorm(qnorm(0.05/2))
alpha_s <- (0.05/100000)
pval_thresh_s <- 2*pnorm(qnorm(alpha_s/2))

# Output results to file
sink(file='604251044_output_pa1.txt')
print('UID:604251044')
print('email:alfred.lucero@ucla.edu')
print('Undergrad or Grad:Undergrad')
print('<A>')
snp_output <- ""
for(i in 1:100000) {
  snp_output <- sprintf("SNP%05d:%f", (i-1), snp_pval[i])
  print(snp_output)
}
print('</A>')
print('<B>')
for(i in 1:100000) {
  if (snp_pval[i] < pval_thresh_s) {
    snp_output <- sprintf("SNP%05d", (i-1))
    print(snp_output)
  }
}
print('</B>')
sink()
