# File:   penalized_logistic_regression-1.0.R
# Author: Ben Kasper
# Date:   11/14/2012


# Prerequisites
library(Matrix)
library(glmnet)
library(pROC)

# Functions (source them later)
readSparseMatrix <- function(filename, sep, header) {
  result <- read.table(file = filename, sep = sep, header = header)
  result <- sparseMatrix(i = result[,1], j = result[,2], x = result[,3])
  return(result)
}

# Import data
x.train <- readSparseMatrix('matrix_train_0.dat', sep = " ", header = FALSE)
y.train <- as.vector(unlist(read.table('labels_train_0.dat')))

# Penalized logistic regression
cv.log.reg <- cv.glmnet(x = x.train, y = y.train, family = 'binomial',
                        nfolds = 10, type.measure = "class")
plot(cv.log.reg)
plambda.opt <- cv.log.reg$lambda.1se

# Errors
preds <- predict(cv.log.reg, newx = x.train, type = "response")
plot(preds - y.train)
hist(y.train - preds)
table(y.train)
hist(preds)
plot(density(preds))
plot(density(y.train))



rocCurve = roc(response = y.train, predictor = preds)
plot(rocCurve)

























