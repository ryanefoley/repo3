genes = 1000
genesWithEff = 100

data = matrix(rnorm(n = genes*100, mean = 0 , sd = 1), nrow = genes, ncol = 100)

treatAndConLabels = array();

for(i in 1:100){
	if(runif(min = 0, max = 1,1)>.5){treatAndConLabels[i] = c("T")}
	else {treatAndConLabels[i] = c("C")}
}

for(i in 1:100){
	if(treatAndConLabels[i] == c("T")){ data[1:genesWithEff,i] = data[1:genesWithEff,i] + 1 }
}

machineUsed = array()
library(Rlab)
for(t in 1:100){
	#x = (t-50)/10
	if(rbern(1,t/100) == 1){
		machineUsed[t] = "B"
		data[,t] = data[,t] + 10
		}
	else{machineUsed[t] = "A"}	
}


#Plotting the linear trend in the first PC
t = rep(1:100)
pca.data = prcomp(data)
plot(pca.data$rotation[,1])
fit = lm(pca.data$rotation[,1]~t)
abline(fit)

#Recomputing the data matrix without the first PC
svd.data = svd(data)
svd.data$d[1] = 0
x = data -  svd.data$d[1] * svd.data$u[,1] %*% t(svd.data$v[,1])

p.values = array()
for(i in 1:genesWithEff){
	p.values[i] = t.test(x[i, treatAndConLabels == c("T")], x[i, treatAndConLabels == c("C")])$p.value
	}


#### Calculate power for test with pc removed

count = 0
sigLevel = .1
for(i in 1:length(p.values)){
	if(p.values[i] < sigLevel){ count = count + 1}
	}
power = count/genesWithEff

####Calculate and remove machine effect from data

#create row of 0s and 1s corresponding to machine A and B respectively for data

machine = ifelse(machineUsed == "A", 0,1)
machine = matrix(machine, nrow = 1, ncol = 100)
newdata = rbind(machine, data)
newdata = data.frame(t(newdata))
for(i in 2:ncol(newdata)){
	fit = aov(newdata[,i] ~ newdata[,1], newdata)
	newdata[,i] = newdata[,i] - newdata[,1]*fit$coef[2]
	}

newdata = as.matrix(t(newdata))

p.values = array()
for(i in 2:nrow(newdata)){
	p.values[i-1] = t.test(newdata[i, treatAndConLabels == c("T")], newdata[i, treatAndConLabels == c("C")])$p.value
}


count = 0
sigLevel = .1
for(i in 1:genesWithEff){
	if(p.values[i] < sigLevel){ count = count + 1}
	}
power2 = count/genesWithEff



	
	
	
	
	
