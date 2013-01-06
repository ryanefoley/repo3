
[spmatrix, tokenlist, category] = readMatrix('MATRIX.TEST');

testMatrix = full(spmatrix);
numTestDocs = size(testMatrix, 1);
numTokens = size(testMatrix, 2);

% Assume nb_train.m has just been executed, and all the parameters computed/needed
% by your classifier are in memory through that execution. You can also assume 
% that the columns in the test set are arranged in exactly the same way as for the
% training set (i.e., the j-th column represents the same token in the test data 
% matrix as in the original training data matrix).

% Write code below to classify each document in the test set (ie, each row
% in the current document word matrix) as 1 for SPAM and 0 for NON-SPAM.

% Construct the (numTestDocs x 1) vector 'output' such that the i-th entry 
% of this vector is the predicted class (1/0) for the i-th  email (i-th row 
% in testMatrix) in the test set.
output = zeros(numTestDocs, 1);

% Load parameters
load('nb_pY.mat')
load('nb_spamWordCounts.mat')
load('nb_nonspamWordCounts.mat')
load('nb_wordCounts.mat')

% For each document predict whether spam 1, or not 0.
for i = 1:numTestDocs
  %log_prob_spam = 0;
  %log_prob_nonspam = 0;
  for j = 1:numTokens
    phi1 = 
    %log_prob_spam = log_prob_spam + testMatrix(i,j)*(log(pY) + log(spamWordCounts(j)/wordCounts(j));
    %log_prob_nonspam = log_prob_nonspam + testMatrix(i,j)*(log(1-pY) + log(nonspamWordCounts(j)/wordCounts(j));
  end
  %if log_prob_spam  > log_prob_nonspam
    output(i) = 1;
  end
end

% Compute the error on the test set
error=0;
for i=1:numTestDocs
  if (category(i) ~= output(i))
    error=error+1;
  end
end

%Print out the classification error on the test set
error/numTestDocs


