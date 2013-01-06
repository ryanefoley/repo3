[spmatrix, tokenlist, category] = readMatrix('MATRIX.TEST');

testMatrix = full(spmatrix);
numTestDocs = size(testMatrix, 1);
numTokens = size(testMatrix, 2);

output = zeros(numTokens, 1);

% Load parameters
load('nb_pY.mat')
load('nb_spamWordCounts.mat')
load('nb_nonspamWordCounts.mat')
load('nb_wordCounts.mat')

% For each document predict whether spam 1, or not 0.
for j = 1:numTokens
  output(j) = log(spamWordCounts(j)/wordCounts(j)) - log(nonspamWordCounts(j)/wordCounts(j));
end

index = zeros(numTokens, 1);
for i = 1:numTokens
  index(i) = i;
end

A = [output index]';
[Y,I]=sort(A(1,:));
B=A(:,I);
B

%output = [index output];

%output = sort(output, 2);
%output
