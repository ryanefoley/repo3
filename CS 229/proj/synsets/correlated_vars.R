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
x <- readSparseMatrix('matrix_full_0.dat', sep = " ", header = FALSE)
x <- as.matrix(x)
y <- as.vector(unlist(read.table('labels_full_0.dat')))

corm <- cor(x)
out <- which(abs(corm) > 0.99, arr.ind=TRUE)
w = out[out[,1] > out[,2]]
xo = x[,-w]
save(xo, file = 'xo_cor_vars_removed.Rdata')

#result = tune(svm, xo, y, ranges = list(gamma = 2^(-12:2), cost = 2^(-1:4)), tunecontrol = tune.control(sampling = "fix"), kernel = 'radial')
