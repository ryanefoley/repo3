# File:   svm.R
# Author: Ryan Foley
# Date:   11/14/2012


# Prerequisites
library(Matrix)
library(e1071)
library(pROC)
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
x <- as.matrix.csr(x)
y <- as.vector(unlist(read.table('labels_full_0.dat')))

# SVM
fit = svm(x,y, cross = 10)

