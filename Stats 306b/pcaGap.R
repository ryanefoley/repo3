library("gplots") ### for PlotCi

olive <- read.table("http://www-stat.stanford.edu/~tibs/sta306b/olive.txt")

pca.olive = princomp(olive[,-c(1,2)], cor = TRUE)


var = array()
for(i in 1:8){
	var[i] = pca.olive$sdev[i]^2/sum(pca.olive$sdev^2)
}

cumVar = cumsum(var)

k = 100
randVar = matrix(0, nrow = k, ncol = 8)

for(q in 1:k){

randObs = matrix(0, nrow = 572, ncol = 8)
for(i in 1:8){
	for(j in 1:572)
	randObs[j,i] = runif(1, min(olive[,i+2]), max(olive[,i+2]))
}

pca.rand = princomp(randObs, cor = TRUE)

var2 = array()
for(i in 1:8){
	var2[i] = pca.rand$sdev[i]^2/sum(pca.rand$sdev^2)
}
randVar[q,] = cumsum(var2)
}

means = array()
sds = array()
for(i in 1:8){
	means[i] = mean(randVar[,i])
	sds[i] = sd(randVar[,i])
}

plotCI(cumVar - means, uiw=(sds*sqrt(1+1/k)), ylab = "Gap", col = 2)



