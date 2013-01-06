library(Matrix)
library(e1071)
library(SparseM)

# Functions (source them later)
readSparseMatrix <- function(filename, sep, header) {
       result <- read.table(file = filename, sep = sep, header = header)
        result <- sparseMatrix(i = result[,1], j = result[,2], x = result[,3])
          return(result)
}

# Import data
print('loading...')
load('xo_cor_vars_removed.Rdata')
y <- as.vector(unlist(read.table('labels_full_0.dat')))

print('tuning...')
result = tune(svm, xo, y, ranges = list(gamma = 2^(-10:-2), cost = 2^(0:3)), tunecontrol = tune.control(sampling = "fix"), kernel = 'radial')
                                                                                                                                              
