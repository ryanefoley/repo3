data = matrix(runif(min=-3, max=5, n = 1000*100), nrow = 1000, ncol = 100)
treatAndConLabels = array();
for(i in 1:100){
	if(runif(min = 0, max = 1,1)>.5){treatAndConLabels[i] = c("T")}
	else {treatAndConLabels[i] = c("C")}
}
colnames(data) <- treatAndConLabels

for(i in 1:100){
	if(treatAndConLabels[i] == c("T")){ data[,i] + 2 }
}

machineUsed = array()
library(Rlab)
for(t in 1:100){
	if(rbern(1,t/100) == 1){
		machineUsed[t] = 1 #1 for machine B
		data[,t] = data[,t] + 2
		}
	else{machineUsed[t] = 0}	#0 for machine A
}

data = rbind(machineUsed, data)
dataNoEffect = data.frame(t(data))

for(i in 2:1001){ #removing effect of machine used
	aovFit = aov(dataNoEffect[,i] ~ dataNoEffect[,1], dataNoEffect)
	dataNoEffect[,i] = dataNoEffect[,i] - dataNoEffect[,1]*as.numeric(aovFit$coefficients[2])
}
end;
